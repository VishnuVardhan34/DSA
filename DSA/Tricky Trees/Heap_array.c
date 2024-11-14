#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void heapify(int h[], int index) {
    int i = index;
    while (i > 0 && h[i] > h[(i - 1) / 2]) {

        int temp = h[i];
        h[i] = h[(i - 1) / 2];
        h[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void display(int h[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", h[i]);
    }
    printf("\n");
}

int main() {
    int heap[MAX];
    printf("Considering a max-heap with only positive numbers\n");
    printf("-1 to stop inserting\n");

    int block = 0;
    int iterator = 0;

    for (int i = 0; i < MAX; i++) {
        heap[i] = -1;
    }

    while (1) {
        printf("Enter element: ");
        scanf("%d", &block);

        if (block == -1) {
            break;
        }


        heap[iterator] = block;
        heapify(heap, iterator);
        iterator++;

        printf("Heap after insertion: ");
        display(heap, iterator);
    }

    printf("Final heap: ");
    display(heap, iterator);

    return 0;
}
