# Software Requirements Specification

## 1. Functional Requirements (FR)
*   **FR-01**: The library shall compute attitude estimation (Roll, Pitch, Yaw) using a generic IMU interface.
*   **FR-02**: The system shall support attitude filters like Madgwick or Mahony through a modular architecture.
*   **FR-03**: The library shall calculate the required attitude setpoints (Pitch, Roll, Yaw) to execute flight maneuvers.
*   **FR-04**: The library shall support registration of external hardware drivers via function pointers.

## 2. Non-Functional & Safety Requirements (NFR)
*   **NFR-01 (Determinism)**: The core control loop shall execute with a Worst-Case Execution Time (WCET) compatible with a 400Hz frequency.
*   **NFR-02 (Memory)**: The library shall use 0 bytes of dynamic memory (Heap).
*   **NFR-03 (Robustness)**: The system shall detect and handle NULL function pointers before execution.
*   **NFR-04 (Portability)**: The core logic shall be decoupled from MCU-specific registers.