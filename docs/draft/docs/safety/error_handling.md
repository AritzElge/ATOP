# Error Handling and Reliability Strategy

## Design Philosophy
The `Atop` library adopts a **Defensive Programming** approach tailored for mission-critical environments. The primary objective is to detect data integrity failures before they propagate into the flight control loop.

## Interface Integrity Verification
A **Post-Write Redundancy Check** is implemented during the configuration of critical function pointers (callbacks).

### Technical Implementation
```c
stored_get_imu_accel = fptr;
// Redundant Check for hardware/memory integrity
if (stored_get_imu_accel != fptr) {
    ret_val = false; 
}
``` 
## Engineering Rationale
1. SEU (Single Event Upset) Detection: In high-radiation environments, a bit-flip may occur in SRAM during the write operation. This check detects bus noise or memory cell corruption. Critical pointers are often declared as volatile to ensure the compiler does not optimize away redundancy checks, guaranteeing that the memory cell is physically read back.
2. Deterministic Failure Management: The system favors explicit return codes (bool/enum) over assert() to prevent unrecoverable system hangs, allowing the application to transition into a Safe Mode state.
3. Validation of Connectivity: Ensures that the link between the Agnostic Library and the Hardware Port is verified during initialization.

### Determinism and Timing Predictability
To ensure a strictly bounded **Worst-Case Execution Time (WCET)**—a prerequisite for orbital flight control—the `Atop` library adheres to the following constraints:

1. **Zero Exception Policy**: Although compatible with C++, the use of `try-catch` blocks and exception throwing is strictly prohibited. This eliminates the non-deterministic overhead of stack unwinding and ensures the binary remains lightweight and predictable.
2. **No Non-Local Jumps**: The use of `setjmp` or `longjmp` is avoided to maintain a linear and traceable stack execution flow, facilitating static analysis and stack depth verification.
3. **Static Allocation**: To prevent heap fragmentation and non-deterministic `malloc()` latencies (which can lead to mission-ending OOM errors), all memory requirements are resolved at compile-time or through fixed-size static buffers.