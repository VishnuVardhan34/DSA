#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

int findMax(int array[], int h){

    int max=array[0];
    for(int j=1; j<h; j++){
        if(max<array[j]){
            max=array[j];
        }
        else{
            continue;
        }
    }
    return max;
}

int findDigits(int max) {
    int digit = 0;
    while (max != 0) {
        max = max / 10;
        digit++;
    }
    return digit;
}


int main(){

    int n=6;
    int radix[6];
    int radix2[n];
    printf("Specify %d elements\n", n);
    for(int i=0; i<n; i++){
        scanf("%d", &radix[i]);
    }

    int max= findMax(radix, n);

    int digit = findDigits(max);
    int it=1;
    int exp=1;
    int countarray[10];
    while(digit>0){
        for(int i=0; i<10; i++){
            countarray[i]=0;
        }
        for(int i=0; i<n; i++){
            countarray[(radix[i]/exp)%10]++;
        }
        for(int i=1; i<=10; i++){
            countarray[i] = countarray[i] + countarray[i-1];
        }
        for (int i = n - 1; i >= 0; i--) {
        int currentDigit = (radix[i] / exp) % 10;
        radix2[countarray[currentDigit] - 1] = radix[i];
        countarray[currentDigit]--;
    }
        for(int i=0; i<n; i++){
            radix[i]=radix2[i];
        }
        digit--;
        exp=exp*10;

        printf("\nIteration: %d\n", it);
        for(int j=0; j<n; j++){
            printf("%d\t", radix[j]);
        }
        it++;
    }
    printf("\nSorted array:\n");
    for(int j=0; j<n; j++){
        printf("%d\t", radix[j]);
    }
    return 0;
}


