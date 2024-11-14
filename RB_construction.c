#include <stdio.h>
#include <stdlib.h>

struct RB {
    int data;
    char dot; // 'R' for Red, 'B' for Black
    struct RB* right;
    struct RB* left;
    struct RB* parent;
};

struct QueueNode {
    struct RB* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

void enqueue(struct Queue* queue, struct RB* treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

struct RB* dequeue(struct Queue* queue) {
    if (queue->front == NULL) return NULL;
    struct QueueNode* temp = queue->front;
    struct RB* treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    return treeNode;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

void displayTreeBFS(struct RB* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    struct Queue queue = {NULL, NULL};
    enqueue(&queue, root);

    printf("Tree (BFS) with Colors:\n");

    while (!isQueueEmpty(&queue)) {
        struct RB* current = dequeue(&queue);
        printf("%d(%c) ", current->data, current->dot);

        if (current->left != NULL) {
            enqueue(&queue, current->left);
        }
        if (current->right != NULL) {
            enqueue(&queue, current->right);
        }
    }
    printf("\n");
}

void rotateLeft(struct RB** root, struct RB* node) {
    struct RB* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != NULL) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == NULL) {
        *root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

void rotateRight(struct RB** root, struct RB* node) {
    struct RB* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == NULL) {
        *root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

void checkRBproperty(struct RB** root, struct RB* attached) {
    while (attached != *root && attached->parent->dot == 'R') {
        struct RB* parent = attached->parent;
        struct RB* grandparent = parent->parent;

        if (parent == grandparent->left) {
            struct RB* uncle = grandparent->right;
            if (uncle != NULL && uncle->dot == 'R') {
                grandparent->dot = 'R';
                parent->dot = 'B';
                uncle->dot = 'B';
                attached = grandparent;
            } else {
                if (attached == parent->right) {
                    rotateLeft(root, parent);
                    attached = parent;
                    parent = attached->parent;
                }
                rotateRight(root, grandparent);
                parent->dot = 'B';
                grandparent->dot = 'R';
                attached = parent;
            }
        } else {
            struct RB* uncle = grandparent->left;
            if (uncle != NULL && uncle->dot == 'R') {
                grandparent->dot = 'R';
                parent->dot = 'B';
                uncle->dot = 'B';
                attached = grandparent;
            } else {
                if (attached == parent->left) {
                    rotateRight(root, parent);
                    attached = parent;
                    parent = attached->parent;
                }
                rotateLeft(root, grandparent);
                parent->dot = 'B';
                grandparent->dot = 'R';
                attached = parent;
            }
        }
    }
    (*root)->dot = 'B';
}

struct RB* insertionRB(struct RB* root, int d) {

    struct RB* newNode = (struct RB*)malloc(sizeof(struct RB));
    newNode->data = d;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->dot = 'R';

    if (root == NULL) {
        newNode->dot = 'B'; // Root node must be black
        return newNode;
    }

    struct RB* travel = root;
    struct RB* parent = NULL;

    while (travel != NULL) {
        parent = travel;
        if (d < travel->data) {
            travel = travel->left;
        } else {
            travel = travel->right;
        }
    }

    newNode->parent = parent;
    if (d < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    checkRBproperty(&root, newNode);
    return root;
}

int main() {
    struct RB* blackdot = NULL;
    printf("Insertion in Red-Black Tree\n");

    int flash = 0, d;
    while (flash != -1) {
        printf("Data: ");
        scanf("%d", &d);

        blackdot = insertionRB(blackdot, d);

        printf("Continue? (-1 to exit): ");
        scanf("%d", &flash);
    }

    displayTreeBFS(blackdot);

    return 0;
}
