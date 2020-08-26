#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fout; 

typedef struct {
    int id;
    char val;
    int allocated;
} SeqNode;

typedef struct {
  int p_id;
  char val;
  int index;
  int next_index;
  int allocated;
} LinkedNode;

typedef struct {
    int p_id;
    int allocated;
    int index;
    char val;
    int index_length;
    int *addr;
}IndexedNode;

void sequential(){
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
    fprintf(fout, "Enter the number of blocks: ");
    scanf("%d", &n);
    fprintf(fout, "%d\n", n);
    printf("File Content\nStarting Address\tLength\tContent\n");
    fprintf(fout, "File Content\nStarting Address\tLength\tContent\n");
    while (!feof(fptr)) {
        fscanf(fptr, "%d\t%d\t%s", &ind, &len, c);
        printf("%d\t\t\t%d\t\t%s\n", ind, len, c);
        fprintf(fout, "\t\t%d\t\t\t%d\t\t%s\n", ind, len, c);
    }
    rewind(fptr);
    seq = (SeqNode*)malloc(n*sizeof(SeqNode));
    for (i=0; i<n; i++){
        (seq+i)->id = i+1;
        (seq+i)->allocated = -1;
        (seq+i)->val = ' ';
    }
    int last = 0;
    printf("\nRequest's Starting Address: \n");
    fprintf(fout, "\nRequest's Starting Address: \n");
    while (!feof(fptr)) {
        fscanf(fptr, "%d\t%d\t%s", &ind, &len, c);
        if (last+len < n && (seq+ind-1)->allocated == -1){
            printf("%d\tAllocated\n", ind);
            fprintf(fout, "%d\tAllocated\n", ind);
            for (int j=0; j<len; j++){
                (seq+ind-1+j)->allocated = ind-1;
                (seq+ind-1+j)->val = c[j];
                last = ind-1+j;
            }
        } else {
            printf("%d\tNot allocated\n", ind);
            fprintf(fout, "%d\tNot allocated\n", ind);
        }
    }

    printf("Status of memory blocks\t\tBlocks\t\tContents\n");
    fprintf(fout, "Status of memory blocks\t\tBlocks\t\tContents\n");
    for (i=0; i<n; i++){
        printf("\t%d\t\t\t%s\t%c\n", (seq+i)->id, ((seq+i)->allocated == -1)? "Free":"Occupied", (seq+i)->val);
        fprintf(fout, "\t\t%d\t\t\t\t\t%s\t\t%c\n", (seq+i)->id, ((seq+i)->allocated == -1)? "Free":"Occupied", (seq+i)->val);
        printf("-----------------------------------------------------\n");
        fprintf(fout, "-----------------------------------------------------\n");
    }
    fclose(fptr);
}

void linked(){
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
    fprintf(fout, "Enter the number of blocks: ");
    scanf("%d", &n);
    fprintf(fout, "%d\n", n);
    // n=10;
    printf("Memory File Content\nCurrent Node\tNext Node\n");
    fprintf(fout, "Memory File Content\nCurrent Node\tNext Node\n");
    while (!feof(mem)) {
        fscanf(mem, "%d\t%d", &ind, &next);
        printf("%d\t\t%d\n", ind, next);
        fprintf(fout, "%d\t\t%d\n", ind, next);
    }
    rewind(mem);

    printf("Process File Content\nProcess\tLength\tContent\n");
    fprintf(fout, "Process File Content\nProcess\tLength\tContent\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        printf("P%d\t\t%d\t\t%s\n", p_id, len, c);
        fprintf(fout, "P%d\t\t%d\t\t%s\n", p_id, len, c);
    }
    rewind(proc);
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

    printf("\nProcess\t\tStart\t\tEnd\t\tStatus\n");
    fprintf(fout, "\nProcess\t\tStart\tEnd\t\tStatus\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        // printf("%d\t%d\t%s\n", p_id, len, c);
        printf("P%d\t\t%d\t", p_id, last+1);
        fprintf(fout, "\tP%d\t\t%d\t", p_id, last+1);
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
        if (end == -1){ 
            printf("\t%s\t\t%s\n", " ", "Not Alloted");
            fprintf(fout, "\t%s\t\t%s\n", " ", "Not Alloted");
        }
        else {
            printf("\t%d\t\t%s\n", end+1, "Alloted");
            fprintf(fout, "\t%d\t\t%s\n", end+1, "Alloted");
        }
        end=-1;

    }

    // printf("\n");
    // for (int i=0; i<n; i++){
    //     printf("%d\t%c\t%d\n", (lin+i)->index, (lin+i)->val, (lin+i)->p_id);
    // }

    rewind(proc);
    printf("\nContents of Process\n");
    fprintf(fout, "\nContents of Process\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        // printf("%d\t%d\t%s\n", p_id, len, c);
        printf("P%d\n", p_id);
        fprintf(fout, "P%d\n", p_id);
        for (int i=0; i<n; i++){
            if (p_id == (lin+i)->p_id){
                printf("\t%d\t%c\n", i+1, (lin+i)->val);
                fprintf(fout, "\t%d\t%c\n", i+1, (lin+i)->val);
            }
        }
        printf("---------------------------------\n");
        fprintf(fout, "---------------------------------\n");
    }
    fclose(proc);
    fclose(mem);
}

void indexed (){
    IndexedNode *indNode;
    FILE *proc;
    int n=0, ind, p_id, len;
    char c[20];
    if ((proc = fopen("indexed_input.txt", "r")) == NULL) {
        printf("Error! opening memory link file");
        exit(1);
    }
    printf("Enter the number of blocks: ");
    fprintf(fout, "Enter the number of blocks: ");
    scanf("%d", &n);
    fprintf(fout, "%d\n", n);
    // n = 10;
    printf("Process File Content\nProcess\tLength\tIndex\tContent\n");
    fprintf(fout, "Process File Content\nProcess\tLength\tIndex\tContent\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        printf("P%d\t%d\t%d\t%s\n", p_id, len, ind, c);
        fprintf(fout, "\tP%d\t\t%d\t\t%d\t\t%s\n", p_id, len, ind, c);
    }
    rewind(proc);
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
    printf("\nProcess\t\tIndex\t\tBlocks\t\tStatus\n");
    fprintf(fout, "\nProcess\t\tIndex\t\tBlocks\t\tStatus\n");
    printf("-----------------------------------------------------\n");
    fprintf(fout, "-----------------------------------------------------\n");
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        // printf("%d\t%d\t%d\t%s\n", p_id, len, ind, c);
        if ((indNode+ind-1)->index != -1){
            printf("P%d\t%d\t", (indNode+ind-1)->p_id, ind);
            fprintf(fout, "P%d\t\t\t%d\t\t\t", (indNode+ind-1)->p_id, ind);
            for (int j=0; j<(indNode+ind-1)->index_length; j++){
                printf("%d, ", (indNode+ind-1)->addr[j]+1);
                fprintf(fout, "%d, ", (indNode+ind-1)->addr[j]+1);
            }
            printf("\t\tAlloted\n");
            fprintf(fout, "\t\t\tAlloted\n");
            printf("-----------------------------------------------------\n");
            fprintf(fout, "-----------------------------------------------------\n");
        } else {
            printf("P%d\t%d\t\t\t\tNot Alloted\n", p_id, ind);
            fprintf(fout, "P%d\t\t\t%d\t\t\t\t\t\tNot Alloted\n", p_id, ind);
            printf("-----------------------------------------------------\n");
            fprintf(fout, "-----------------------------------------------------\n");

        }
    }
    printf("\nAllocation\n");
    fprintf(fout, "\nAllocation\n");
    printf("Index\tBlock\tContents\n");
    fprintf(fout, "Index\tBlock\tContents\n");
    printf("-----------------------------------------------------\n");
    fprintf(fout, "-----------------------------------------------------\n");
    for (int i=0; i<n; i++){
        if ((indNode+i)->index != -1){
            for (int j=0; j<(indNode+i)->index_length; j++){
                printf("%d\t%d\t%c\n", i+1, (indNode+i)->addr[j]+1, (indNode + (indNode+i)->addr[j])->val);
                fprintf(fout, "%d\t\t%d\t\t%c\n", i+1, (indNode+i)->addr[j]+1, (indNode + (indNode+i)->addr[j])->val);
                printf("-----------------------------------------------------\n");
                fprintf(fout, "-----------------------------------------------------\n");
            }
        }
    }
    fclose(proc);
}


void main (){
    int flag=1, menu=4;
    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while (flag){
        printf("-----------------Menu----------------\n1.Sequential\n2.Linked\n3.Indexed\n4.Exit\nSelect:");
        fprintf(fout, "-----------------Menu----------------\n1.Sequential\n2.Linked\n3.Indexed\n4.Exit\nSelect:");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1: 
            printf("\nSequential Allocation\n");
            fprintf(fout, "\nSequential Allocation\n");
            sequential();
            break;
        case 2: 
            printf("\nLinked Allocation\n");
            fprintf(fout, "\nLinked Allocation\n");
            linked();
            break;
        case 3: 
            printf("\nIndexed Allocation\n");
            fprintf(fout, "\nIndexed Allocation\n");
            indexed();
            break;
        case 4:
            flag=0;
            break;

        default:
            printf("Invalid Menu\n");
            fprintf(fout, "Invalid Menu\n");
            break;
        }
    }
    fclose(fout);
}