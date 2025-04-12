/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 spekie
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>
#include <time.h>

#define ARRAY_MIN (1024)
#define ARRAY_MAX (4096*4096)
#define NUM_PRIMES (100000)

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

double get_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void benchmark_primes() {
    int primes_found = 0;
    int num = 2;
    double start_time = get_seconds();

    while (primes_found < NUM_PRIMES) {
        if (is_prime(num)) {
            primes_found++;
        }
        num++;
    }
    double end_time = get_seconds();
    double elapsed_time = end_time - start_time;
    printf("Time took to find %d numbers: %f seconds\n", NUM_PRIMES, elapsed_time);
    printf("Avg time per number: %f ms\n", (elapsed_time * 1000) / NUM_PRIMES);
}

int main() {
    printf("Calculating prime numbers...\n");
    benchmark_primes();
    return 0;
}
