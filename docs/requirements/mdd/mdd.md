# Mission Description Document (MDD) - Template
*Based on ECSS-E-ST-10C Annex B (DRD: Mission description document)*

---

## 1. Introduction

### **1.1 Purpose and Objectives**
The purpose of this Mission Description Document (MDD) is to establish the baseline mission concept, operational profile, and architectural boundaries for the **ATOP (Aeronautic Trajectory and Orientation Processor).**
The primary objective of ATOP is to provide a deterministic, highly reliable, hardware-agnostic C-language library capable of computing aeronautic trajectory estimation, orientation processing, and executing both inner-loop stabilization and outer-loop guidance control for fixed-wing UAVs under strict criticality constraints.

### **1.2 Scope**
This document covers the Phase 0/A mission concept description, operational phases, hardware-agnostic abstraction philosophy via compile-time macro injection, and top-level constraints for the ATOP core library. It serves as the baseline from which the User Requirements Document(URD) and subsequent Software Requirements Specifications (SRS) are derived.

### **1.3 Definitions, Acronyms and Abbreviations**
- **ATOP**: Aeronautic Trajectory and Orientation Processor.
- **HAL / DAL**: Hardware Abstraction Layer / Device Abstraction Layer.
- **Inner Loop**: Attitude stabilization and control loop. Known as orientation loop in the original project.
- **Outer Loop**: Trajectory tracking, navigation, and guidance loop. Known as Trajectory Loop in original project.
- **Bare-metal**: Execution environment without an uderlying Real-Time Operating System (RTOS).
- **UAV**: Unmanned Aerial Vehicle.

---

## 2. Applicable and Reference Documents

### 2.1 Applicable Documents
| Doc ID | Title | Issue/Rev |
|--------|-------|-----------|
| [AD-1] | Preliminary Technical Requirements Specification (Derived) | [1.0] |

### 2.2 Reference Documents
| Doc ID | Title | Issue/Rev |
|--------|-------|-----------|
| [RD-1] | ECSS-E-ST-10C - System Engineering General Requirements | Rev. 1 |
| [RD-2] | ECSS-E-ST-40C - Software Engineering | Rev. 1 |
| [RD-3] | MISRA-C:2012 Guidelines | March 2013 |
| [RD-4] | The Power of 10: Rules for Developing Safety-Critical Code (NASA/JPL) | - |
| [RD-5] | PATO (Procesador Aeronautico de Trayectoria y Orientación) -  TFG Arch. Baseline | 1.0 |

---

## 3. Preliminary Technical Requirements Specification Summary

### **3.1 Summary of Objectives**
- **Trajectory & Orientation Processing**: Execute robust state estimation of aircraft vectors, attitude, and trajectory parameters.
- **Hierarchical Flight Control**: Execute inner-loop stabilization (high-bandwidth plant damping) and outer-loop guidance (low-bandwidth trajectory tracking cognizant of asynchronous sensor updates like GNSS).
- **Hardware Agnosticism & Language Interoperability**: Decouple numerical processing and control algorithms from physical microcontrollers through compile-time macro dependency injection (HAL/DAL hooks), exposing a clean C API wrapped with `extern "C"` for seamless C++ integration.
- **Maximum Criticality Compliance**: Enforce strict execution boundedness, static memory allocation (zero dynamic allocation), and compliance with MISRA-C and Power of 10 safety rules.

### **3.2 Design Driving Requirements**
- **DD-01 (Computational Boundedness & Predictability)**: ATOP core algorithms shall exhibit strictly bounded execution times and zero dynamic memory allocation to ensure mathematical predictability and eliminate runtime indeterminism.
- **DD-02 (Hardware Decoupling)**: Zero direct dependencies on hardware registers or vendor-specific HAL libraries inside ATOP core; all sensor inputs (IMU, GNSS) and actuator/throttle outputs must be bound at compile-time via macro hooks.
- **DD-03 (Resource Footprint & Portability)**: The library must execute on targets ranging from 8-bit to 32-bit platforms with minimal static RAM and flash footprints, maintaining logical equivalence across architectures.
- **DD-04 (Asynchronous Sensor Management)**: The architecture must support multirate processing, decoupling high-rate inner-loop mechanics from low-rate, asynchronous external updates (e.g., GNSS at $\le 5\text{ Hz}$).


---

## 4. Concept Description

### 4.1 Overview of the Concept
ATOP is structured as a decoupled layered firmware library. The architecture enforces strict separation of concerns: the core service layer operates exclusively on standardized abstract data structures, completely agnostic of physical peripherals. Integration is achieved via compile-time macro dependency injection, ensuring zero runtime overhead.

### 4.2 Mission Analysis and Environment
- **Operational Environment**: Fixed-wing unmanned aerial vehicle operating under atmospheric aerodynamic disturbances. The system engages exclusively when the aircraft is already airborne in level flight.
- **Sensor Inputs**: High-rate Inertial Measurement Unit (IMU) and low-rate asynchronous Position/Velocity vectors from GNSS receivers.
- **Actuator Outputs**: Surface control ailerons, elevator, and rudder actuators.

### 4.3 System Description (Element by Element)
- **4.3.1 Service Layer (Core ATOP)**: The processing engine containing the Sensor Fusion Filter, Mathematical Utilities, and Precision PID Controllers.
- **4.3.2 Device Abstraction Layer (DAL)**: Interface contracts defining data structures and pre-conditions for sensors and actuators.
- **4.3.3 Application Layer (Mission Orchestrator)**: The host environment (`main.c`/`cpp`) responsible for initialization, macro binding, and mission state management.

### 4.4 Description of How the System Works in Each Mission Phase
- **4.4.1 Initialization & Calibration**: Startup, static memory verification, sensor bias estimation, and state vector seeding.
- **4.4.2 Disarmed / Standby**: System active, monitoring health, waiting for engagement command once airborne.
- **4.4.3 Armed & Guided Manual**: Flight control active post-launch (level flight); operator or ground station provides direct guidance/attitude consignas that modulate the inner loop directly.
- **4.4.4 Nominal Autonomous Flight**: Continuous execution of high-rate attitude stabilization and low-rate trajectory tracking (waypoint navigation via GNSS).

### 4.5 Performance Drivers
- Low latency in state estimation, jitter-free execution of PID control loops, strict execution boundedness, and robust handling of asynchronous telemetry.

### 4.6 Constraints
- Strict zero-malloc policy, compact static memory footprint, MISRA-C compliance, and hardware agnosticism via compile-time macro injection.

### 4.7 Main Events
- **ME-01**: Completion of sensor bias estimation and static memory allocation validation upon system boot.
- **ME-02**: System engagement post-launch (in level flight) and activation of inner-loop plant damping.
- **ME-03**: Transition between Operator-Guided mode (direct attitude consignas) and Autonomous Waypoint Navigation.

### 4.8 Operations Scenarios
- **OS-01 (Autonomous Survey / Waypoint Flight)**: The UAV executes a pre-programmed sequence of spatial waypoints while in level flight. Outer-loop updates trajectories using asynchronous GNSS telemetry while inner-loop stabilizes aerodynamic disturbances at high frequency.
- **OS-02 (Operator-Assisted / Guided Flight)**: The ground operator overrides autonomous trajectory tracking to inject direct attitude/heading consignas, which ATOP modulates directly through the inner-loop stabilization mechanics.

---

## 5. Assessment of the Performance
- **5.1 Compliance Assessment**: ATOP's macro-injection model and strict C linkage satisfy portability and integration requirements across diverse host environments.
- **5.2 Non-Compliances and Impacts**: None identified at the Phase 0/A concept baseline.

---

## 6. Identification of Risk Areas

- **6.1 Technological Risks**: Numerical stability and quantization effects of Sensor Fusion Filter matrices on resource-constrained 8-bit targets.
- **6.2 Contingencies and Failure Handling**: Loss of GNSS signal results in graceful degradation of outer loop, falling back to dead reckoning or pure inner-loop attitude stabilization.
- **6.3 Programmatic Risks**: Verification complexity across multiple distinct hardware platforms and compiler toolchains.
- **6.4 Trade-off Analysis**: Selection of deterministic Kalman filtering and compile-time macro injection over dynamic dispatch and heuristic filters to guarantee execution bounds and eliminate runtime overhead.

---

## 7. Conclusion

- **7.1 Strengths**: Complete hardware agnosticism, C/C++ interoperability via `extern "C"`, strict determinism via zero dynamic memory allocation, and robust handling of asynchronous sensor inputs.
- **7.2 Weaknesses**: Integration responsibility relies entirely on the host system engineer to satisfy DAL pre-conditions.

---

## 8. Special Remarks

### **INTEGRATION & QUALIFICATION NOTICE**: 
- ATOP is provided as an uncompiled, hardware-agnostic firmware library. Compliance with safety rules (such as MISRA-C and static memory bounds) within the core codebase does not constitute end-system qualification. Final verification, binary static analysis, worst-case execution time (WCET) profiling, and hardware-in-the-loop (HIL) testing must be performed by the integrating entity on the final compiled target binary.

