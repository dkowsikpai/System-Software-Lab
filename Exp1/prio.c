#include<stdio.h>
#include<stdlib.h>

void findBurstTime(int n, int *at, int *bt, int *tat, int *prio){
    int cum=0, count=0, t=0, min=1000, index=-1;
    while(1) {
        min=1000;
        index=-1;
        for (int i=0; i<n; i++){
            if (*(at+i) <= t && *(at+i) != -1 && *(prio+i) < min){
                min = *(prio+i);
                index = i;
            }
        }
        t += *(bt+index);
        *(tat+index) = t - *(at+index);
        count++;
        *(at+index) = -1;
        if (count >= n){
            break;
        }
    }
}

void findWaitingTime(int n, int *bt, int *tat, int *wt){
    for (int i=0; i < n; i++){
        *(wt+i) = *(tat+i) - *(bt+i);
    }
}

void main(){
    int n=0, *at, *bt, *tat, *wt, *prio;
    int a, b , c, i = 0;

    FILE *fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", &a, &b, &c);
        n++;
    }
    rewind(fptr);

    at = (int*) malloc(n * sizeof(int));
    bt = (int*) malloc(n * sizeof(int));
    tat = (int*) malloc(n * sizeof(int));
    wt = (int*) malloc(n * sizeof(int));
    prio = (int*) malloc(n * sizeof(int));

    if(at == NULL || bt == NULL || tat == NULL || wt == NULL || prio == NULL){
        printf("Error! memory not allocated.");
        exit(0);
    }

    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", at+i, bt+i, prio+i);
        i++;        
    }

    findBurstTime(n, at, bt, tat, prio);
    findWaitingTime(n, bt, tat, wt);

    printf("Turn Arount Time\tWaiting Time\n");
    for (int i=0; i < n; i++){
        // printf("%d\n", *(tat + i));
        printf("%d\t\t\t%d\n", *(tat + i), *(wt + i));
    }

    

    free(at);
    free(bt);
    free(tat);
    free(wt);
    free(prio);
    fclose(fptr);
}