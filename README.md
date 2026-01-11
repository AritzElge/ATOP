# ATOP: Aeronautic Trajectory and Orientation Processor

An educational, platform-agnostic C Micro-Kernel for UAV flight control systems. Developed as an evolution of a university final project, focusing on clarity, modular design, and flexible hardware abstraction.

![Project Status](https://img.shields.io/badge/Project_Status-TRL3-blue)

[![Static Analysis](https://github.com/AritzElge/ATOP/actions/workflows/static_analysis.yml/badge.svg)](https://github.com/AritzElge/ATOP/actions/workflows/static_analysis.yml)

[![STM32 Build](https://github.com/AritzElge/ATOP/actions/workflows/stm32_build.yml/badge.svg)](https://github.com/AritzElge/ATOP/actions/workflows/stm32_build.yml)

## Table of Contents
- [Purpose & Scope](#purpose-&-scope)
- [Features](#features)
- [Architectural Philosophy](#architectural-philosophy)
- [Getting Started](#getting-started)
- [Documentation](#documentation)
- [License](#license)

## Purpose & Scope

This repository represents **Version 2 (v2)** of the control system developed during my Bachelor's Degree Final Project in Industrial and Automatic Electronic Engineering.

*   **v1 (Thesis Project):** A monolithic, baremetal firmware developed for Arduino, focused on validating core flight algorithms. You can review the original work [here](https://addi.ehu.es/handle/10810/53462).
*   **v2 (Current Micro-kernel):** Refactored as a 5-layer agnostic library to solve the hardware-locking issues of v1, allowing for cross-platform deployment and advanced simulation.

## Features

*   **Core Flight Dynamics**: Implements key algorithms for orientation estimation (AHRS) and trajectory stabilization.
*   **Modular Hardware Abstraction Layer (HAL)**: Achieved through function pointers for maximum flexibility and rapid prototyping.
*   **Platform Agnostic**: Easily portable to any system that supports C/C++.
*   **C/C++ Compatibility**: All public headers are wrapped with `extern "C" {}`.

## Architectural Philosophy

### Flexibility vs. Certification Standards

ATOP utilizes a decoupled architecture inspired by modern aerospace frameworks (e.g., NASA’s cFS). By using function pointers for Dependency Injection, we enable high-fidelity Software-In-The-Loop (SITL) testing without code modification.

Safety Standards & MISRA C:2012
While this flexibility requires a formal deviation from MISRA C:2012 (e.g., Rule 11.1), the library implements rigorous mitigation strategies (NULL-pointer validation, redundancy checks, and SEU detection) to ensure reliability. Detailed rationale and compliance matrices can be found in [CODING_STANDARDS.md](./docs/CODING_STANDARDS.md).

## Architecture Layers

```mermaid
graph TD
    subgraph Application_Layer [Application Layer]
        A[main.c <br/> Mission Orchestrator]
    end

    subgraph ATOP_microKernel [ATOP Micro-Kernel]
        subgraph Service_Layer [Service Layer]
            direction LR
            B1[atop] ~~~ B2[PID]
        end
        subgraph Device_Abstraction_Layer [Device Abstraction Layer]
            direction LR
            C1[imu_Interface] ~~~ C2[servo_Interface] ~~~ C3[gnss_Interface] ~~~ C4[waypoint_interface] ~~~ C5[Orientation_interface] 
        end
    end

    subgraph HAL_Layer [Hardware Abstraction Layer]
        direction LR
        D1[I2C/SPI Drivers] ~~~ D2[PWM Drivers] ~~~ D3[UART Drivers]
    end

    subgraph Physical_Layer [Physical Layer]
        E[Target MCU <br/> Sensors <br/> Actuators]
    end

    %% --- LOGICAL CONNECTIONS (Node-to-Node) ---

    %% Mission Flow: App uses Library Services
    Application_Layer --> Service_Layer
    
    %% Internal Coupling: Services use Abstraction Interfaces
    Service_Layer ---> Device_Abstraction_Layer
    
    %% Hardware Configuration: App initializes Drivers
    Application_Layer --> HAL_Layer
    
    %% Silicon Execution: Drivers interact with MCU
    HAL_Layer --> Physical_Layer

    %% Interface Binding: User links Interfaces with real HAL Drivers
    Device_Abstraction_Layer -. "bind" .-> HAL_Layer

    %% Services (Deep Blue)
    style B1 fill:#0D47A1,stroke:#002171,color:#fff
    style B2 fill:#0D47A1,stroke:#002171,color:#fff

    %% Interf. (Deep Green)
    style C1 fill:#1B5E20,stroke:#003308,color:#fff
    style C2 fill:#1B5E20,stroke:#003308,color:#fff
    style C3 fill:#1B5E20,stroke:#003308,color:#fff
    style C4 fill:#1B5E20,stroke:#003308,color:#fff
    style C5 fill:#1B5E20,stroke:#003308,color:#fff

    %% Hardware/HAL: Steel Grey
    style D1 fill:#37474F,stroke:#102027,color:#fff
    style D2 fill:#37474F,stroke:#102027,color:#fff
    style D3 fill:#37474F,stroke:#102027,color:#fff
    style E fill:#263238,stroke:#000a12,color:#fff

    %% --- LAYER STYLES ---
    style Application_Layer fill:#424242,stroke:#212121,stroke-width:2px,color:#fff
    style ATOP_microKernel fill:#002171,stroke:#1E88E5,stroke-width:2px,stroke-dasharray: 5 5,color:#fff
    style Service_Layer fill:#1565C0,stroke:#0D47A1,stroke-width:1px,color:#fff
    style Device_Abstraction_Layer fill:#2E7D32,stroke:#1B5E20,stroke-width:1px,color:#fff
    style HAL_Layer fill:#546E7A,stroke:#37474F,stroke-width:1px,color:#fff
    style Physical_Layer fill:#37474F,stroke:#263238,stroke-width:1px,color:#fff
```
*The dashed 'bind' line represents the functional dependency injection. This decoupled interface ensures that the flight-critical logic (ATOP Library) remains bit-identical across different hardware targets and simulation environments.*

## Data Flow Diagram

```mermaid
graph LR
    A[IMU] --> |Accel, Gyro and Magnetometer data| B[MicroKernel]
    C[GNSS] --> |GNSS Position and speed vector| B
    B --> |Accel, Gyro and Magnetometer data| D[Orientation Filter]
    D --> |Current orientation| E[Data Logger]
    D --> |Current Orientation| G[Orientation Control Loop]
    G --> H[PID]
    H --> F[Surface Control Actuators]   
    B --> |GNSS Position and speed vector| I[Trayectory Control Loop]
    I --> |Setpoint Generation| G
    J[Mission Planner] --> |Waypoint| B
    B --> |Accel data| G
    B --> |Collected data| E
```

### Dependency Injection Flow
```mermaid
graph LR
    A[User HAL/DAL] -->|Function Pointers Dependancy Injection| B[MicroKernel Configuration]
    B --> C[MicroKernel]   
```

## Development Roadmap

| Version | Milestone                          | TRL   |
|--------|------------------------------------|-------|
| v0.1.0 | Architectural Baseline             | TRL 3–4 |
| v0.2.0 | Core Flight Logic Implementation   | TRL 4–5 |
| v0.3.0 | SITL Integration                   | TRL 5–6 |
| v0.4.0 | HITL on STM32                      | TRL 6–7 |
| v1.0.0 | Operational Validation (UAV Flight)| TRL 7   |

> ✅ Current phase: Interfaze Implementation (→ v0.1.0)  
> 🎯 Next milestone: Interfaze Implemented (Architecture Baseline)

## Getting Started

### Prerequisites

A C compiler and a target microcontroller environment (e.g., Arduino IDE, STM32CubeIDE) are required.

### Building and Usage

Please refer to the [Build & Deployment Guide](./docs/deployment/build_guide.md) for detailed toolchain setup, MCU porting instructions, and binary reproducibility.

## 📖 Engineering Documentation Portal

A comprehensive suite of documentation following aerospace standards is available in the [docs/](./docs/) directory:
- [Quick Start: Build Guide](./docs/deployment/build_guide.md)
- [Safety & Risk Analysis](./docs/safety/risk_fmea.md)
- [Architecture Overview](./docs/architecture.md)

## License

This project is licensed under the [MIT License](LICENSE).

---
