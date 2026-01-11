# Software Requirements Specification

## 1. Functional Requirements (FR)
*   **FR-01**: The library shall compute attitude estimation (Roll, Pitch, Yaw) using a generic IMU interface.
*   **FR-02**: The system shall support attitude filters like Madgwick or Mahony through a modular architecture.
*   **FR-03**: The library shall calculate the required attitude setpoints (Pitch, Roll, Yaw) to execute flight maneuvers.
*   **FR-04**: The library shall support registration of external hardware drivers via function pointers.

## 2. Non-Functional & Safety Requirements (NFR)
*   **NFR-01 (Determinism)**: The core control loop shall execute with a Worst-Case Execution Time (WCET) compatible with a 400Hz frequency.
*   **NFR-02 (Memory)**: The micro-kernel shall use 0 bytes of dynamic memory (Heap).
*   **NFR-03 (Robustness)**: The system shall detect and handle NULL function pointers before execution.
*   **NFR-04 (Portability)**: The core logic shall be decoupled from MCU-specific registers.
*   **NFR-05 (Interoperability)**: The micro-kernel headers shall be compatible with C++ compilers using extern 'C' linkage specifications.

## 3. Architectural Requirements (AR)
*   **AR-01 (Layered Architecture)**: The system shall be strictly layered into a *Device Abstraction Layer* and a *Service Layer* to ensure hadware independance.
*   **AR-02 (Encapsulation)**: All internal system states shall be encapsulated, direct access to global variables from outside the module is prohibited.
*   **AR-03 (Static Configuration)**: System parameters and buffer sizes shall be configurable at compile-time to avoid runtime overhead.
*   **AR-04 (Interface-based desing)**: The micro-kernel shall interact with hardware through generic interfaces (APIs) to allow swaping of drivers without modifying the core logic.