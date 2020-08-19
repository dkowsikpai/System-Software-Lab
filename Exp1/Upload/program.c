/**
 * Program: Implementation of scheduling Algorithm
 * Author: Kowsik Nandagopan D, CSE, GEC Thrissur
*/

// Header File
#include<stdio.h>
#include<stdlib.h>
// Setting Quantum for Round Robin
#define QUANTUM 3

// Global Variables: Number of processes n, at: Arrival Time
// bt: Burst Time, tat: Turn Arround Time, wt: Wait Time, prio: Priority
int n=0, *at, *bt, *tat, *wt, *prio;
// Temp Variables
int a, b , c, i = 0;

// Print to file file pointer
FILE *fout;

// Re-read file: without quitting the program we can modify file
void reread(){
    // Reinitialization
    n = 0;
    at = NULL;
    bt = NULL;
    tat = NULL;
    wt = NULL;
    prio = NULL;
    i = 0;
    // Reading from the input.txt file
    FILE *fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    // Taking the count of number of processes
    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", &a, &b, &c);
        n++;
    }
    rewind(fptr);

    // Allocating space for the dynamic array
    at = (int*) malloc(n * sizeof(int));
    bt = (int*) malloc(n * sizeof(int));
    tat = (int*) malloc(n * sizeof(int));
    wt = (int*) malloc(n * sizeof(int));
    prio = (int*) malloc(n * sizeof(int));

    if(at == NULL || bt == NULL || tat == NULL || wt == NULL || prio == NULL){
        printf("Error! memory not allocated.");
        exit(0);
    }

    // Reading from file
    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", at+i, bt+i, prio+i);
        i++;        
    }
    fclose(fptr);
}

// First in first served Turn Around Calculation
void findTurnAroundFCFS(int n, int *at, int *bt, int *tat){
    int cum=0;
    for (int i=0; i < n; i++){
        *(tat+i) = cum - *(at+i) + *(bt + i);
        cum += *(bt + i);
    }
}

// Shortest Job First Turn Around Calculation
void findTurnAroundSJF(int n, int *at, int *bt, int *tat){
    int cum=0, count=0, t=0, min=10000, index=-1;
    while(1) {
        min=10000;
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

// Round Robin Turn Around Calculation
void findTurnAroundRR(int n, int *at, int *bt, int *tat){
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

// Priority Sheduling Turn Around Calculation
void findTurnAroundPriority(int n, int *at, int *bt, int *tat, int *prio){
    int cum=0, count=0, t=0, min=10000, index=-1;
    while(1) {
        min=10000;
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

// Waiting Time calculation in all the cases
void findWaitingTime(int n, int *bt, int *tat, int *wt){
    for (int i=0; i < n; i++){
        *(wt+i) = *(tat+i) - *(bt+i);
    }
}

// Displaying output of funtions and printing to the file
void display(){
    printf("Turn Arount Time\tWaiting Time\n");
    fprintf(fout, "Turn Arount Time\tWaiting Time\n");
    for (int i=0; i < n; i++){
        // printf("%d\n", *(tat + i));
        printf("%d\t\t\t%d\n", *(tat + i), *(wt + i));
        fprintf(fout, "%d\t\t\t%d\n", *(tat + i), *(wt + i));
    }
}

void main(){
    int menu=5, flag=1;
    // Printing Output to output.txt
    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // Reading and printing the contents of input.txt to console and output.txt
    printf("Input file contents:\n");
    fprintf(fout, "Input file contents:\n");
    FILE *fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    printf("Arrival Time\tBurst Time\tPriority\n");
    fprintf(fout, "Arrival Time\tBurst Time\tPriority\n");
    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", &a, &b, &c);
        printf("%d\t\t%d\t\t%d\n", a, b, c);
        fprintf(fout, "%d\t\t\t\t%d\t\t\t\t%d\n", a, b, c);
    }
    
    // Menu Driver
    while (flag){
        printf("-----------------Menu----------------\n1.FCFS\n2.SJF\n3.RR\n4.Priority\n5.Exit\nSelect:");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1: 
            printf("First-Come-First-Serverd\n");
            fprintf(fout, "First-Come-First-Serverd\n");
            reread();
            findTurnAroundFCFS(n, at, bt, tat);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;

        case 2:
            printf("Shortest-Job-First\n");
            fprintf(fout, "Shortest-Job-First\n");
            reread();
            findTurnAroundSJF(n, at, bt, tat);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;

        case 3:
            printf("Round-Robin\n");
            fprintf(fout, "Round-Robin\n");
            reread();
            findTurnAroundRR(n, at, bt, tat);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;

        case 4:
            printf("Priority\n");
            fprintf(fout, "Priority\n");
            reread();
            findTurnAroundPriority(n, at, bt, tat, prio);
            findWaitingTime(n, bt, tat, wt);
            display();
            break;
        
        case 5:
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
