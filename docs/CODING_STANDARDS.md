## Coding Standards & Safety

The **atop** library is developed with a focus on reliability, determinism, and maintainability, adhering to industry-recognized standards for safety-critical embedded systems and aerospace applications.

### 🚀 NASA/JPL Standards Compliance
The core architecture of the library follows the **NASA/JPL Power of 10 Rules** and the **JPL Institutional Coding Standard** to ensure high-integrity flight software:
*   **Static Memory Allocation:** The system strictly avoids dynamic memory allocation (`malloc`/`free`). All memory requirements are determined at compile-time to guarantee determinism and prevent heap exhaustion (Rule 3).
*   **Assertion-Driven Verification:** Static and runtime assertions are extensively used to verify system invariants, data integrity, and architectural assumptions (Rule 5).
*   **Encapsulation and Scope Control:** Strict file-level visibility is enforced through the use of the `static` specifier, minimizing the risk of unintended side effects and global namespace pollution.

### 🛡️ MISRA C Deviations
While the project strives for MISRA C compliance, certain architectural deviations are documented and justified to support advanced verification workflows:

*   **Rule 11.1 (Function Pointers):** The library utilizes **Dependency Injection via Function Pointers** to decouple high-level flight control logic from low-level hardware-specific implementations.
    *   *Justification:* This design choice enables **Software-In-The-Loop (SITL)** and **Hardware-In-The-Loop (HITL)** testing. It allows the same core logic to be validated in simulation environments without modifying the library's source code.
    *   *Risk Mitigation:* All function pointers undergo validation against `NULL` prior to execution. Furthermore, the architecture ensures that driver registration is restricted to the system initialization phase.

### 🛠️ Build Configuration & Determinism
The project employs conditional compilation and a modular build system to ensure that the flight binary remains optimized and free of dead code:
*   **Component Segregation:** Testing-specific libraries and transport layers (e.g., HITL UART modules) are excluded from production builds through preprocessor directives.
*   **Footprint Optimization:** The final binary size is minimized for resource-constrained targets by including only the necessary dependencies for the selected hardware profile.
*   **Consistent Behavior:** The architecture ensures that the flight control logic remains identical between simulation (SITL/HITL) and real-world deployment, reducing the risk of "it works in the simulator" errors.
