#include <stdio.h>
#include <stdlib.h>

struct heap {
    int data;
    int level;
    struct heap* right;
    struct heap* left;
    struct heap* parent;
};

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
        int temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;
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

void printHeap(struct heap* root) {
    if (!root) return;
    printf("Node: %d, Level: %d\n", root->data, root->level);
    if (root->left) printHeap(root->left);
    if (root->right) printHeap(root->right);
}

int main() {
    struct heap* root = NULL;
    printf("Max heap implementation\n");
    int flash = 0, d;

    while (flash != -1) {
        printf("Enter data (or -1 to stop): ");
        if (scanf("%d", &d) != 1) break;
        if (d == -1) break;

        root = insertion(root, d);
        printHeap(root);
    }

    return 0;
}
