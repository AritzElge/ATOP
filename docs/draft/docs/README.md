# 📚 Atop Documentation Portal

Welcome to the technical documentation suite for the Atop flight control micro-kernel. This project is architected for mission-critical UAV applications, prioritizing determinism, hardware abstraction, and safety-critical compliance.

## Documentation Index

### 1. Fundamentals & Design
*   **[System Architecture](./architecture.md)**: Detailed 5-layer abstraction model, functional decoupling, and Mermaid diagrams.
*   **[Requirements Specification](./requirements.md)**: Functional promises and non-functional constraints (determinism, WCET, and memory).

### 2. Safety & Reliability (RAMS)
*   **[Coding Standards](./standards/CODING_STANDARDS.md)**: Compliance with **NASA Power of 10** and documented **MISRA C:2012** deviations.
*   **[Risk Analysis (FMEA)](./safety/risk_fmea.md)**: Identification of failure modes and technical mitigations for flight-critical loops.
*   **[Error Handling Strategy](./safety/error_handling.md)**: Defensive programming, **SEU** (Single Event Upset) detection, and redundancy checks.

### 3. Verification & Validation (V&V)
*   **[Test Plan](./tests/test_plan.md)**: Multi-stage verification strategy including **SITL** (Software-In-The-Loop) and **HITL** (Hardware-In-The-Loop).
*   **[External Libraries (SOUP)](./external_libs.md)**: Justification and risk assessment of Software of Unknown Pedigree (Standard Headers and Math Libs).

### 4. Integration & Deployment
*   **[HAL Interface Contract](./deployment/hal_interface.md)**: Technical specification for MCU peripheral integration via functional dependency injection.
*   **[Build & Toolchain Guide](./deployment/build_guide.md)**: Instructions for reproducible builds, optimization flags, and **Binary Identity** verification.

## 🛠️ Design Philosophy
**Atop** is built on the principle of **Hardware Agnosticism**. By decoupling the flight control loops from the MCU registers through functional dependency injection, the library ensures:
1. **Portability:** Seamless transition between different ARM Cortex-M targets (e.g., STM32L4).
2. **Testability:** The ability to mock the entire hardware layer for high-fidelity PC simulation.
3. **Stability:** Protection against runtime environment failures through strict static allocation and redundancy checks.