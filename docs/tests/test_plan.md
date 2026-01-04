## Test Plan & Verification Strategy

### 1. Overview

The verification of the Atop library follows a V-Model approach, starting from a Proof of Concept (PoC) to full Hardware-In-The-Loop (HITL) simulation. This ensures that the control logic is sound before it ever commands a real actuator.

### 2. Phase 0: Proof of Concept (PoC)

Before full implementation, a PoC was conducted to validate the Dependency Injection architecture.

* **Objective:** Verify that the micro-kernel can execute a "Dummy Control Loop" using function pointers without overhead or memory corruption.
* **Execution:** A minimal sketch on a PC/MCU where "sensors" were just static variables and "actuators" were printf statements.
* **Success Criteria:** Stable loop timing and successful detection of NULL pointers during the registration phase.

### 3. Phase 1: Software-In-The-Loop (SITL)

The library is compiled for the host machine (Linux/Windows) and linked to a flight simulator.
* **Methodology:** The Atop kernel runs as a standalone process on the PC.
* **Interfacing:** Functions like get_accel() and get_gyro() are mapped to a bridge that reads data from the flight simulator (e.g., via UDP or Shared Memory).
* **Focus:**
    * **Validation of PID/Orientation_Filter** (EKF, Madgwick or others) convergence.
    * **Testing of the Outer Loop** (trajectory tracking) in a risk-free environment.
    * Code coverage analysis.

### 4. Phase 2: Hardware-In-The-Loop (HITL)

The actual library runs on the target MCU, but the "world" remains virtual.

* **Methodology:** The MCU is connected to a PC via Serial (UART) or CAN bus.
* **Interfacing:**
    * **Sensors:** The MCU receives "telemetry" from the simulator and injects it into the library through the get_ functions.
    * **Actuators:** The library's set_motor_output() sends commands back to the simulator's physics engine.
* **Focus:**
    * **MCU Performance:** Measuring CPU load and WCET on the real architecture.
    * **Latency Analysis:** Verifying that the Serial/Interfacing overhead does not destabilize the Inner Loop.

### 5. Critical Verification Matrix

Requirement	Test Method	Environment
Logic Correctness	Mathematical Unit Tests	SITL
Real-time Deadlines	Timing Analysis / Oscilloscope	HITL
Safety Failover	Fault Injection (Sensor Disconnect)	SITL / HITL
Bit-flip Resilience	Memory Corruption Simulation	HITL (on MCU)

### 6. Simulation Environment
To ensure high-fidelity results, the following stack is proposed:

* **Flight Simulator:** FlightGear or Gazebo for physics and sensor noise modeling.
* **Interface Bridge:** A custom Python/C++ script to translate simulator packets into the library's functional signatures.