/**
 * Implementation of dining philosopher problem
 * Author: Kowsik Nandagopan D
*/

// Header files
#include <stdio.h>
#include <unistd.h> // For sleep ();
#include <pthread.h> // For thread operations
#include <semaphore.h> // For semaphore
#include <stdlib.h> // For malloc

// Constants
#define THINKING 2 // Thincking set as 2
#define HUNGRY 1 
#define EATING 0

// Macro definition
#define LEFT (p + 4)%N
#define RIGHT (p + 1)%N

// Global
int N; // Number of philosophers
int* state; // State of N philosophers
int* phil; // Philosopher numbering { 0, 1, 2, 3, 4 ... }

sem_t mutex; // Mutex -> Binary Semaphore
sem_t *Chop; // Binary semaphore for the N chosticks

// Test whether LEFT and RIGHT philosopher is eating. If not middle one can eat
void test(int p) {
    if (state[p] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){ // Condition
        state[p] = EATING; // If satisfied state is to eat
        sleep(2); // Wait for 2ms
        printf("Philosopher %d takes fork %d  and %d from table\n", p+1, LEFT+1, RIGHT+1); // Print
        printf("Philosopher %d is Eating\n", p+1);

        // Release chopstic semaphore after 2ms of eating
        sem_post(&Chop[p]);
    }
}

// Semaphore operation for eating
void take_fork(int p){
    sem_wait(&mutex); // Mutex capture
    
    state[p] = HUNGRY; // set state to hungry
    printf("Philosopher %d is hungry\n", p+1); // print
    test(p); // test whether the philosopher LEFT and RIGHT is THINKING and capture

    sem_post(&mutex); // Release Lock
    sem_wait(&Chop[p]); // Set thesemaphore to wait is not available
    sleep(1);
}

// Put the fork to dining table
void put_fork(int p){
    sem_wait(&mutex); // cature mutex lock

    state[p] = THINKING; // state to thinking
    printf("Philosopher %d put fork %d and %d on table\n", p+1, LEFT+1, RIGHT+1); // print
    printf("Philosopher %d thinking\n", p+1);

    test(LEFT); // activate the left philosopher
    test(RIGHT); // activate right philosopher

    sem_post(&mutex); // release mutex
}

// Thread function: accepts philosopher numbering.
void* philosopher(void* argv){
    while (1){ // infinite operation
        int *i=argv; // phil[i]
        sleep(1); // wait for 1ms. To complete printing in the main function
        take_fork(*i); // take fork from table
        put_fork(*i); // put fork to table
    }
}

void main (){
    // initialization
    int i = 0;
    // Setting number of philosophers
    printf("Enter the number of Philosophers: ");
    scanf("%d", &N);

    // Setting the state and philosopher number
    state = (int*)malloc(N*sizeof(int));
    phil = (int*)malloc(N*sizeof(int)); 
    for (i=0; i<N; i++){
        state[i] = 0; // Default. Will change value in thread
        phil[i] = i; // { 0, 1, 2, 3, 4 ...}
    }

    // DEBUGING
    // for (i=0; i<N; i++){
    //     printf("%d-%d\n", state[i], phil[i]);
    // }

    // Initializing number of threads and number of semaphore based on N
    pthread_t* th;
    th = (pthread_t*)malloc(N*sizeof(pthread_t)); // N threads for N philosophers
    Chop = (sem_t*)malloc(N*sizeof(sem_t)); // N chopstics in between N philosophers

    sem_init(&mutex, 0, 1); // Initialize mutex with value 1. Semaphore associated with thread
    for (i=0; i<N; i++)
        sem_init(&Chop[i], 0, 0); // Initialize mutex with value 0. Semaphore associated with thread
    
    for (i=0; i<N; i++){
        pthread_create(&th[i], NULL, philosopher, &phil[i]); // Create thread and call
        printf("Philosopher %d is thinking\n", i+1); // Will be executed when the sleep(1) is executed in thread.
    }

    for (i=0; i<N; i++)
        pthread_join(th[i], NULL); // Wait for all thread to complete before stopping main function
}