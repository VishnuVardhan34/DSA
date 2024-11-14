#include <stdio.h>
#include <stdlib.h>

struct heap {
    int data;
    int level;
    struct heap* right;
    struct heap* left;
    struct heap* parent;
};

void swap(struct heap* a, struct heap* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

struct heap* changelink(struct heap* root) {
    if (!root) return NULL;

    struct heap* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct heap* current = queue[front++];

        if (!current->left) return current;
        if (!current->right) return current;

        queue[rear++] = current->left;
        queue[rear++] = current->right;
    }

    return NULL;
}

void bubbleUp(struct heap* node) {
    while (node->parent && node->data > node->parent->data) {
        swap(node, node->parent);
        node = node->parent;
    }
}

struct heap* insertion(struct heap* root, int d) {
    struct heap* newchild = (struct heap*)malloc(sizeof(struct heap));
    newchild->data = d;
    newchild->left = newchild->right = newchild->parent = NULL;

    if (!root) {
        newchild->level = 0;
        return newchild;
    }

    struct heap* link = changelink(root);

    newchild->level = link->level + 1;
    newchild->parent = link;

    if (!link->left) {
        link->left = newchild;
    } else {
        link->right = newchild;
    }

    bubbleUp(newchild);

    return root;
}

void heapifyDown(struct heap* node) {
    while (node->left || node->right) {
        struct heap* largest = node;

        if (node->left && node->left->data > largest->data)
            largest = node->left;
        if (node->right && node->right->data > largest->data)
            largest = node->right;

        if (largest != node) {
            swap(node, largest);
            node = largest;
        } else {
            break;
        }
    }
}

struct heap* getLastNode(struct heap* root) {
    if (!root) return NULL;

    struct heap* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    struct heap* last = NULL;
    while (front < rear) {
        last = queue[front++];

        if (last->left) queue[rear++] = last->left;
        if (last->right) queue[rear++] = last->right;
    }

    return last;
}

struct heap* extractMax(struct heap* root) {
    if (!root) return NULL;

    struct heap* lastNode = getLastNode(root);

    swap(root, lastNode);

    if (lastNode->parent) {
        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = NULL;
        } else {
            lastNode->parent->right = NULL;
        }
    }

    if (lastNode == root) {
        free(root);
        return NULL;
    }

    free(lastNode);

    heapifyDown(root);

    return root;
}

void heapSort(struct heap* root) {
    printf("Heap Sort (Descending Order): ");
    while (root) {
        printf("%d ", root->data);
        root = extractMax(root);
    }
    printf("\n");
}

void printHeap(struct heap* root) {
    if (!root) return;

    struct heap* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    printf("Heap structure:\n");
    while (front < rear) {
        struct heap* current = queue[front++];
        printf("Node: %d, Level: %d\n", current->data, current->level);

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
}

int main() {
    struct heap* root = NULL;
    printf("Max Heap implementation with Heap Sort\n");

    int flash = 0, d;
    while (flash != -1) {
        printf("Enter data (or -1 to stop): ");
        if (scanf("%d", &d) != 1) break;
        if (d == -1) break;

        root = insertion(root, d);
        printHeap(root);
    }

    heapSort(root);

    return 0;
}
