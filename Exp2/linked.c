#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
  int p_id;
  char val;
  int index;
  int next_index;
  int allocated;
} LinkedNode;

void main (){
    LinkedNode *lin, *pointer;
    FILE *mem, *proc;
    int n=0, ind, next, len, p_id;
    char c[20];
    if ((mem = fopen("linked_memory_input.txt", "r")) == NULL) {
        printf("Error! opening memory link file");
        exit(1);
    }
    if ((proc = fopen("linked_process_input.txt", "r")) == NULL) {
        printf("Error! opening process file");
        exit(1);
    }
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    // n=10;
    lin = (LinkedNode*)malloc(n*sizeof(LinkedNode));
    for (int i=0; i<n; i++){
        (lin+i)->index = i+1;
        (lin+i)->next_index = -1;
        (lin+i)->allocated = -1;
        (lin+i)->p_id = -1;
    }
    int free=0, links=0;
    while (!feof(mem)) {
        fscanf(mem, "%d\t%d", &ind, &next);
        (lin+ind-1)->next_index = next;  
        free++;   
    }
    links = free;
    int last=0, num_process=0, end=-1;

    printf("Process\t\tStart\t\tEnd\t\tStatus\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        // printf("%d\t%d\t%s\n", p_id, len, c);
        printf("P%d\t\t%d\t", p_id, last+1);
        if (free-len >= 0 && (lin+last)->allocated == -1){
            num_process++;
            for (int j=0; j<len; j++){
                (lin+last)->allocated = p_id;
                (lin+last)->val = c[j];
                (lin+last)->p_id = p_id;
                end = last;
                last = (lin+last)->next_index-1;
                free--;
            }    
        }
        if (end == -1) printf("\t%s\t\t%s\n", " ", "Not Alloted");
        else printf("\t%d\t\t%s\n", end+1, "Alloted");
        end=-1;

    }

    // printf("\n");
    // for (int i=0; i<n; i++){
    //     printf("%d\t%c\t%d\n", (lin+i)->index, (lin+i)->val, (lin+i)->p_id);
    // }

    rewind(proc);
    printf("\nContents of Process\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        // printf("%d\t%d\t%s\n", p_id, len, c);
        printf("P%d\n", p_id);
        for (int i=0; i<n; i++){
            if (p_id == (lin+i)->p_id){
                printf("\t%d\t%c\n", i+1, (lin+i)->val);
            }
        }
        printf("---------------------------------\n");
    }
    
    
}