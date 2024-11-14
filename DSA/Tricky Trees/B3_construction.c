#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3      // Maximum keys in a node (for a 4-way B-Tree)
#define MIN_KEYS 1      // Minimum keys in a non-root node

typedef struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode *children[MAX_KEYS + 1];
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode* createNode(int isLeaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->numKeys = 0;
    newNode->isLeaf = isLeaf;

    for (int i = 0; i <= MAX_KEYS; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void traverse(BTreeNode* node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                traverse(node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }

        if (!node->isLeaf) {
            traverse(node->children[i]);
        }
    }
}

BTreeNode* splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
    int mid = MAX_KEYS / 2;

    BTreeNode* newChild = createNode(fullChild->isLeaf);
    newChild->numKeys = mid;

    for (int j = 0; j < mid; j++) {
        newChild->keys[j] = fullChild->keys[mid + 1 + j];
    }

    if (!fullChild->isLeaf) {
        for (int j = 0; j <= mid; j++) {
            newChild->children[j] = fullChild->children[mid + 1 + j];
        }
    }

    fullChild->numKeys = mid;

    for (int j = parent->numKeys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }

    parent->children[i + 1] = newChild;

    for (int j = parent->numKeys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }

    parent->keys[i] = fullChild->keys[mid];
    parent->numKeys += 1;

    return parent;
}

BTreeNode* insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->numKeys += 1;
    } else {
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == MAX_KEYS) {
            node = splitChild(node, i, node->children[i]);

            if (node->keys[i] < key) {
                i++;
            }
        }
        node->children[i] = insertNonFull(node->children[i], key);
    }

    return node;
}

BTreeNode* insert(BTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == MAX_KEYS) {
            BTreeNode* newRoot = createNode(0);
            newRoot->children[0] = root;
            newRoot = splitChild(newRoot, 0, root);

            int i = 0;
            if (newRoot->keys[0] < key) {
                i++;
            }
            newRoot->children[i] = insertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            root = insertNonFull(root, key);
        }
    }

    return root;
}

int main() {
    BTreeNode* root = NULL;
    int key;

    printf("B-Tree (4-way) insertion program.\n");
    printf("Enter keys to insert into the B-Tree. Type -1 to stop.\n");

    while (1) {
        printf("Enter key: ");
        scanf("%d", &key);

        if (key == -1) {
            break;
        }

        root = insert(root, key);
        printf("B-Tree after inserting %d: ", key);
        traverse(root);
        printf("\n");
    }

    printf("\nFinal B-Tree traversal: ");
    traverse(root);
    printf("\n");

    return 0;
}
