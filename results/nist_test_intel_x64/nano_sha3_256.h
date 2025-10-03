// nano_sha3_256.h - C API for nano-sha3-256 static library
// Minimal header for smoke testing and C integration

#ifndef NANO_SHA3_256_H
#define NANO_SHA3_256_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Single-call SHA3-256 hash function
// @param out: output buffer (must be 32 bytes)
// @param input: input data to hash
// @param len: length of input data in bytes
void nano_sha3_256(uint8_t *out, const uint8_t *input, size_t len);

#ifdef __cplusplus
}
#endif

#endif // NANO_SHA3_256_H