#include <stdio.h>
#include <stdlib.h>

struct SM {
    int row;
    int col;
    int data;
    struct SM* next;
};

struct SM* inserting(struct SM* travel, int r, int c, int d) {
    struct SM* root = travel;
    if (travel == NULL) {
        struct SM* added = (struct SM*)malloc(sizeof(struct SM));
        added->row = r;
        added->col = c;
        added->data = d;
        added->next = NULL;
        root = added;
        return root;
    } else {
        while (travel->next != NULL) {
            travel = travel->next;
        }
        struct SM* added = (struct SM*)malloc(sizeof(struct SM));
        added->row = r;
        added->col = c;
        added->data = d;
        added->next = NULL;
        travel->next = added;
        return root;
    }
}

void displaySM(struct SM* root) {
    printf("\nTRIPLET TABLE\n");
    printf("----------------\n");
    printf("Row\tColumn\tData\t\n");
    while (root != NULL) {
        printf("%d\t%d\t%d\n", root->row, root->col, root->data);
        root = root->next;
    }
}

struct SM* modify(struct SM* root) {
    struct SM* stored = root;
    struct SM* backpointer = NULL;

    printf("Enter row and column to modify\n");
    int mr, mc, md;
    scanf("%d%d", &mr, &mc);

    if (root == NULL) {
        printf("List is empty.\n");
        return root;
    }

    while (root != NULL) {
        if (root->row == mr && root->col == mc) {
            printf("Current data: %d\nEnter new data: ", root->data);
            scanf("%d", &md);

            if (md == 0) {
                if (backpointer == NULL) {
                    free(root);
                    root = NULL;
                    printf("Node deleted. List is now empty.\n");
                } else {
                    backpointer->next = root->next;
                    free(root);
                    printf("Node deleted.\n");
                }
            } else {
                root->data = md;
                printf("Node updated to %d.\n", md);
            }

            return stored;
        }
        backpointer = root;
        root = root->next;
    }

    printf("Node with row %d and column %d not found.\n", mr, mc);

    char ch;
    printf("Do you want to insert a new node? (Y/N): ");
    scanf(" %c", &ch);
    if (ch == 'Y' || ch == 'y') {
        printf("Specify the data for the new node: ");
        scanf("%d", &md);
        stored = inserting(stored, mr, mc, md);
        printf("New node inserted.\n");
    }

    return stored;
}

void addition(struct SM* root, struct SM* reet) {
    struct SM* result = NULL;
    struct SM* ptr1 = root;
    struct SM* ptr2 = reet;

    // Add nodes from both lists
    while (ptr1 != NULL || ptr2 != NULL) {
        if (ptr1 == NULL) {
            result = inserting(result, ptr2->row, ptr2->col, ptr2->data);
            ptr2 = ptr2->next;
        } else if (ptr2 == NULL) {
            result = inserting(result, ptr1->row, ptr1->col, ptr1->data);
            ptr1 = ptr1->next;
        } else if (ptr1->row == ptr2->row && ptr1->col == ptr2->col) {
            int sum = ptr1->data + ptr2->data;
            if (sum != 0) {
                result = inserting(result, ptr1->row, ptr1->col, sum);
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        } else if (ptr1->row < ptr2->row || (ptr1->row == ptr2->row && ptr1->col < ptr2->col)) {
            result = inserting(result, ptr1->row, ptr1->col, ptr1->data);
            ptr1 = ptr1->next;
        } else {
            result = inserting(result, ptr2->row, ptr2->col, ptr2->data);
            ptr2 = ptr2->next;
        }
    }

    // Display the result
    printf("\nResultant Triplet Table after Addition:\n");
    displaySM(result);

    printf("\nResultant Matrix Representation:\n");
    displayMat(result);
}

void displayMat(struct SM* root) {
    if (root == NULL) {
        printf("Matrix is empty.\n");
        return;
    }
    struct SM* find = root;
    int maxRow = 0, maxCol = 0;
    while (find != NULL) {
        if (find->row > maxRow) maxRow = find->row;
        if (find->col > maxCol) maxCol = find->col;
        find = find->next;
    }

    printf("Matrix representation:\n");
    for (int i = 0; i <= maxRow; i++) {
        for (int j = 0; j <= maxCol; j++) {
            find = root;
            int value = 0;
            while (find != NULL) {
                if (find->row == i && find->col == j) {
                    value = find->data;
                    break;
                }
                find = find->next;
            }
            printf("%d ", value);
        }
        printf("\n");
    }
}

int main() {
    int flash = 0, r, c, d;
    struct SM* root = NULL;
    printf("Enter -1 to terminate insertion\n");
    while (flash != -1) {
        printf("Row, Column, Data:\n");
        scanf("%d%d%d", &r, &c, &d);
        if (r == -1 || c == -1 || d == -1 || d == 0) {
            flash = -1;
            break;
        }
        root = inserting(root, r, c, d);
    }

    struct SM* reet = NULL;
    flash = 0;
    printf("Enter -1 to terminate insertion (2nd matrix)\n");
    while (flash != -1) {
        printf("Row, Column, Data:\n");
        scanf("%d%d%d", &r, &c, &d);
        if (r == -1 || c == -1 || d == -1) {
            flash = -1;
            break;
        }
        reet = inserting(reet, r, c, d);
    }

    flash = 0;
    while (flash != -1) {
        printf("\n1. Display both matrices\n");
        printf("2. Addition\n");
        printf("3. Modification\n");
        printf("4. Display a real matrix (Considering the maximum number of row and column)\n");
        scanf("%d", &flash);
        switch (flash) {
            case 1: {
                displaySM(root);
                displaySM(reet);
                break;
            }
            case 2: {
                printf("Adding both matrices...\n");
                addition(root, reet);
                break;
            }
            case 3: {
                int decide;
                printf("List 1 or 2?\n");
                scanf("%d", &decide);
                if (decide == 1) {
                    root = modify(root);
                } else if (decide == 2) {
                    reet = modify(reet);
                } else {
                    printf("Invalid list selection.\n");
                }
                break;
            }
            case 4: {
                printf("SM-1\n");
                displayMat(root);
                printf("SM-2\n");
                displayMat(reet);
                break;
            }
            default: {
                printf("Invalid!\n");
            }
        }
    }

    return 0;
}
