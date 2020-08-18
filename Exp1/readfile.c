#include<stdio.h>
#include<stdlib.h>

void main(){
    int a, b , c;
    FILE *fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", &a, &b, &c);
        printf("%d\t%d\t%d\n", a, b, c);
    }
    printf("end");
}