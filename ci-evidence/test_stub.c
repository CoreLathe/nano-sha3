// Minimal C test stub to verify linking and measure actual code size
// This ensures all symbols are kept by referencing the main API

#include "nano_sha3_256.h"
#include <stddef.h>

// Force linker to keep all symbols by referencing the main function
int main(void) {
    // Call the SHA3-256 function with dummy parameters to prevent dead-code elimination
    unsigned char output[32];
    unsigned char input[1] = {0};
    nano_sha3_256(output, input, sizeof(input));
    
    return 0;
}