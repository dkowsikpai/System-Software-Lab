/**
 * Implementation of disk scheduling algorithm
 * Author: Kowsik Nandagopan D
*/

// Library
#include <stdio.h>
#include <stdlib.h>


// First come First Serverd
void fcfs(){
    // Initialization
    int header, total=0, prev, n=0, temp, i, p;
    int *req;

    // Reading from the file
    FILE *f;
    if ((f = fopen("req.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // Counting number of requests from file
    while (!feof(f)){
        fscanf(f, "%d\n", &temp);
        n++;
    }
    rewind(f);

    // Setting request to array pointer
    i = 0;
    req = (int*)malloc(n * sizeof(int));
    while (!feof(f)){
        fscanf(f, "%d\n", req + i);
        i++;
    }

    // Asking for the initial header position
    printf("Enter current header position: ");
    scanf("%d", &header);

    // var init
    p = n;
    i = 0;

    // Traversing through list
    while (p > 0){
        total += abs(header - req[i]); // Adding the head movements
        header = req[i]; // setting new head position
        i++;
        p--; // Reducing request count
    }

    // Printing head movements
    printf("Total Head movements: %d\n", total);

}


// Scan / Elevator Algorithm
void scan() {
    // Init
    int header, total=0, prev, n=0, temp, i, p, init;
    int *req;
    // Reading from file
    FILE *f;
    if ((f = fopen("req.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // Request Count
    while (!feof(f)){
        fscanf(f, "%d\n", &temp);
        n++;
    }
    rewind(f);

    // Setting in array
    i = 0;
    req = (int*)malloc(n * sizeof(int));
    while (!feof(f)){
        fscanf(f, "%d\n", req + i);
        i++;
    }

    // Initial head position
    printf("Enter current header position: ");
    scanf("%d", &header);

    // Soriting the request in ascending order
    for (i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (req[i] < req[j]){
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }


    // Getting initial index
    for (int j=0; j<n; j++){
        if (req[j] <= header) {
            init = j;
        } else {
            break;
        } 
    }

    // printf("i-%d\n", init);

    // var init
    p = n;
    i = init+1;
    while (p > 0){
        // Forward pass to 199 section
        while (i < n) {
            total += abs(header - req[i]); // Adding head movements
            header = req[i]; // new head position
            i++;
            p--; // Reducing request count
        }
        total += abs(header - 199); // Reseting header to 199
        header = 199;
        i = init;
        // Back pass to 0
        while (i >= 0) {
            total += abs(header - req[i]); 
            header = req[i]; // Setting new header position
            i--;
            p--; // Reducing the request count
        }
        
    }
    
    // Printing
    printf("Total Head movements: %d\n", total);
}


// C-Scan Algorithm
void cscan(){
    // Init
    int header, total=0, prev, n=0, temp, i, p, init;
    int *req;

    // Reading from file
    FILE *f;
    if ((f = fopen("req.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // Request count
    while (!feof(f)){
        fscanf(f, "%d\n", &temp);
        n++;
    }
    rewind(f);

    // Setting to Array
    i = 0;
    req = (int*)malloc(n * sizeof(int));
    while (!feof(f)){
        fscanf(f, "%d\n", req + i);
        i++;
    }

    // Initial header position
    printf("Enter current header position: ");
    scanf("%d", &header);

    // Sorting request in Ascending order
    for (i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (req[i] < req[j]){
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }


    // Initial index
    for (int j=0; j<n; j++){
        if (req[j] <= header) {
            init = j;
        } else {
            break;
        } 
    }

    // printf("i-%d\n", init);

    // var init 
    p = n;
    i = init+1;
    while (p > 0){
        // Foward Pass to 199
        while (i < n) {
            // printf("%d->%d\n", header, req[i]);
            total += abs(header - req[i]);
            header = req[i];
            i++;
            p--;
        }
        total += abs(header - 199) + 199; // Resetting header to 0
        header = 0;
        i = 0;  
        // Forward pass to initial header position
        while (i <= init) {
            printf("%d->%d\n", header, req[i]);
            total += abs(header - req[i]);
            header = req[i];
            i++;
            p--;
        }      
    }
    
    // Printing
    printf("Total Head movements: %d\n", total);
}

void main (){
    // fcfs();
    // scan();
    // cscan();
}