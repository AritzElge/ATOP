## Hardware Abstraction Layer (HAL) Interface Definition

### 1. Overview

The Atop library serves as the mission-critical core for UAV flight control. To maintain isolation from the specific MCU hardware (e.g., STM32, ESP32, or Rad-Hard ARM), it requires the Application Layer to provide direct functional links to the sensors and actuators.
This interface is critical for the Inner Loop (Rate/Attitude) and Outer Loop (Position/Navigation) control stability.

### 2. Interface Mechanism: Functional Injection

The library defines standardized function signatures. The developer must link these signatures to the actual MCU peripheral drivers (I2C, SPI, UART, PWM) during the system power-up sequence.

#### Safety Verification

Upon registration, Atop performs:

1. Pointer Integrity: NULL-pointer checks.
2. Redundancy Validation: Post-write verification as defined in error_handling.md.

### 3. Flight-Critical Function Signatures

#### 3.1. Inertial Measurement Unit (IMU)

Essential for high-frequency attitude estimation.

Function	Responsibility	Expected Behavior
bool (*get_accel)(float*, float*, float*)	Fetch Accelerometer data (X, Y, Z).	Units: m/s². Must be non-blocking.
bool (*get_gyro)(float*, float*, float*)	Fetch Gyroscope data (X, Y, Z).	Units: rad/s. Must be calibrated for bias.

##### Critical for the control loop determinism.

Function	Responsibility	Precision
get_timestamp_us	Return system uptime in microseconds.	Microsecond resolution for WCET calculations.
delay_blocking	Hardware-accurate blocking delay.	Used only during critical peripheral power-up.

### 4. Implementation Constraints for UAV Critical Flight

To ensure the stability of the control loops, the implementation of these functions must comply with:

1. **Jitter Minimization:** Sensor reading functions must have a predictable execution time to avoid "latency jitter" in the PID/EKF loops.
2. **Unit Consistency:** All data MUST be provided in the International System of Units (SI). Converting units inside the critical loop is prohibited to save CPU cycles.
3. **Atomic Reads:** For sensors like the IMU, the X, Y, and Z components must be sampled from the same hardware register snapshot to avoid "inter-axis skew".
4. **Failsafe Support:** If a hardware function returns false, the library will immediately trigger the Failsafe/Safe-Mode logic (e.g., emergency landing or motor cut-off).