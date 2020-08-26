#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int id;
    char val;
    int allocated;
} SeqNode;

void main() {
    SeqNode *seq;
    int i;
    FILE *fptr;
    int n=0, ind, len;
    char c[20];
    if ((fptr = fopen("sequential_input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    seq = (SeqNode*)malloc(n*sizeof(SeqNode));
    for (i=0; i<n; i++){
        (seq+i)->id = i+1;
        (seq+i)->allocated = -1;
        (seq+i)->val = ' ';
    }
    int last = 0;
    printf("Request's Starting Address: \n");
    while (!feof(fptr)) {
        fscanf(fptr, "%d\t%d\t%s", &ind, &len, c);
        if (last+len < n && (seq+ind-1)->allocated == -1){
            printf("%d\tAllocated\n", ind);
            for (int j=0; j<len; j++){
                (seq+ind-1+j)->allocated = ind-1;
                (seq+ind-1+j)->val = c[j];
                last = ind-1+j;
            }
        } else {
            printf("%d\tNot allocated\n", ind);
        }
    }

    printf("Status of memory blocks\t\tBlocks\t\tContents\n");
    for (i=0; i<n; i++){
        printf("\t%d\t\t\t%s\t%c\n", (seq+i)->id, ((seq+i)->allocated == -1)? "Free":"Occupied", (seq+i)->val);
        printf("-----------------------------------------------------\n");
    }
        
}
