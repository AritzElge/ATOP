## External Libraries & Dependency Justification (SOUP)

### 1. Policy on External Dependencies
To maintain the highest level of safety and determinism, the Atop library follows a Minimalist Dependency Policy. Every external component must be justified based on its reliability, license, and impact on the Worst-Case Execution Time (WCET).

### 2. Integrated Dependencies
Library	Purpose	Justification
Standard C Library (libc)	Basic types and math functions (stdint.h, math.h).	Industry standard. **Limited to the freestanding subset** to avoid non-deterministic functions.
Unity Test (Development only)	Unit testing framework.	Lightweight, specifically designed for embedded C, and highly portable for SITL.

### 3. Excluded Dependencies (Architectural Decisions)
To comply with NASA/JPL Power of 10 and MISRA C standards, the following have been intentionally excluded:
* **Dynamic Memory (Heap):** Use of <stdlib.h> functions like malloc and free is strictly forbidden within the library core to prevent memory fragmentation and OOM (Out-of-Memory) conditions.
* **Standard Template Library (STL):** Even when compiled with C++ support, the STL is excluded to avoid hidden allocations and non-deterministic execution times.
* **C++ Exceptions/RTTI:** Disabled to maintain a predictable stack and reduce binary footprint.

### 4. Licensing and SOUP Assessment
The Atop library is licensed under the MIT License.
* All integrated components must have compatible permissive licenses (MIT, BSD, Apache 2.0).
* This ensures that commercial NewSpace entities can integrate the library into proprietary flight stacks without licensing conflicts.