#include<stdio.h>
#include<stdlib.h>

void main() {
    int a, proc, res;

    FILE *f;
    if ((f = fopen("nums.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (!feof(f)){
        fscanf(f, "%d\t%d", &proc, &res);
        // printf("%d\n", a);
    }


    int *arr[proc]; 
    for (int i=0; i<proc; i++) 
         arr[i] = (int *)malloc(res * sizeof(int)); 

    FILE *fptr;
    if ((fptr = fopen("max.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    int r=0, c=0;
    while (!feof(fptr)){
        while (c < res){
            fscanf(fptr, "%d\t", &a);
            arr[r][c] = a;
            c++;
        }
        r++;
        c = 0;
    }

    for (int i=0; i<proc; i++) {
        for (int j=0; j<res; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}