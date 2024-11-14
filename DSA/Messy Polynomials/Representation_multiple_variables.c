#include <stdio.h>
#include <stdlib.h>

struct poly {
    int coeff;
    int degx;
    int degy;
    struct poly *next;
};

int main() {
    struct poly *zero = (struct poly *)malloc(sizeof(struct poly));
    zero->coeff = 0;
    zero->degx = 0;
    zero->degy = 0;
    zero->next = NULL;
    struct poly *travel;
    struct poly *lastadd = zero;

    int flash = 0, c, dx, dy;

    printf("Polynomial with two variables (x and y)\n");
    printf("Enter -1 to exit.\n");

    while (flash != -1) {
        travel = zero->next;

        printf("Coeff: ");
        scanf("%d", &c);
        printf("Degx: ");
        scanf("%d", &dx);
        printf("Degy: ");
        scanf("%d", &dy);

        while (travel != NULL && (travel->degx != dx || travel->degy != dy)) {
            travel = travel->next;
        }

        if (travel == NULL) {
            struct poly *newterm = (struct poly *)malloc(sizeof(struct poly));
            newterm->coeff = c;
            newterm->degx = dx;
            newterm->degy = dy;
            newterm->next = NULL;
            lastadd->next = newterm;
            lastadd = newterm;
        } else {
            travel->coeff += c;
        }

        printf("Continue? (-1 to exit, any other number to continue): ");
        scanf("%d", &flash);
    }

    char a;
    printf("Sort polynomial with variable");
    scanf("%c", &a);

    travel = zero->next;
    while (travel != NULL) {
        if (travel->coeff > 0) {
            printf("+ %dx^%dy^%d  ", travel->coeff, travel->degx, travel->degy);
        } else {
            printf("%dx^%dy^%d  ", travel->coeff, travel->degx, travel->degy);
        }
        travel = travel->next;
    }

    return 0;
}
