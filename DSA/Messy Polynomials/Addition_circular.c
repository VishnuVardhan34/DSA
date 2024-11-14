#include <stdio.h>
#include <stdlib.h>

struct term {
    int coeff;
    int deg;
    struct term *next;
};

// Function to insert a new term in the polynomial list
void addTerm(struct term **poly, int coeff, int deg) {
    struct term *newTerm = (struct term *)malloc(sizeof(struct term));
    newTerm->coeff = coeff;
    newTerm->deg = deg;

    if (*poly == NULL) {
        newTerm->next = newTerm;  // First term points to itself to form a circular list
        *poly = newTerm;
    } else {
        struct term *last = *poly;
        while (last->next != *poly) {
            last = last->next;
        }
        last->next = newTerm;
        newTerm->next = *poly;  // Complete the circle
    }
}

// Function to add two polynomials
struct term *addPolynomials(struct term *poly1, struct term *poly2) {
    struct term *result = NULL;
    struct term *p1 = poly1, *p2 = poly2;

    do {
        if (p1->deg == p2->deg) {
            int sumCoeff = p1->coeff + p2->coeff;
            addTerm(&result, sumCoeff, p1->deg);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->deg < p2->deg) {
            addTerm(&result, p1->coeff, p1->deg);
            p1 = p1->next;
        } else {
            addTerm(&result, p2->coeff, p2->deg);
            p2 = p2->next;
        }
    } while (p1 != poly1 || p2 != poly2);

    return result;
}

// Function to display the polynomial
void displayPolynomial(struct term *poly) {
    if (poly == NULL) return;

    struct term *current = poly;
    do {
        if (current->coeff > 0) {
            printf("+ %dx^%d ", current->coeff, current->deg);
        } else {
            printf("%dx^%d ", current->coeff, current->deg);
        }
        current = current->next;
    } while (current != poly);
    printf("\n");
}

int main() {
    struct term *poly1 = NULL, *poly2 = NULL;
    int flash = 0, c, d;

    printf("Enter terms for Polynomial 1 (-1 to finish):\n");
    while (flash != -1) {
        printf("Coeff: ");
        scanf("%d", &c);
        printf("Deg: ");
        scanf("%d", &d);
        addTerm(&poly1, c, d);
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
        addTerm(&poly2, c, d);
        printf("Continue? (-1 to finish, any other number to continue): ");
        scanf("%d", &flash);
    }

    printf("\nPolynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct term *result = addPolynomials(poly1, poly2);

    printf("Result of Addition: ");
    displayPolynomial(result);

    return 0;
}

