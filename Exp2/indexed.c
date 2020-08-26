#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int p_id;
    int allocated;
    int index;
    char val;
    int index_length;
    int *addr;
}IndexedNode;

void main(){

    IndexedNode *indNode;
    FILE *proc;
    int n=0, ind, p_id, len;
    char c[20];
    if ((proc = fopen("indexed_input.txt", "r")) == NULL) {
        printf("Error! opening memory link file");
        exit(1);
    }
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    // n = 10;
    indNode = (IndexedNode*)malloc(n*sizeof(IndexedNode));
    for (int i=0; i<n; i++){
        (indNode+i)->addr = NULL;
        (indNode+i)->allocated = -1;
        (indNode+i)->val = ' ';
        (indNode+i)->p_id = -1;
        (indNode+i)->index = -1;
        (indNode+i)->index_length = -1;
    }
    int free = n;
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        // printf("%d\t%d\t%d\t%s\n", p_id, len, ind, c);
        if (free >= len+1 && (indNode+ind-1)->allocated==-1){
            (indNode+ind-1)->index = ind;
            (indNode+ind-1)->p_id = p_id;
            (indNode+ind-1)->allocated = p_id;
            (indNode+ind-1)->addr = (int*)malloc(len*sizeof(int));
            (indNode+ind-1)->index_length = len;
            free--;
            for (int j=0; j<len; j++){
                int addr = -1;
                for (int k=0; k<n; k++){
                    if ((indNode+k)->allocated == -1){
                        addr = k;
                        // printf("%d\n", k);
                        break;
                    }
                }
                // printf("%d\n", addr);
                if (addr != -1 && free >= len){
                    (indNode+ind-1)->addr[j] = addr;
                    // printf("%d\n", (indNode+ind-1)->addr[j]);
                    (indNode+addr)->val = c[j];
                    (indNode+addr)->p_id = p_id;
                    (indNode+addr)->allocated = p_id;
                    free--;
                }

            }
        }
    }

    rewind(proc);
    printf("Process\t\tIndex\t\tBlocks\t\tStatus\n");
    printf("-----------------------------------------------------\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        // printf("%d\t%d\t%d\t%s\n", p_id, len, ind, c);
        if ((indNode+ind-1)->index != -1){
            printf("P%d\t%d\t", (indNode+ind-1)->p_id, ind);
            for (int j=0; j<(indNode+ind-1)->index_length; j++){
                printf("%d, ", (indNode+ind-1)->addr[j]+1);
            }
            printf("\t\tAlloted\n");
            printf("-----------------------------------------------------\n");
        } else {
            printf("P%d\t%d\t\t\t\tNot Alloted\n", p_id, ind);
            printf("-----------------------------------------------------\n");

        }
    }
    printf("\nAllocation\n");
    printf("Index\tBlock\tContents\n");
    printf("-----------------------------------------------------\n");
    for (int i=0; i<n; i++){
        if ((indNode+i)->index != -1){
            for (int j=0; j<(indNode+i)->index_length; j++){
                printf("%d\t%d\t%c\n", i+1, (indNode+i)->addr[j]+1, (indNode + (indNode+i)->addr[j])->val);
                printf("-----------------------------------------------------\n");
            }
        }
    }

    // printf("%d", (indNode+6)->addr[1]);
}