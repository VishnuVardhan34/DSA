#include <stdio.h>
#include <stdlib.h>

int getiterations(int max[], int m) {
    int current_max = max[0];
    for (int i = 1; i < m; i++) {
        if (max[i] > current_max) {
            current_max = max[i];
        }
    }
    int j = 0;
    while (current_max != 0) {
        current_max /= 10;
        j++;
    }
    return j;
}

void display(int arr[], int m) {
    for (int i = 0; i < m; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void radixin(int max[], int m, int max_iterations) {
    int exp = 1; // Start with the least significant digit
    int count[10] = {0}; // For counting digits 0–9
    int another[m]; // Temporary array for sorted values

    for (int iter = 1; iter <= max_iterations; iter++) {
        // Reset count array
        for (int i = 0; i < 10; i++) {
            count[i] = 0;
        }

        // Count occurrences of each digit
        for (int i = 0; i < m; i++) {
            int digit = (max[i] / exp) % 10;
            count[digit]++;
        }

        // Calculate cumulative count
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = m - 1; i >= 0; i--) {
            int digit = (max[i] / exp) % 10;
            another[count[digit] - 1] = max[i];
            count[digit]--;
        }

        // Copy the sorted numbers back to the original array
        for (int i = 0; i < m; i++) {
            max[i] = another[i];
        }

        // Display current iteration
        printf("\nIteration %d: ", iter);
        display(max, m);

        // Move to the next digit place
        exp *= 10;
    }
}

int main() {
    int flash;
    printf("Max elements?\n");
    scanf("%d", &flash);
    int radix[flash];

    for (int i = 0; i < flash; i++) {
        printf("Index radix[%d]: ", i);
        scanf("%d", &radix[i]);
    }

    int max_iterations = getiterations(radix, flash);
    radixin(radix, flash, max_iterations);

    return 0;
}
