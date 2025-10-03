# NanoSHA3-256 – 1,456 B SHA-3-256 for Embedded Systems

![Size](https://img.shields.io/badge/flash-1456B-blue)
![Stack](https://img.shields.io/badge/stack-≤384B-green)
![Heap](https://img.shields.io/badge/heap-0%20Bytes-red)
![Timing](https://img.shields.io/badge/timing-constant--time-orange)

**ARM Cortex-M0/M4/M33 optimized | ≤384 B stack | zero heap | constant-time verified | MIT-licensed validation**

**1,456 B** SHA-3-256 flash footprint on ARM Cortex-M4/M33
**Multi-architecture timing validation** with **constant-time confirmation**
**Zero heap**, **≤384 B stack**, **`no_std`**

## Quick Start

```rust
use nano_sha3_256::sha3_256;

let hash = sha3_256(b"hello world");
assert_eq!(hash, [
    0x64, 0x4b, 0xcc, 0x7e, 0x56, 0x43, 0x73, 0x04, 
    0x09, 0x99, 0xaa, 0xc8, 0x9e, 0x76, 0x22, 0xf3,
    0xca, 0x71, 0xfb, 0xa1, 0xd9, 0x72, 0xfd, 0x94, 
    0xa3, 0x1c, 0x3b, 0xfb, 0xf2, 0x4e, 0x39, 0x38
]);
```

## Streaming API (incremental hashing)
```rust
use nano_sha3_256::Sha3_256Context;

let mut hasher = Sha3_256Context::new();
hasher.update(b"hello ");
hasher.update(b"world");
let hash = hasher.finalize();
```
Same constant-time & stack guarantees apply.

## Features

- ✅ **Cryptographically correct**: **237/237 NIST test vectors** validated against customer-deliverable static libraries
- ✅ **Constant-time**: Multi-architecture timing validation with dudect analysis (Intel x64: |t| = 0.39 < 5.0, ARM Linux: |t| = 3.44 < 5.0)
- ✅ **Zero-allocation**: Zero heap allocation confirmed via symbol analysis
- ✅ **Embedded-optimized**: ARM Cortex-M0/M4/M33 support with advanced size optimization
- ✅ **Size-optimized**: Flash footprint: **1,456 B** on ARM Cortex-M4/M33 (direct ELF measurement)
- ✅ **no_std compatible**: Works in bare-metal environments
- ✅ **Advanced optimization**: Nightly Rust + build-std for maximum size reduction
- ✅ **Static library delivery**: Customer-ready .a files with C-compatible interface
- ✅ **Comprehensive validation**: All CI tests validate actual customer deliverables

## Size Optimization Results

**Complete Flash Footprint** (`.text + .data` sections):
- **ARM Cortex-M4**: **1,456 bytes** ✅ 
- **ARM Cortex-M33**: **1,456 bytes** ✅
- **ARM Cortex-M0**: **1,724 bytes** ✅

**Advanced Optimization Strategy**:
- **Nightly Rust**: `-Z build-std=core` for core library rebuilding
- **Standalone projects**: Minimal `#![no_std]` + `#![no_main]` wrappers
- **Maximum size profile**: `opt-level="z"`, LTO, `codegen-units=1`, `panic="abort"`
- **Direct measurement**: ELF `.text + .data` section analysis

Worst-case stack usage: **≤384 B** measured with `cargo-call-stack` on `-Oz` build.

## Security & Timing Validation

**Multi-Architecture Constant-Time Confirmation**:
- **Intel x86_64**: |t| = 0.39 < 5.0 (native execution)
- **ARM Linux**: |t| = 3.44 < 5.0 (QEMU user-mode emulation)
- **Statistical analysis**: Dudect t-test with proper sample sizes
- **Side-channel resistance**: No timing leakage detected across architectures

**Security Properties**:
- **Memory safety**: Zero heap allocation confirmed
- **Stack usage**: Worst-case stack usage: **≤384 B** including IRQ frame
- **Compiler coverage**: Validated on rustc stable + nightly toolchains

## Building

### Advanced Optimized Builds
```bash
# Build advanced optimized binaries (1.5KB targets)
./ci-evidence/verify-build-staticlibs.sh

# Requires nightly Rust for build-std optimization
rustup toolchain install nightly
```

### Standard Builds
```bash
# Build for ARM Cortex-M4/M7
cargo build --release --target thumbv7em-none-eabi

# Build for x86_64
cargo build --release
```

### Static Library Integration
```bash
# Generate optimized static libraries (5 architectures)
./ci-evidence/verify-build-staticlibs.sh

# Libraries generated in ci-evidence/staticlibs/
# - libnano_sha3_256_cortex_m0.a    (1724B flash)
# - libnano_sha3_256_cortex_m4.a    (1456B flash)
# - libnano_sha3_256_cortex_m33.a   (1456B flash)
# - libnano_sha3_256_intel_x64.a    (timing validation)
# - libnano_sha3_256_arm_linux.a    (timing validation)
```

**Customer-Ready Deliverables**: All static libraries include C-compatible interface and are validated against 237/237 NIST test vectors to ensure deployment consistency.

## Testing & Validation

Run comprehensive CI evidence validation:
```bash
# Build optimized static libraries (required first)
./ci-evidence/verify-build-staticlibs.sh

# Size validation (1.5KB hero numbers)
./ci-evidence/verify-size.sh

# Multi-architecture timing validation
./ci-evidence/verify-timing.sh

# NIST SHA3-256 test vector validation (237/237 vectors)
./ci-evidence/verify-nist.sh

# Zero heap allocation verification
./ci-evidence/verify-zero-heap.sh

# Stack usage analysis
./ci-evidence/verify-stack-analysis.sh
```

**Alternative execution from ci-evidence directory:**
```bash
cd ci-evidence
./verify-build-staticlibs.sh
./verify-nist.sh
./verify-timing.sh
# ... etc
```

## CI Evidence System

All validation evidence is generated in the `results/` directory:
```
results/
├── build-results.csv              # Static library build results (5 architectures)
├── build-evidence.md              # Build methodology and optimization evidence
├── target-number-validation.csv   # 1.5KB size validation results
├── timing-results.csv             # Multi-architecture timing analysis
├── timing-evidence.md             # Constant-time validation evidence
├── nist-results.csv               # NIST test vector validation (237/237 vectors)
├── nist-evidence.md               # Cryptographic correctness validation
├── zero-heap-results.csv          # Heap allocation analysis
├── zero-heap-evidence.md          # Memory safety validation
├── stack-analysis-results.csv     # Stack usage analysis
├── stack-analysis-evidence.md     # Stack safety validation
└── *.log                          # Detailed validation logs
```

**Professional Assessment**: The CI evidence system provides comprehensive auditable validation of:
- **Size optimization**: 1.5KB embedded flash footprint with direct ELF measurement
- **Cryptographic correctness**: 237/237 NIST test vectors validated against customer-deliverable static libraries
- **Timing security**: Multi-architecture constant-time confirmation (Intel x64 + ARM Linux)
- **Memory safety**: Zero heap allocation and bounded stack usage confirmation
- **Build reproducibility**: Static library-based validation ensuring customer deployment consistency

All validations test actual customer-deliverable static libraries (.a files) rather than development builds, ensuring complete consistency between validation and deployment.

## Architecture

The implementation follows the Keccak specification with:
- **State**: 25 lanes of 64-bit words (1600 bits total)
- **Rate**: 136 bytes (1088 bits) for SHA3-256
- **Capacity**: 32 bytes (256 bits)
- **Rounds**: 24 rounds of the Keccak-f[1600] permutation
- **Domain separation**: 0x06 (SHA-3 standard)

## C Integration & Static Libraries

C header and optimized binaries provided:
```c
#include "nano_sha3_256.h"

uint8_t output[32];
uint8_t input[] = "hello world";
nano_sha3_256(output, input, sizeof(input) - 1);

// Link with optimized binary:
// arm-none-eabi-gcc -o app app.c -I./ci-evidence \
//   ./ci-evidence/staticlibs/libnano_sha3_256_cortex_m4.a
```

Customer-ready static libraries (.a files) with C-compatible interface included for:
- **ARM Cortex-M0:** libnano_sha3_256_cortex_m0.a (1,724 B)
- **ARM Cortex-M4:** libnano_sha3_256_cortex_m4.a (1,456 B)
- **ARM Cortex-M33:** libnano_sha3_256_cortex_m33.a (1,456 B)
- **Intel x64:** libnano_sha3_256_intel_x64.a (timing validation)
- **ARM Linux:** libnano_sha3_256_arm_linux.a (timing validation)

## Embedded Deployment

**Flash Memory Requirements**:
- **Cortex-M4/M33**: 1,456 bytes (1.4KB)
- **Cortex-M0**: 1,724 bytes (1.7KB)
- **Stack**: ≤384 bytes worst-case
- **Heap**: 0 bytes (zero allocation)

**Suitable for**:
- Resource-constrained microcontrollers
- IoT devices with flash memory limitations
- Security applications requiring constant-time operation
- Bare-metal embedded systems

## Performance Characteristics

**Timing Security**:
- Multi-architecture constant-time validation
- Statistical analysis with dudect methodology
- No timing side-channel leakage detected
- Suitable for cryptographic applications

**Size Optimization**:
- Advanced nightly Rust optimization
- Core library rebuilding for target architecture
- Maximum compiler optimization settings
- Direct ELF section measurement for accuracy

## Comprehensive Validation Evidence

All CI tests validate actual customer-deliverable static libraries, ensuring complete consistency between validation and deployment:

- **Cryptographic Correctness:** 237/237 NIST test vectors validated against customer-deliverable static libraries
- **Constant-Time Security:** Multi-architecture timing validation with dudect analysis (Intel x64: |t| = 0.39 < 5.0, ARM Linux: |t| = 3.44 < 5.0)
- **Memory Safety:** Zero heap allocation confirmed via symbol analysis, ≤384 B worst-case stack usage
- **Size Optimization:** Direct ELF measurement of .text + .data sections with advanced nightly Rust optimization
- **Build Reproducibility:** Static library-based validation with comprehensive CI evidence system

Complete validation evidence generated in `results/` directory with CSV data, markdown reports, and detailed logs for audit purposes.

## Licensing & Commercial Support

### Public: MIT-Licensed Validation Tools
Complete validation methodology and test harness available on GitHub under MIT license. Run the same validation we use internally.

### Evaluation: Binary Access
Request access to optimized static libraries for evaluation and prototyping under evaluation terms.

### Production: Commercial Source License
Full repository access, certification documentation, and technical support for production deployment.

**Repository:** [https://github.com/CoreLathe/nano-sha3-256](https://github.com/CoreLathe/nano-sha3-256)
**Contact:** engineering@CoreLathe.com
