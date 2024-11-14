#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


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

void displaypoly(struct poly * travel, struct poly * zero, int i, int n){
    if(i!=n-1)
    printf("\nPolynomial %d\n", i+1);
    else
        printf("\nResult Polynomial: \n");
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
}

int main(){
    struct poly * zero = (struct poly *)malloc(sizeof(struct poly));
    zero->coeff=0;
    zero->deg=0;
    zero->next=NULL;
    struct poly * travel;
    struct poly * lastadd = zero;

    int flash =0,c,d;
    int n;
    printf("Polynomial addition no limit, only one single linked list.\n");
    printf("Number of polynomials to add\n");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
            printf("\n\nPolynomial %d: ", i+1);
            while(flash!=-1){
                printf("\n");
            travel = zero->next;
            printf("Coeff: ");
            scanf("%d", &c);
            printf("Deg: ");
            scanf("%d", &d);

            while(travel!=NULL && travel->deg!=d){
                travel=travel->next;
            }

            if(travel==NULL){
                struct poly * newterm = (struct poly *)malloc(sizeof(struct poly));
                newterm->coeff=c;
                newterm->deg=d;
                newterm->next=NULL;
                lastadd->next=newterm;
                lastadd=newterm;
            }
            else{
                travel->coeff+=c;
            }

            printf("Continue?");
            scanf("%d", &flash);
        }
        flash=0;
        sortPolynomial(zero);
        displaypoly(travel, zero, i, n);
    }


    return 0;
}
