#include <stdio.h>
#include <time.h>

const int tin = 98765432;
const int iterations = 1000000;

int sum(int n) {
    if (n < 10) return n;
    int total = 0;
    while (n > 0) {
        total += n % 10;
        n /= 10;
    }
    return sum(total);
}

int main() {
    int temp = tin;
    const int its = iterations;
    int res = 0;

    clock_t start, end;
    double duration;

    // ------------------ Recursive ------------------
    start = clock();

    for (int i = 0; i < its; ++i) {
        res += sum(temp);
    }

    end = clock();
    duration = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

    printf("Checksum: %d\n", res);
    printf("Execution Time Recursive: %.3f ms\n", duration);

    // ------------------ Iterative ------------------
    res = 0;
    start = clock();

    for (int i = 0; i < its; ++i) {
        int temptemp = temp;
        while (temptemp >= 10) {
            int total = 0;
            while (temptemp > 0) {
                total += temptemp % 10;
                temptemp /= 10;
            }
            temptemp = total;
        }
        res += temptemp;
    }

    end = clock();
    duration = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

    printf("Checksum: %d\n", res);
    printf("Execution Time Iterative: %.3f ms\n", duration);

    // ------------------ Formula ------------------
    res = 0;
    start = clock();

    for (int i = 0; i < its; ++i) {
        res += (1 + (temp - 1) % 9);
    }

    end = clock();
    duration = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

    printf("Checksum: %d\n", res);
    printf("Execution Time Formula: %.3f ms\n", duration);

    return 0;
}
