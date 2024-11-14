#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int deg;
    struct Node *next;
    struct Node *prev;
};

// Function to create a new term node
struct Node* createNode(int coeff, int deg) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->deg = deg;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a new term at the end of the doubly linked list
void insertTerm(struct Node** poly, int coeff, int deg) {
    struct Node* newNode = createNode(coeff, deg);

    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to subtract two polynomials
struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL || p2 != NULL) {
        if (p1 != NULL && (p2 == NULL || p1->deg > p2->deg)) {
            insertTerm(&result, p1->coeff, p1->deg);
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p2->deg > p1->deg)) {
            insertTerm(&result, -p2->coeff, p2->deg);
            p2 = p2->next;
        } else { // Degrees are equal
            int diffCoeff = p1->coeff - p2->coeff;
            if (diffCoeff != 0) {
                insertTerm(&result, diffCoeff, p1->deg);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}

// Function to display the polynomial
void displayPolynomial(struct Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    struct Node* current = poly;
    while (current != NULL) {
        if (current->coeff > 0 && current != poly) {
            printf("+ ");
        }
        printf("%dx^%d ", current->coeff, current->deg);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    int flash = 0, c, d;

    printf("Enter terms for Polynomial 1 (-1 to finish):\n");
    while (flash != -1) {
        printf("Coeff: ");
        scanf("%d", &c);
        printf("Deg: ");
        scanf("%d", &d);
        insertTerm(&poly1, c, d);
        printf("Continue? (-1 to finish, any other number to continue): ");
        scanf("%d", &flash);
    }

    flash = 0;
    printf("\nEnter terms for Polynomial 2 (-1 to finish):\n");
    while (flash != -1) {
        printf("Coeff: ");
        scanf("%d", &c);
        printf("Deg: ");
        scanf("%d", &d);
        insertTerm(&poly2, c, d);
        printf("Continue? (-1 to finish, any other number to continue): ");
        scanf("%d", &flash);
    }

    printf("\nPolynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Node* result = subtractPolynomials(poly1, poly2);

    printf("Result of Subtraction (Polynomial 1 - Polynomial 2): ");
    displayPolynomial(result);

    return 0;
}

