# User Requirements Document (URD): ATOP (Aeronautic Trajectory and Orientation Processor)
*Based on ECSS-E-ST-10C / ECSS-E-ST-10-06C principles*

## 1. Introduction
- **1.1 Purpose**: The purpose of this User Requirements Document (URD) is to establish the formal, verifiable stakeholder and user requirements for **ATOP (Aeronautic Trajectory and Orientation Processor)**, translating the mission concepts from the [MDD](../mdd/mdd.md) into high-level functional, performance, interface, and safety requirements.
- **1.2 Scope**: This document covers the user-level and system-level operational expectations for ATOP as a fixed-wing UAV flight control and orientation processing firmware library, serving as the parent document for the subsequent SRS.
> **INTEGRATION & QUALIFICATION NOTICE**: 
> ATOP is provided as an uncompiled, hardware-agnostic firmware library. Compliance with safety rules (such as MISRA-C and static memory bounds) within the core codebase does not constitute end-system qualification. Final verification, binary static analysis, worst-case execution time (WCET) profiling, and hardware-in-the-loop (HIL) testing must be performed by the integrating entity on the final compiled target binary.

- **1.3 Definitions, Acronyms and Abbreviations**:
  - **ATOP**: Aeronautic Trajectory and Orientation Processor.
  - **URD**: User Requirements Document.
  - **MDD**: Mission Description Document.
  - **HAL / DAL**: Hardware Abstraction Layer / Device Abstraction Layer.
  - **Inner Loop**: High-bandwidth attitude stabilization and plant damping loop.
  - **Outer Loop**: Low-bandwidth trajectory tracking and guidance loop.
  - **Bare-metal**: Execution environment without an underlying Real-Time Operating System (RTOS).
  - **UAV**: Unmanned Aerial Vehicle.

## 2. Applicable and Reference Documents
### 2.1 Applicable Documents
| Doc ID | Title | Issue/Rev |
|--------|-------|-----------|
| [AD-1] | Mission Description Document (MDD): ATOP | 1.0 |

### 2.2 Reference Documents
| Doc ID | Title | Issue/Rev |
|--------|-------|-----------|
| [RD-1] | ECSS-E-ST-10C - System Engineering General Requirements | Rev. 1 |
| [RD-2] | ECSS-E-ST-40C - Software Engineering | Rev. 1 |
| [RD-3] | ECSS-E-ST-10-06C - Technical Requirements Specification | Rev. 1 |
| [RD-4] | MISRA-C:2012 Guidelines | March 2013 |
| [RD-5] | The Power of 10: Rules for Developing Safety-Critical Code (NASA/JPL) | - |
| [RD-6] | PATO (Procesador Aeronáutico de Trayectoria y Orientación) - TFG Arch. Baseline | 1.0 |

## 3. General Description of the User Needs
- **3.1 Operational Context**: ATOP shall operate as an embedded firmware library within the flight computer of a fixed-wing unmanned aerial vehicle (UAV) under strict *bare-metal* execution across 8-bit to 32-bit microcontrollers. The system engages exclusively post-launch, once the aircraft is airborne in level flight.
- **3.2 Mission Objectives**: Provide deterministic state estimation, hierarchical flight control (inner/outer loops), complete hardware independence via compile-time macro dependency injection, and C++ interoperability via `extern "C"`.
- **3.3 Operational Scenarios**: 
  - *OS-01 (Autonomous Survey)*: Pre-programmed spatial waypoint navigation combining outer-loop GNSS updates and high-rate inner-loop stabilization.
  - *OS-02 (Operator-Assisted / Guided Mode)*: Ground operator injects direct attitude/heading consignas, overriding autonomous trajectory tracking and modulating the inner loop directly.

## 4. User and Mission Requirements
*Requirements shall be unique, atomic, verifiable, and structured with IDs like `URD-[CAT]-[NUM]`.*

### 4.1 Functional Requirements
- **URD-FUNC-0010 (Inner-Loop Stabilization)**: The ATOP core shall execute high-bandwidth attitude stabilization and plant damping (inner loop) based on high-rate inertial sensor inputs.
  - *Verification Method*: Test / Analysis
  - *Traceability*: [MDD Section 3.2 (DD-01)](../mdd/mdd.md#dd-01-computational-boundedness--predictability)
- **URD-FUNC-0020 (Outer-Loop Guidance & Waypoints)**: The ATOP core shall execute low-bandwidth trajectory tracking and waypoint navigation (outer loop), incorporating asynchronous telemetry updates from GNSS receivers.
  - *Verification Method*: Test
  - *Traceability*: [MDD Section 3.2 (DD-04)](../mdd/mdd.md#dd-04-asynchronous-sensor-management)
- **URD-FUNC-0030 (Operator-Assisted Guided Mode)**: The system shall provide an operational mode allowing an external operator or ground station to inject direct attitude/heading consignas that modulate the inner-loop stabilization mechanics.
  - *Verification Method*: Test
  - *Traceability*: [MDD Section 4.4.3 & OS-02](../mdd/mdd.md#44-description-of-how-the-system-works-in-each-mission-phase)
- **URD-FUNC-0040 (Hardware-Agnostic Binding)**: The library shall completely decouple its core algorithms from physical hardware peripherals, utilizing compile-time macro dependency injection (HAL/DAL hooks) for sensor inputs and actuator outputs.
  - *Verification Method*: Review of Design / Inspection
  - *Traceability*: [MDD Section 3.2 (DD-02)](../mdd/mdd.md#dd-02-hardware-decoupling)
- **URD-FUNC-0050 (Language Interoperability)**: The library public API shall expose a clean C interface wrapped with `extern "C"` to guarantee seamless integration within C++ host environments.
  - *Verification Method*: Test / Inspection
  - *Traceability*: [MDD Section 3.1](../mdd/mdd.md#31-summary-of-objectives)

### 4.2 Operational & Performance Requirements
- **URD-PERF-0010 (Computational Predictability)**: ATOP core algorithms shall exhibit strictly bounded execution times to ensure mathematical predictability across target platforms.
  - *Verification Method*: Analysis / Test
  - *Traceability*: [MDD Section 3.2 (DD-01)](../mdd/mdd.md#dd-01-computational-boundedness--predictability)
- **URD-PERF-0020 (Multirate Asynchronous Processing)**: The architecture shall support decoupled multirate execution, allowing high-rate inner-loop processing independently of low-rate, asynchronous external GNSS updates ($\le 5\text{ Hz}$).
  - *Verification Method*: Test / Analysis
  - *Traceability*: [MDD Section 3.2 (DD-04)](../mdd/mdd.md#dd-04-asynchronous-sensor-management)

### 4.3 Interface & Environmental Constraints
- **URD-ENV-0010 (Target Portability)**: The firmware library shall be capable of compiling and executing on target hardware ranging from constrained 8-bit microcontrollers (e.g., AVR) to 32-bit platforms (e.g., STM32, PIC, RISC-V / LEON).
  - *Verification Method*: Test / Review of Design
  - *Traceability*: [MDD Section 3.2 (DD-03)](../mdd/mdd.md#dd-03-resource-footprint--portability)
- **URD-ENV-0020 (Engagement Condition)**: The flight control loops shall be designed to engage exclusively when the host application signals that the aircraft is airborne in level flight (post-launch).
  - *Verification Method*: Test / Review of Design
  - *Traceability*: [MDD Section 4.2](../mdd/mdd.md#42-mission-analysis-and-environment)

### 4.4 Reliability, Availability, Maintainability & Safety (RAMS)
- **URD-RAMS-0010 (Zero Dynamic Memory Allocation)**: The library shall strictly prohibit dynamic memory allocation (`malloc`, `calloc`, `realloc`, or equivalent) at runtime to prevent heap fragmentation and ensure memory safety.
  - *Verification Method*: Inspection / Static Code Analysis
  - *Traceability*: [MDD Section 4.6](../mdd/mdd.md#46-constraints)
- **URD-RAMS-0020 (Coding Standards Compliance)**: All source code implementing the ATOP core shall comply with safety-critical coding guidelines, specifically MISRA-C and NASA's Power of 10 rules.
  - *Verification Method*: Static Code Analysis / Code Review
  - *Traceability*: [MDD Section 2.2](../mdd/mdd.md#22-reference-documents)

> **INTEGRATION & QUALIFICATION NOTICE**: 
> ATOP is provided as an uncompiled, hardware-agnostic firmware library. Compliance with safety rules (such as MISRA-C and static memory bounds) within the core codebase does not constitute end-system qualification. Final verification, binary static analysis, worst-case execution time (WCET) profiling, and hardware-in-the-loop (HIL) testing must be performed by the integrating entity on the final compiled target binary.

## 5. Operational & Natural Environment
- **URD-ENV-NAT-0010 (Aerodynamic & Gravitational Disturbances)**: The library algorithms shall maintain numerical stability under standard fixed-wing atmospheric aerodynamic disturbances and varying gravitational vectors.
  - *Verification Method*: Analysis / Simulation Test
  - *Traceability*: [MDD Section 4.2](../mdd/mdd.md#42-mission-analysis-and-environment)

## 6. Security and Data Protection
- **URD-SEC-0010 (State Data Encapsulation)**: Internal filter states and flight control parameters shall be fully encapsulated within defined data structures to prevent unauthorized or unintended external memory corruption by host application code.
  - *Verification Method*: Code Review / Inspection
  - *Traceability*: [MDD Section 4.3.1](../mdd/mdd.md#43-system-description-element-by-element)