/**
 * Implementation of banker's algorithm
 * Author: Kowsik Nandagopan D
*/

// Library
#include <stdio.h>
#include <stdlib.h>

void main (){
    // Initializing Process, resource
    int process, res, a, or=0, proc=-1; 

    // Nums.txt gives the number of processes and resources
    FILE *f;
    if ((f = fopen("nums.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // reading num.txt
    while (!feof(f)){
        fscanf(f, "%d\t%d\t%d", &process, &res, &proc);
    }

    // Allocating memory space required
    int *max[process], *alloc[process], *need[process];
    int *p = (int*)malloc(process * sizeof(int));
    int *order = (int*)malloc(process * sizeof(int));
    int *avail = (int*)malloc(process * sizeof(int));
    int *request = (int*)malloc(process * sizeof(int));
    for (int i=0; i<process; i++) {
        max[i] = (int *)malloc(res * sizeof(int)); 
        alloc[i] = (int *)malloc(res * sizeof(int)); 
        need[i] = (int *)malloc(res * sizeof(int)); 
        p[i] = 0;
    }

    // Reading maximum allowed resource from max.txt
    FILE *fptr;
    if ((fptr = fopen("max.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    int r=0, c=0;
    while (!feof(fptr)){
        while (c < res){
            fscanf(fptr, "%d\t", &a);
            max[r][c] = a;
            c++;
        }
        r++;
        c = 0;
    }
    fclose(fptr);

    // Reading Allocated resource from max.txt
    if ((fptr = fopen("alloc.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    r=0; c=0;
    while (!feof(fptr)){
        while (c < res){
            fscanf(fptr, "%d\t", &a);
            alloc[r][c] = a;
            c++;
        }
        r++;
        c = 0;
    }
    fclose(fptr);

    // Reading Allocated resource from max.txt
    if ((fptr = fopen("avail.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    r=0; c=0;
    while (!feof(fptr)){
        fscanf(fptr, "%d\t", &a);
        avail[c] = a;
        c++;
    }
    fclose(fptr);

    // Reading if requested process resource from req.txt
    if ((fptr = fopen("req.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    r=0; c=0;
    while (!feof(fptr)){
        fscanf(fptr, "%d\t", &a);
        request[c++] = a;
    }
    fclose(fptr);

    // Adding request to Allocated list
    if (proc != -1)
        for (int j=0; j<res; j++){
            alloc[proc][j] += request[j];
        }    

    // Calculating need matrix
    for (int i=0; i<5; i++){
        for (int j=0; j<3; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Calculating for sequense
    int oldc=process; c = process;
    do{
        // If process were left unchanged while will break
        oldc = c;
        // Looping through processes
        for (int i=0; i<process; i++){
            // If process is unallocated
            if (p[i] == 0){
                // If loop allocatable flag = 0; else flag = 1;
                int flag = 0;
                // Looping through resources
                for (int j=0; j<res; j++){
                    // Checking allocatable or not
                    if (avail[j] < need[i][j] || max[i][j] < need[i][j]){
                        flag = 1;
                        break;
                    }
                }

                // If allocatable
                if (flag == 0){
                    printf("P%d - ", i);
                    // Soring the process sequence
                    order[or++] = i;
                    // Printing the sequence and adding to the available (if process is removed from the list)
                    for (int j=0; j<res; j++){
                        // Adding back
                        avail[j] += need[i][j];
                        printf("%d\t", avail[j]);
                    }
                    printf("\n");
                    // Allocating
                    p[i] = 1;
                    // Reducing process count in ready queue
                    c--;
                }
            }
        }
        // Checking condition
    } while (oldc > c); // If process list remains unchange it exits
    if (c==0) { // If safe state
        printf("Safe Sequence exist\n");
        for (int j=0; j<or; j++){
            // Print sequence
            printf("P%d->", order[j]);
        }
    }
    else printf("REQUEST DENIED"); // If no safe sequence is found
    printf("\n");
}