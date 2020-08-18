#include<stdio.h>
#include<stdlib.h>
#define QUANTUM 3

int n=0, *at, *bt, *tat, *wt, *prio;
int a, b , c, i = 0;

void reread(){
    n = 0;
    at = NULL;
    bt = NULL;
    tat = NULL;
    wt = NULL;
    prio = NULL;
    i = 0;
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
    fclose(fptr);
}

void findBurstTimeFCFS(int n, int *at, int *bt, int *tat){
    int cum=0;
    for (int i=0; i < n; i++){
        *(tat+i) = cum - *(at+i) + *(bt + i);
        cum += *(bt + i);
    }
}

void findBurstTimeSJF(int n, int *at, int *bt, int *tat){
    int cum=0, count=0, t=0, min=1000, index=-1;
    while(1) {
        min=1000;
        index=-1;
        for (int i=0; i<n; i++){
            if (*(at+i) <= t && *(at+i)!=-1 && *(bt+i) < min) {
                min = *(bt+i);
                index=i;
            }
        }
        t += min;
        cum += *(bt+index);
        *(tat+index) = cum - *(at+index);
        *(at+index) = -1;
        count++;
        if (count >= n){
            break;
        }
    }
}

void findBurstTimeRR(int n, int *at, int *bt, int *tat){

    int *bt_temp = (int *)malloc(n*sizeof(int));
    int count=0, t=0;

    for (int i=0; i<n; i++){
        *(bt_temp+i) = *(bt+i);
    }

    while(1) {
        for(int i=0; i < n; i++){
            if (*(at+i) <= t && *(at+i) != -1) {
                if (*(bt_temp+i) <= QUANTUM){
                    t += *(bt_temp+i);
                    *(tat+i) = t - *(at+i);
                    *(at+i) = -1;
                    count++;
                } else {
                    t += QUANTUM;
                    *(bt_temp+i) -= QUANTUM;
                }
            }
        }
        if (count >= n){
            break;
        }
    }
}

void findBurstTimePriority(int n, int *at, int *bt, int *tat, int *prio){
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

void display(){
    printf("Turn Arount Time\tWaiting Time\n");
    for (int i=0; i < n; i++){
        // printf("%d\n", *(tat + i));
        printf("%d\t\t\t%d\n", *(tat + i), *(wt + i));
    }
}

void main(){
    int menu=5, flag=1;
    while (flag){
        printf("Menu\n1.FCFS\n2.SJF\n3.RR\n4.Priority\n5.Exit\nSelect:");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("First-Come-First-Serverd\n");
            reread();
            findBurstTimeFCFS(n, at, bt, tat);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;

        case 2:
            printf("Shortest-Job-First\n");
            reread();
            findBurstTimeSJF(n, at, bt, tat);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;

        case 3:
            printf("Round-Robin\n");
            reread();
            findBurstTimeRR(n, at, bt, tat);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;

        case 4:
            printf("Priority\n");
            reread();
            findBurstTimePriority(n, at, bt, tat, prio);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;
        
        case 5:
            flag=0;
            break;

        default:
            printf("Invalid Menu\n");
            break;
        }
    }
}
