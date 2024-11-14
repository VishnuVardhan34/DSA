#include <stdio.h>
#include <stdlib.h>

struct poly {
    int coeff;
    int deg;
    struct poly *next;
};

void addTerm(struct poly **head, int coeff, int deg) {
    struct poly *temp = *head;
    struct poly *prev = NULL;
    while (temp != NULL && temp->deg > deg) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL && temp->deg == deg) {
        temp->coeff += coeff;
    } else {
        struct poly *newterm = (struct poly*)malloc(sizeof(struct poly));
        newterm->coeff = coeff;
        newterm->deg = deg;
        newterm->next = temp;
        if (prev == NULL) {
            *head = newterm;
        } else {
            prev->next = newterm;
        }
    }
}

void printPoly(struct poly *head) {
    struct poly *temp = head;
    int i = 1;
    while (temp != NULL) {
        printf("Term %d: Coeff: %d Deg: %d\n", i++, temp->coeff, temp->deg);
        temp = temp->next;
    }
}

int main() {
    int n = 0, c = 0, d = 0;
    struct poly *polynomial1 = NULL;

    printf("Enter the first polynomial, specifying the coefficient and degree respectively.\n");
    printf("Number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nCoefficient: ");
        scanf("%d", &c);
        printf("Degree: ");
        scanf("%d", &d);
        addTerm(&polynomial1, c, d);
    }

    printf("\nEnter the second polynomial\n");
    printf("Number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nCoefficient: ");
        scanf("%d", &c);
        printf("Degree: ");
        scanf("%d", &d);
        addTerm(&polynomial1, c, d);
    }

    printf("\nResultant polynomial:\n");
    printPoly(polynomial1);

    return 0;
}
