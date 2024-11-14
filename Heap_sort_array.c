#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void heapify_down(int h[], int n, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && h[left] > h[largest]) {
        largest = left;
    }

    if (right < n && h[right] > h[largest]) {
        largest = right;
    }

    if (largest != index) {
        int temp = h[index];
        h[index] = h[largest];
        h[largest] = temp;
        heapify_down(h, n, largest);
    }
}

void display(int h[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");
}

void heapsort(int h[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_down(h, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        printf("%d |", h[0]);
        int temp = h[0];
        h[0] = h[i];
        h[i] = temp;

        heapify_down(h, i, 0);
    }

    printf("%d\n", h[0]);
}

int main() {
    int heap[MAX];
    int iterator = 0;

    printf("Considering a max-heap with only positive numbers\n");
    printf("-1 to stop inserting\n");

    while (1) {
        int block;
        printf("Enter element: ");
        scanf("%d", &block);

        if (block == -1) {
            break;
        }

        heap[iterator] = block;
        int i = iterator;
        while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
            int temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }

        iterator++;
        printf("Heap after insertion: ");
        display(heap, iterator);
    }

    printf("Final heap: ");
    display(heap, iterator);

    printf("Heap sorting...\n");
    heapsort(heap, iterator);

    return 0;
}
