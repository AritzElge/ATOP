# ATOP Coding Standards

This document outlines the coding practices and standards used in the ATOP project.

## Hardware Abstraction Layer (HAL) Design

The ATOP library uses function pointers to register hardware-specific driver functions at runtime. This provides a highly flexible and platform-agnostic interface, allowing users to easily adapt the library to different microcontrollers (e.g., Arduino, STM32, ESP32).

### Example Interface (IMU)

The interface relies on type definitions and pointers storing functions:

```c
// Function Types
typedef _Bool (*imu_start)(void);
typedef _Bool (*get_imu_accel)(float* accelOX, float* accelOY, float* accelOZ);
// ... other typedefs ...

// Pointer storing functions
_Bool set_imu_accelFunction(get_imu_accel fptr);
// ...

### MISRA C Compliance Statement
Due to the use of function pointers, ATOP does not comply with the MISRA C:2012 guidelines. Specifically, this design violates rules such as:
* **Rule 1.1 (Required):** Restrictions on the use of certain language features that can compromise safety.

### Note for Safety-Critical Applications
If this library were to be deployed in a safety-critical aerospace environment requiring certification (e.g., DO-178C or equivalent), the HAL architecture would need to be refactored to use a static, table-based approach or dependency injection via structs, eliminating function pointers entirely.