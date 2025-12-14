# ATOP: Aeronautic Trajectory and Orientation Processor

An educational, platform-agnostic C library for UAV flight control systems. Developed as an evolution of a university final project, focusing on clarity, modular design, and flexible hardware abstraction.

![Project Status](https://img.shields.io/badge/Project_Status-WIP-blue)
[![Static Analysis](https://github.com/AritzElge/ATOP/actions/workflows/static_analysis.yml/badge.svg)](https://github.com/AritzElge/ATOP/actions/workflows/static_analysis.yml)

## Table of Contents
- [Purpose & Scope](#purpose-&-scope)
- [Features](#features)
- [Architectural Philosophy](#architectural-philosophy)
- [Getting Started](#getting-started)
- [Documentation](#documentation)
- [License](#license)

## Purpose & Scope

This repository originates from my Bachelor's Thesis in Aerospace Engineering and is primarily intended for **educational purposes**. The main objective is to demonstrate robust architectural patterns for separating core flight control logic from platform-specific hardware interactions (e.g., IMU, GPS, Servos).

The design prioritizes flexibility and ease of integration across various development boards (like Arduino or generic microcontrollers) over strict certification standards, making it an ideal learning resource.

## Features

*   **Core Flight Dynamics**: Implements key algorithms for orientation estimation (AHRS) and trajectory stabilization.
*   **Modular Hardware Abstraction Layer (HAL)**: Achieved through function pointers for maximum flexibility and rapid prototyping.
*   **Platform Agnostic**: Easily portable to any system that supports C/C++.
*   **C/C++ Compatibility**: All public headers are wrapped with `extern "C" {}`.

## Architectural Philosophy

### Flexibility vs. Certification Standards

The Hardware Abstraction Layer (HAL) architecture utilizes function pointers extensively to allow users to "inject" their specific hardware drivers at runtime.

**ATOP is not compliant with safety standards such as MISRA C:2012.**

Specifically, the use of function pointers violates rules intended to prevent runtime errors in safety-critical systems (e.g., **MISRA C:2012 Rule 1.1**).

This design choice highlights a crucial engineering trade-off: maximizing flexibility for prototyping/education versus adhering to rigorous certification requirements for commercial aerospace use (e.g., DO-178C). The [CODING_STANDARDS.md](docs/CODING_STANDARDS.md) file details the rationale and the necessary steps to transition this architecture to a static, compliant system if required.

## Getting Started

### Prerequisites

A C compiler and a target microcontroller environment (e.g., Arduino IDE, STM32CubeIDE) are required.

### Building and Usage

Instructions on how to compile the library, configure the hardware abstraction layer using the provided interface functions, and integrate it into a project will be provided here soon in the [docs/](docs/) directory.

## Documentation

Comprehensive diagrams, project specifications, and details on the coding standards will be provided here soon in the [docs/](docs/) directory.

## License

This project is licensed under the [MIT License](LICENSE).

---