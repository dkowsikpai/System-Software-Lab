/**
    * Simulate the disk scheduling algorithms - SCAN and C-SCAN, 
    * compare the head movements in each algorithm for forward, random and reverse order of the input. 
    * 
    * Kowsik Nandagopan D,
    * CSE S5
    * Roll no 31, TCR18CS031
*/
// Library
#include <stdio.h>
#include <stdlib.h>

// Scan / Elevator Algorithm
int scan(int *rq, int header, int n) {
    // Init
    int total=0, init, prev, i, p, temp;
    int *req;
    req = (int*)malloc(n * sizeof(int));
    for (i=0; i<n; i++)
        req[i] = rq[i];

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
    printf("Request order: ");
    while (p > 0){
        // Forward pass to 199 section
        while (i < n) {
            total += abs(header - req[i]); // Adding head movements
            header = req[i]; // new head position
            printf("%d->", req[i]);
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
            printf("%d->", req[i]);
            i--;
            p--; // Reducing the request count
        }
        
    }
    
    // Printing
    printf("\nTotal Head movements: %d\n", total);
    // fclose(f);
    return total;

}


// C-Scan Algorithm
int cscan(int *rq, int header, int n){
    // Init
    int total=0, prev, temp, i, p, init;
    int *req;
    req = (int*)malloc(n * sizeof(int));
    for (i=0; i<n; i++)
        req[i] = rq[i];

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

    // var init 
    p = n;
    i = init+1;
    printf("Request order: ");
    while (p > 0){
        // Foward Pass to 199
        while (i < n) {
            // printf("%d->%d\n", header, req[i]);
            total += abs(header - req[i]);
            header = req[i];
            printf("%d->", req[i]);
            i++;
            p--;
        }
        total += abs(header - 199) + 199; // Resetting header to 0
        header = 0;
        i = 0;  
        // Forward pass to initial header position
        while (i <= init) {
            // printf("%d->%d\n", header, req[i]);
            total += abs(header - req[i]);
            header = req[i];
            printf("%d->", req[i]);
            i++;
            p--;
        }      
    }
    
    // Printing
    printf("\nTotal Head movements: %d\n", total);
    // fclose(f);
    return total;
}

void main() {
    // Initialisation
    int *req, *req_rev, *req_rand, flag=1, menu=4, header, n, temp, i;
    int tot_for, tot_rev, tot_rand;
    int ctot_for, ctot_rev, ctot_rand;
    FILE *f;

    // Reading file
    if ((f = fopen("forward.txt", "r")) == NULL) {
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
    fclose(f);

    // Init header
    printf("Enter initial header position: ");
    scanf("%d", &header);

    // Simulation
    //=============================== Forward ===================================
        printf("Input order: ");
    for(i=0; i<n; i++)
        printf("%d->", req[i]);
    printf("\n");

    printf("----------------------- SCAN in forward input --------------------\n");
    tot_for = scan(req, header, n);
    printf("----------------------- C-SCAN in forward input --------------------\n");
    ctot_for = cscan(req, header, n);

    printf("\n\n");
    
    
    
    // ============================================ Reverse ==================================
    req_rev = (int*)malloc(n * sizeof(int));
    for(i=0; i<n; i++) {
        req_rev[n-i-1] = req[i];
    }

    printf("Input order: ");
    for(i=0; i<n; i++)
        printf("%d->", req_rev[i]);
    printf("\n");
    printf("----------------------- SCAN in reverse input --------------------\n");
    tot_rev = scan(req_rev, header, n);
    printf("----------------------- C-SCAN in reverse input --------------------\n");
    ctot_rev = cscan(req_rev, header, n);


    // ============================================ Random ======================================
    req_rand = (int*)malloc(n * sizeof(int));
    for(i=0; i<n; i++) {
        req_rand[i] = req[i];
    }

    if (n > 1) { // Just a test to avoid negative numbers on n-i
        for (i = 0; i < n - 1; i++) {
          int j = i + rand() / (RAND_MAX / (n - i) + 1); // RAND MAX is the largest value rand can give. To avoid division by zero and same index we ad 1 to denominator
          int t = req_rand[j]; // Swapping
          req_rand[j] = req_rand[i];
          req_rand[i] = t;
        }
    }

    printf("\n\n");

    printf("Input order: ");
    for(i=0; i<n; i++)
        printf("%d->", req_rand[i]);
    printf("\n");
    printf("----------------------- SCAN in random input --------------------\n");
    tot_rand = scan(req_rand, header, n);
    printf("----------------------- C-SCAN in random input --------------------\n");
    ctot_rand = cscan(req_rand, header, n);


    // ============================ Table ====================================
    printf("\n\n----------------------- Comparison ----------------------\n");
    printf("Order\t\tSCAN\t\tC-SCAN\n");
    printf("Forward\t\t%d\t\t%d\n", tot_for, ctot_for);
    printf("Random\t\t%d\t\t%d\n", tot_rand, ctot_rand);
    printf("Reverse\t\t%d\t\t%d\n", tot_rev, ctot_rev);
    
}
