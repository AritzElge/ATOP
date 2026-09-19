# Failure Mode and Effects Analysis (FMEA)

This document analyzes potential failure modes within the `Atop` micro-kernel library, specifically focusing on the Service and Device Abstraction layers.

## Methodology
- **Failure Mode**: The specific technical malfunction.
- **Effect**: Impact on the flight control loop and mission integrity.
- **Mitigation**: Technical strategy implemented to detect, isolate, or recover from the failure.

## Risk Analysis Table
| ID | Component | Failure Mode | Potential Effect | Implementation Mitigation |
| --- | --- | --- | --- | --- | 
| F001 | Device Abstraction | **Null Function Pointer** during initialization. | System HardFault/Crash upon service execution.	| Mandatory if (callback != NULL) validation gate before every architectural jump. |
| F002 | Hardware Port Link | **Single Event Upset (SEU)** in stored pointers. | Execution of arbitrary code or invalid memory access. | **Post-Write Redundancy Check:** Verification of pointer integrity immediately after SRAM write operations. |
| F003 | Service Layer | **Spontaneous Pointer Decoupling** (Unassigned pointer at runtime).	| Sudden loss of critical telemetry or attitude control. | **State Integrity Heartbeat:** Periodic validation of critical callback vectors against golden images or redundant copies. |
| F004 | HAL / Hardware Layer | Execution Timeout in hardware-bound function. | Violation of Worst-Case Execution Time (WCET), breaking control loop determinism. | Non-blocking design pattern using explicit return codes (ATOP_TIMEOUT) and Watchdog Timer (WDT) integration. |

## Criticality Levels
1. **Catastrophic (F001, F002):** Total loss of spacecraft control. Mitigation is mandatory at the architectural level.
2. **Critical (F003):** Loss of a primary mission function. Requires transition to Safe Mode.
3. **Marginal (F004):** Degraded performance. Managed via retry logic or telemetry reporting.