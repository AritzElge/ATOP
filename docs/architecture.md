## System Architecture: ATOP 

### 1. Architectural Overview

The ATOP (Advanced Technology Operations Platform) library is designed following a strictly decoupled layered architecture. This ensures high reliability and hardware agnosticism, critical for long-term space missions where hardware components might be replaced or upgraded between mission phases.

### 2. Design Philosophy

- **Separation of Concerns:** The Service Layer possesses no knowledge of the underlying hardware; it only operates on standardized data structures.
- **Static Memory Allocation:** To ensure mission safety, the library avoids dynamic memory allocation (malloc), preventing heap fragmentation in long-running flight software.

### 3. Layer Definitions


```mermaid
graph TD
    subgraph Application_Layer [Application Layer]
        A[main.c <br/> Mission Orchestrator]
    end

    subgraph ATOP_Library [ATOP Library]
        subgraph Service_Layer [Service Layer]
            direction LR
            B1[atop] ~~~ B2[PID] ~~~ B3[Orientation_filter]
        end
        subgraph Device_Abstraction_Layer [Device Abstraction Layer]
            direction LR
            C1[imu_Interface] ~~~ C2[servo_Interface] ~~~ C3[gnss_Interface] ~~~ C4[waypoint_interface]
        end
    end

    subgraph HAL_Layer [Hardware Abstraction Layer - HAL]
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
    style B3 fill:#0D47A1,stroke:#002171,color:#fff

    %% Interf. (Deep Green)
    style C1 fill:#1B5E20,stroke:#003308,color:#fff
    style C2 fill:#1B5E20,stroke:#003308,color:#fff
    style C3 fill:#1B5E20,stroke:#003308,color:#fff
    style C4 fill:#1B5E20,stroke:#003308,color:#fff

    %% Hardware/HAL: Steel Grey
    style D1 fill:#37474F,stroke:#102027,color:#fff
    style D2 fill:#37474F,stroke:#102027,color:#fff
    style D3 fill:#37474F,stroke:#102027,color:#fff
    style E fill:#263238,stroke:#000a12,color:#fff

    %% --- LAYER STYLES ---
    style Application_Layer fill:#424242,stroke:#212121,stroke-width:2px,color:#fff
    style ATOP_Library fill:#002171,stroke:#1E88E5,stroke-width:2px,stroke-dasharray: 5 5,color:#fff
    style Service_Layer fill:#1565C0,stroke:#0D47A1,stroke-width:1px,color:#fff
    style Device_Abstraction_Layer fill:#2E7D32,stroke:#1B5E20,stroke-width:1px,color:#fff
    style HAL_Layer fill:#546E7A,stroke:#37474F,stroke-width:1px,color:#fff
    style Physical_Layer fill:#37474F,stroke:#263238,stroke-width:1px,color:#fff
```
*The dashed 'bind' line represents the functional dependency injection. This decoupled interface ensures that the flight-critical logic (ATOP Library) remains bit-identical across different hardware targets and simulation environments.*

#### 3.1 Application Layer

The Mission Orchestrator (main.c). It is responsible for:

- Initializing the Hardware Abstraction Layer (HAL).
- Injecting hardware-specific drivers into the ATOP Interfaces (Binding).
- Managing the high-level mission state machine.

#### 3.2 Service Layer (Core ATOP)

The "brain" of the system. It processes raw data into actionable knowledge:
- **Orientation Filter:** Implementation of the Madgwick/Mahony algorithms.
- **PID Controller:** Precision closed-loop control for actuators.
- **Quaternion Engine:** Mathematical utilities for 3D rotations.

#### 3.3 Device Abstraction Layer (DAL)
A set of Interface Contracts. It defines the "what" but not the "how".

Example: imu_interface expects a standardized acceleration vector, regardless of whether the physical sensor is an MPU6050 or a high-grade radiation-hardened IMU.

#### 3.4 Hardware Abstraction Layer (HAL)
The bridge between software and silicon. These are the specific drivers provided by the user or the MCU manufacturer (e.g., STM32 HAL, ESP-IDF, or bare-metal registers).

### 4. Integration  (Binding Process)
To maintain the decoupling shown in the diagram, the user must perform a Functional Binding at startup
