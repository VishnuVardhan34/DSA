#include <stdio.h>
#include <stdlib.h>

struct AVL {
    int data;
    int heightfactor; // balance factor: left height - right height
    struct AVL *right;
    struct AVL *left;
    struct AVL *parent;
};

struct QueueNode {
    struct AVL* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

// Queue functions for BFS traversal
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, struct AVL* node) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}

struct AVL* dequeue(struct Queue* queue) {
    if (queue->front == NULL)
        return NULL;
    struct QueueNode* temp = queue->front;
    struct AVL* node = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(temp);
    return node;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

void printBFS(struct AVL* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    struct Queue* queue = createQueue();
    enqueue(queue, root);

    printf("BFS representation of AVL tree:\n");
    while (!isQueueEmpty(queue)) {
        struct AVL* current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left != NULL)
            enqueue(queue, current->left);
        if (current->right != NULL)
            enqueue(queue, current->right);
    }
    printf("\n");
}

// AVL tree functions
int getHeight(struct AVL *node) {
    if (node == NULL) return -1;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void updateHeightFactor(struct AVL *node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->heightfactor = leftHeight - rightHeight;
    }
}

struct AVL* rotateRight(struct AVL* problem) {
    struct AVL *help = problem->left;
    problem->left = help->right;
    if (help->right != NULL) help->right->parent = problem;
    help->parent = problem->parent;
    if (problem->parent == NULL) {
    } else if (problem == problem->parent->left) {
        problem->parent->left = help;
    } else {
        problem->parent->right = help;
    }
    help->right = problem;
    problem->parent = help;

    updateHeightFactor(problem);
    updateHeightFactor(help);

    return help;
}

struct AVL* rotateLeft(struct AVL* problem) {
    struct AVL *help = problem->right;
    problem->right = help->left;
    if (help->left != NULL) help->left->parent = problem;
    help->parent = problem->parent;
    if (problem->parent == NULL) {
    } else if (problem == problem->parent->left) {
        problem->parent->left = help;
    } else {
        problem->parent->right = help;
    }
    help->left = problem;
    problem->parent = help;

    updateHeightFactor(problem);
    updateHeightFactor(help);

    return help;
}

struct AVL* identifyAVL(struct AVL* problem) {
    if (problem->heightfactor == -2) {
        if (problem->right->heightfactor <= 0) {
            return rotateLeft(problem); // RR Rotation
        } else {
            rotateRight(problem->right);
            return rotateLeft(problem); // RL Rotation
        }
    } else if (problem->heightfactor == 2) {
        if (problem->left->heightfactor >= 0) {
            return rotateRight(problem); // LL Rotation
        } else {
            rotateLeft(problem->left);
            return rotateRight(problem); // LR Rotation
        }
    }
    return problem;
}

struct AVL* insertionAVL(struct AVL* root, int info) {
    struct AVL *record = NULL;

    if (root->data > info && root->left != NULL) {
        root->heightfactor += 1;
        if (root->heightfactor == -2 || root->heightfactor == 2) {
            record = root;
        }
        root->left = insertionAVL(root->left, info);
    }
    if (root->data > info && root->left == NULL) {
        struct AVL *attach = (struct AVL*)malloc(sizeof(struct AVL));
        attach->data = info;
        attach->left = attach->right = NULL;
        attach->parent = root;
        attach->heightfactor = 0;
        root->left = attach;
        root->heightfactor += 1;
        if (root->heightfactor == -2 || root->heightfactor == 2) {
            record = root;
        }
    }
    if (root->data < info && root->right != NULL) {
        root->heightfactor -= 1;
        if (root->heightfactor == -2 || root->heightfactor == 2) {
            record = root;
        }
        root->right = insertionAVL(root->right, info);
    }
    if (root->data < info && root->right == NULL) {
        struct AVL *attach = (struct AVL*)malloc(sizeof(struct AVL));
        attach->data = info;
        attach->left = attach->right = NULL;
        attach->parent = root;
        attach->heightfactor = 0;
        root->right = attach;
        root->heightfactor -= 1;
        if (root->heightfactor == -2 || root->heightfactor == 2) {
            record = root;
        }
    }

    updateHeightFactor(root);

    if (root->heightfactor == -2 || root->heightfactor == 2) {
        root = identifyAVL(root);
    }

    return root;
}

struct AVL* minValueNode(struct AVL* node) {
    struct AVL* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct AVL* deleteNode(struct AVL* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct AVL* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct AVL* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) return root;

    updateHeightFactor(root);
    return identifyAVL(root);
}

void deleteAVL(struct AVL** root, int key) {
    *root = deleteNode(*root, key);
}

int main() {
    struct AVL *travel = NULL;
    printf("Considering the tree with only positive numbers and negative numbers (excluding -1)\n");
    int flash = 0, d;

    while (flash != -1) {
        printf("Data:\n");
        scanf("%d", &d);

        if (travel == NULL && d!=-1) {
            struct AVL *tree = (struct AVL*)malloc(sizeof(struct AVL));
            tree->right = tree->left = tree->parent = NULL;
            tree->data = d;
            tree->heightfactor = 0;
            travel = tree;
        } else {
            travel = insertionAVL(travel, d);
        }
        flash =d;

    }

    printBFS(travel);

    printf("Enter deletion? Enter 0 to start\n");
    scanf("%d", &flash);
    while (flash != -1) {
        printf("Enter node for deletion:\n");
        scanf("%d", &d);
        deleteAVL(&travel, d);
        printBFS(travel);
        printf("Continue deletion? (-1 to stop)\n");
        scanf("%d", &flash);
    }

    return 0;
}
