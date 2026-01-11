## Coding Standards & Safety

The **atop** library is developed with a focus on reliability, determinism, and maintainability, adhering to industry-recognized standards for safety-critical embedded systems and aerospace applications.

### 🚀 NASA/JPL Standards Compliance
The core architecture of the library follows the **NASA/JPL Power of 10 Rules** and the **JPL Institutional Coding Standard** to ensure high-integrity flight software:
*   **Static Memory Allocation:** The system strictly avoids dynamic memory allocation (`malloc`/`free`). All memory requirements are determined at compile-time to guarantee determinism and prevent heap exhaustion (Rule 3).
*   **No-Recursion Policy:** To ensure a fixed and statically analyzable stack depth, all execution paths are iterative. This prevents stack overflow failures during critical orbital maneuvers (Rule 1).
*   **Assertion-Driven Verification:** Static and runtime assertions are extensively used to verify system invariants, data integrity, and architectural assumptions (Rule 5).
    *   *Note:* For production flight binaries, assertions are complemented by the deterministic error-handling logic defined in `safety/error_handling.md` to prevent unrecoverable system hangs (Rule 5).
*   **Encapsulation and Scope Control:** Strict file-level visibility is enforced through the use of the `static` specifier, minimizing the risk of unintended side effects and global namespace pollution.

### 🚀 Deviation from NASA JPL Rule 9: Function Pointers

**Rule 9 (JPL)**: The use of pointers should be restricted. No more than one level of dereferencing is allowed. Function pointers are not permitted.  
**Deviation**: Function pointers are used for dependency injection in the HAL/DAL interface.

**Justification**:  
This architectural choice enables hardware abstraction, cross-platform testing (SITL/HITL), and decoupled integration, critical for validation in aerospace systems.

**Mitigations**:  
- All function pointers are validated for `NULL` before use.  
- Registration is restricted to initialization; no runtime re-binding.  
- Static analysis enabled (no dynamic dispatch).   

### 🛡️ MISRA C Deviations
While the project strives for MISRA C compliance, certain architectural deviations are documented and justified to support advanced verification workflows:

*   **Rule 11.1 (Function Pointers):** The library utilizes **Dependency Injection via Function Pointers** to decouple high-level flight control logic from low-level hardware-specific implementations.
    *   *Justification:* This design enables **Software-In-The-Loop (SITL)** and **Hardware-In-The-Loop (HITL)** testing, allowing the same core logic to be validated across environments without source modification.
    *   *Risk Mitigation:* 
        1. All function pointers are validated for `NULL` before execution (see `safety/error_handling.md`).
        2. **Locked Initialization:** Callback registration is restricted to the system initialization phase. Once initialized, pointers are immutable.
        3. No dynamic dispatch or runtime re-binding occurs during flight.   

### 🛠️ Build Configuration & Determinism
The project employs conditional compilation and a modular build system to ensure that the flight binary remains optimized and free of dead code:
*   **Component Segregation:** Testing-specific libraries and transport layers (e.g., HITL UART modules) are excluded from production builds through preprocessor directives.
*   **WCET Optimization:** Compilation flags are tuned to ensure a strictly bounded **Worst-Case Execution Time (WCET)**, ensuring the control loop meets its real-time deadlines.
*   **Consistent Behavior:** The architecture ensures that the flight control logic remains identical between simulation (SITL/HITL) and real-world deployment, reducing the risk of "it works in the simulator" errors.

### 📚 External References & Standards

To ensure the highest level of software integrity, this project refers to the following aerospace and safety-critical standards:

*   **NASA/JPL Power of 10 Rules:** A set of 10 rules for safety-critical code development focused on verifiability and transparency. 
    *   [Download/View PDF](https://spinroot.com/gerard/pdf/P10.pdf)
*   **JPL Institutional Coding Standard (JPL D-60411):** The official C coding standard for flight software at the Jet Propulsion Laboratory.
    *   [View Documentation](http://everyspec.com/NASA/NASA-JPL/JPL-D-60411_VER-1_32832/)
*   **NASA C Style Guide (SEL-94-003):** Guidelines from the Goddard Space Flight Center for writing maintainable and readable C code.
    *   [NASA Technical Reports Server (NTRS)](https://ntrs.nasa.gov/citations/19950022400)
*   **MISRA C:2012 Guidelines:** Industry standard for C programming in safety-related systems (Automotive, Aerospace, Medical).
    *   [Official MISRA Website](https://www.misra.org.uk)
*   **Barr Group Embedded C Coding Standard:** A popular industry standard designed to minimize bugs in firmware.
    *   [Access Online Version](https://barrgroup.com)