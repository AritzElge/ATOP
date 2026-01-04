# Build & Compilation Guide

This guide describes how to compile the `Atop` library and its examples for both simulation (SITL) and target MCU deployment.

## 1. Prerequisites
To maintain **Binary Identity** and reproducibility, the following toolchain is recommended:
*   **Compiler**: `arm-none-eabi-gcc` (Version 12.x or higher recommended).
*   **Build System**: [CMake](cmake.org) (minimum 3.15).
*   **Analysis Tools**: `cppcheck` and `clang-format`.

## 2. Compilation for Target MCU (STM32L476RG)
The library is optimized for ARM Cortex-M4 architectures.

### Optimization Flags
To ensure determinism and safety, the following flags are used:
*   `-ffunction-sections -fdata-sections`: To enable Dead Code Elimination (Linker).
*   `-fno-exceptions -fno-rtti`: To disable C++ overhead.
*   `-Wall -Wextra -Wpedantic`: To enforce strict ISO C compliance.
*   `-O2` or `-Os`: Optimized for a balance between speed and footprint.

### Build Command
```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-stm32.cmake ..
make -j4
```
## 3. Compilation for Simulation (SITL)
To run the library on a host PC (Linux/macOS) for logic validation:

```bash
cmake -DATOP_SITL=ON ..
make
```

## 4. Binary Identity Verification
After compilation, it is recommended to generate a SHA-256 hash of the .bin or .elf file. This ensures that the binary deployed in the UAV is the exact same copy that was validated during the HITL phase.

```bash
sha256sum atop_flight_core.bin
```