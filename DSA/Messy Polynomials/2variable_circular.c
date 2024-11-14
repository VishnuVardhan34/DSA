#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coeff;
    int x_deg;
    int y_deg;
    struct Term *next;
};

struct Term* createTerm(int coeff, int x_deg, int y_deg) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coeff = coeff;
    newTerm->x_deg = x_deg;
    newTerm->y_deg = y_deg;
    newTerm->next = newTerm;
    return newTerm;
}

void insertTerm(struct Term** poly, int coeff, int x_deg, int y_deg) {
    struct Term* newTerm = createTerm(coeff, x_deg, y_deg);

    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        struct Term* last = (*poly)->next;
        while (last->next != *poly) {
            last = last->next;
        }
        last->next = newTerm;
        newTerm->next = *poly;
    }
}

struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    struct Term* p1 = poly1;
    struct Term* p2 = poly2;

    do {
        insertTerm(&result, p1->coeff, p1->x_deg, p1->y_deg);
        p1 = p1->next;
    } while (p1 != poly1);

    do {
        struct Term* curr = result;
        int found = 0;
        do {
            if (curr->x_deg == p2->x_deg && curr->y_deg == p2->y_deg) {
                curr->coeff += p2->coeff;
                found = 1;
                break;
            }
            curr = curr->next;
        } while (curr != result);

        if (!found) {
            insertTerm(&result, p2->coeff, p2->x_deg, p2->y_deg);
        }
        p2 = p2->next;
    } while (p2 != poly2);

    return result;
}

void displayPolynomial(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    struct Term* current = poly;
    do {
        if (current->coeff > 0 && current != poly) {
            printf("+ ");
        }
        printf("%dx^%dy^%d ", current->coeff, current->x_deg, current->y_deg);
        current = current->next;
    } while (current != poly);
    printf("\n");
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    int flash = 0, c, x_deg, y_deg;

    printf("Enter terms for Polynomial 1 (-1 to finish):\n");
    while (flash != -1) {
        printf("Coeff: ");
        scanf("%d", &c);
        printf("x Deg: ");
        scanf("%d", &x_deg);
        printf("y Deg: ");
        scanf("%d", &y_deg);
        insertTerm(&poly1, c, x_deg, y_deg);
        printf("Continue? (-1 to finish, any other number to continue): ");
        scanf("%d", &flash);
    }

    flash = 0;
    printf("\nEnter terms for Polynomial 2 (-1 to finish):\n");
    while (flash != -1) {
        printf("Coeff: ");
        scanf("%d", &c);
        printf("x Deg: ");
        scanf("%d", &x_deg);
        printf("y Deg: ");
        scanf("%d", &y_deg);
        insertTerm(&poly2, c, x_deg, y_deg);
        printf("Continue? (-1 to finish, any other number to continue): ");
        scanf("%d", &flash);
    }

    printf("\nPolynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Term* result = addPolynomials(poly1, poly2);

    printf("Result of Addition: ");
    displayPolynomial(result);

    return 0;
}
