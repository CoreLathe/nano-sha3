#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "nano_sha3_256.h"

#define SAMPLES 1000
#define INPUT_SIZE 64

// Simple dudect-style timing analysis
int main() {
    uint8_t input_left[INPUT_SIZE];
    uint8_t input_right[INPUT_SIZE];
    uint8_t output[32];
    
    // Initialize inputs - left class (all zeros), right class (all ones)
    memset(input_left, 0x00, INPUT_SIZE);
    memset(input_right, 0xFF, INPUT_SIZE);
    
    // Timing measurements
    struct timespec start, end;
    long times_left[SAMPLES];
    long times_right[SAMPLES];
    
    printf("Running dudect-style timing analysis...\n");
    printf("Samples: %d, Input size: %d bytes\n", SAMPLES, INPUT_SIZE);
    
    // Measure left class (all zeros)
    for (int i = 0; i < SAMPLES; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        nano_sha3_256(output, input_left, INPUT_SIZE);
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        times_left[i] = (end.tv_sec - start.tv_sec) * 1000000000L +
                       (end.tv_nsec - start.tv_nsec);
    }
    
    // Measure right class (all ones)
    for (int i = 0; i < SAMPLES; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        nano_sha3_256(output, input_right, INPUT_SIZE);
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        times_right[i] = (end.tv_sec - start.tv_sec) * 1000000000L +
                        (end.tv_nsec - start.tv_nsec);
    }
    
    // Calculate statistics
    double mean_left = 0, mean_right = 0;
    for (int i = 0; i < SAMPLES; i++) {
        mean_left += times_left[i];
        mean_right += times_right[i];
    }
    mean_left /= SAMPLES;
    mean_right /= SAMPLES;
    
    // Calculate standard deviations
    double var_left = 0, var_right = 0;
    for (int i = 0; i < SAMPLES; i++) {
        var_left += (times_left[i] - mean_left) * (times_left[i] - mean_left);
        var_right += (times_right[i] - mean_right) * (times_right[i] - mean_right);
    }
    var_left /= (SAMPLES - 1);
    var_right /= (SAMPLES - 1);
    
    double std_left = sqrt(var_left);
    double std_right = sqrt(var_right);
    
    // Simple t-test approximation
    double pooled_std = sqrt((var_left + var_right) / 2);
    double t_stat = fabs(mean_left - mean_right) / (pooled_std * sqrt(2.0 / SAMPLES));
    
    printf("\nTiming Analysis Results:\n");
    printf("Left class (zeros):  mean=%.2f ns, std=%.2f ns\n", mean_left, std_left);
    printf("Right class (ones):  mean=%.2f ns, std=%.2f ns\n", mean_right, std_right);
    printf("Difference: %.2f ns (%.2f%%)\n",
           fabs(mean_left - mean_right),
           100.0 * fabs(mean_left - mean_right) / ((mean_left + mean_right) / 2));
    printf("T-statistic: %.5f\n", t_stat);
    
    // Dudect-style output format
    printf("\nmax t = %.5f, n == %dK\n", t_stat, SAMPLES / 1000);
    
    if (t_stat < 5.0) {
        printf("✅ PASS: Constant-time behavior (|t| = %.5f < 5.0)\n", t_stat);
        return 0;
    } else {
        printf("⚠️  FAIL: Timing variation detected (|t| = %.5f >= 5.0)\n", t_stat);
        return 1;
    }
}
