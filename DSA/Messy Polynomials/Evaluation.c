#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int coeff;
    int deg;
    struct Node *next;
    struct Node *prev;
};

struct Node* createNode(int coeff, int deg) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->deg = deg;
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
}

void insertTerm(struct Node** poly, int coeff, int deg) {
    struct Node* newNode = createNode(coeff, deg);

    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* last = (*poly)->prev;
        last->next = newNode;
        newNode->prev = last;
        newNode->next = *poly;
        (*poly)->prev = newNode;
    }
}

double evaluatePolynomial(struct Node* poly, double x) {
    double result = 0.0;
    if (poly == NULL) return result;

    struct Node* current = poly;
    do {
        result += current->coeff * pow(x, current->deg);
        current = current->next;
    } while (current != poly);

    return result;
}

void displayPolynomial(struct Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    struct Node* current = poly;
    do {
        if (current->coeff > 0 && current != poly) {
            printf("+ ");
        }
        printf("%dx^%d ", current->coeff, current->deg);
        current = current->next;
    } while (current != poly);
    printf("\n");
}

int main() {
    struct Node* poly = NULL;
    int flash = 0, c, d;
    double x;

    printf("Enter terms for the polynomial (-1 to finish):\n");
    while (flash != -1) {
        printf("Coeff: ");
        scanf("%d", &c);
        printf("Deg: ");
        scanf("%d", &d);
        insertTerm(&poly, c, d);
        printf("Continue? (-1 to finish, any other number to continue): ");
        scanf("%d", &flash);
    }

    printf("\nPolynomial: ");
    displayPolynomial(poly);

    printf("\nEnter the value of x: ");
    scanf("%lf", &x);

    double result = evaluatePolynomial(poly, x);
    printf("The result of the polynomial evaluation at x = %.2lf is: %.2lf\n", x, result);

    return 0;
}
