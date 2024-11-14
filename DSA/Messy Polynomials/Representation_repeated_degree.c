#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct poly{
    int coeff;
    int deg;
    struct poly * next;
};

void sortPolynomial(struct poly *head) {
    if (!head || !head->next) return;

    struct poly *sorted = NULL;

    struct poly *current = head->next;
    while (current != NULL) {
        struct poly *next = current->next;

        if (sorted == NULL || sorted->deg > current->deg) {
            current->next = sorted;
            sorted = current;
        } else {
            struct poly *temp = sorted;
            while (temp->next != NULL && temp->next->deg < current->deg) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    head->next = sorted;
}

int main(){
    struct poly * zero = (struct poly*)malloc(sizeof(struct poly));
    zero->coeff = 0;
    zero->deg = 0;
    zero->next = NULL;
    int flash=0,c,d;
    struct poly * travel = zero->next;
    struct poly * lastadd = zero;
    printf("Polynomial with one variable\n");
    printf("-1 to exit\n");

        while (flash != -1) {
        printf("\n\n");
        travel = zero->next;

        printf("Coeff: ");
        scanf("%d", &c);
        printf("Deg: ");
        scanf("%d", &d);

        while (travel != NULL && travel->deg != d) {
            travel = travel->next;
        }

        if (travel == NULL) {
            struct poly *newterm = (struct poly *)malloc(sizeof(struct poly));
            newterm->coeff = c;
            newterm->deg = d;
            newterm->next = NULL;
            lastadd->next = newterm;
            lastadd = newterm;
        } else {
            travel->coeff += c;
        }

        printf("Continue? (-1 to exit, any other number to continue): ");
        scanf("%d", &flash);
    }

    sortPolynomial(zero);

    travel = zero->next;
    while(travel!=NULL){
        if(travel->coeff > 0){
            printf("+ %dx^%d  ", travel->coeff, travel->deg);
        }
        else{
            printf("%dx^%d  ", travel->coeff, travel->deg);
        }
        travel=travel->next;
    }
    return 0;
}
