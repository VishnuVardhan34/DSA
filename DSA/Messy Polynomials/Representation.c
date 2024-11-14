#include <stdio.h>
#include <string.h>

struct poly{
    int coeff;
    int deg;
    struct poly * next;
};

int main(){
    struct poly * zero = (struct poly*)malloc(sizeof(struct poly));
    zero->coeff = 0;
    zero->deg = 0;
    zero->next = NULL;
    int flash = 0,c,d;
    struct poly * travel = zero;
    printf("Polynomial execution with one variable (x)\n");
    printf("-1 to exit\n");
    while(flash!=-1){
        printf("Specify the coefficient\n");
        scanf("%d", &c);
        printf("Specify the degree\n");
        scanf("%d", &d);
        struct poly * newterm = (struct poly*)malloc(sizeof(struct poly));
        newterm->coeff = c;
        newterm->deg = d;
        travel->next = newterm;
        newterm->next = NULL;
        travel = newterm;
        printf("Continue?\n");
        scanf("%d", &flash);
    }
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
