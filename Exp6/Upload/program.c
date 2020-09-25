/**
 * Implementation of producer consumer problem
 * Author: Kowsik Nandagopan D
*/

// Library
#include<stdio.h>
#include<stdlib.h>

// Global variable for buffer size, and semaphores
int buffer,empty,full=0,mutex=1;
    
// Wait Semaphore
int wait(int s){
    while(s<=0); //Busy waiting
    return --s; // Counting semaphore
}

// Signal Semaphore
int signal(int s){
    return ++s; // Releasing by incrementing
}

// Producer
void produce(){
    int i;
    if(mutex==1 && empty!=0){
        mutex=wait(mutex);
        empty=wait(empty);
        // Add to buffer
        full=signal(full);            
        mutex=signal(mutex);
    
    }else
        printf("\n Buffer is Full , cannot produce\n"); // If full
        
}

// Consumer
void consume(){
    int i;
    if(mutex==1 && full!=0){
        mutex=wait(mutex);
        full=wait(full);
        // Remove from buffer
        empty=signal(empty);
        mutex=signal(mutex);
        
    }else
        printf("\nConsumer cannot consume : Buffer empty\n"); // If empty
        
}
    
    
void main(){
    // Initialization
    int i,n,*p,*c,ci,pi;
    FILE *f;
    if ((f = fopen("nums.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // reading num.txt for buffer size and number of n
    while (!feof(f)){
        fscanf(f, "%d\t%d", &buffer, &n);
    }
    // Initializing empty size of semaphore as buffer size
    empty = buffer;
    fclose(f);

    // Initializing the producer and consumer rate array
    p = (int*)malloc(n*sizeof(int));
    c = (int*)malloc(n*sizeof(int));

    i = 0;
    if ((f = fopen("rate.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // reading rate.txt
    while (!feof(f)){
        fscanf(f, "%d\t%d", (p+i), (c+i)); // Input rate of <Producer Rate> <Tab> <Consumer Rate>
        i++;
    }
    empty = buffer;
    fclose(f);
    
    printf("Buffer spaces filled: %d",full);
    consume(c[0]);

    // Running infinite loop
    ci=0;pi=0;
    while(1)
    {
        // Running consumer
        if(full>c[ci])
        {    
            for(i=0;i<c[ci];++i)
                consume();
            printf("\nConsumer consumed successfully");
            printf("\nBuffer spaces filled: %d\n",full);
            ci++;
        }
        else // Running Producer
        {
            for(i=0;i<p[pi];++i)
                produce();
            printf("\nProducer produced successfully");
            printf("\nBuffer spaces filled: %d\n",full);
            pi++;
        }
        // Breaking if all items are consumed
        if(ci==n)
            break;
    }
}
    
