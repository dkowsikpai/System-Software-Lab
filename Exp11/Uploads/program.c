/**
 * Implementation of Hash table for SYMTAB
 * Author: Kowsik Nandagopan D
*/
// Library
#include<stdio.h>
#include<stdlib.h>
#include<string.h> // String operation
#include<math.h> // For pow

// Constants
#define MAX 11 // SYMTAB hash table max length
#define STRL 4 // String size allowe (4 as per test case)
#define MAXBIT 7 // Number of bits per charecter(prefer not to change)

// Global
char l[10];
void search();
// Hash table
struct symb {
        int add;
        char label[10];
}sy[MAX];

// Main
void main() {
        // Initialization
        int a[MAX],num,key,i,ch;
        char ans;
        int create(char []); // create hash index
        void lprob(int [],int,int); // Add by list probing
        void display(int []); // display hash table
        // Initializing address array
        for(i=0;i<MAX;i++)
                a[i]=0;
        // Menu
        do {
                printf("\n\n1.Create a symbol table \n2.Search in the symbol table\n3.Exit\nEnter your choice:");
                scanf("%d",&ch); // Choice
                switch(ch) {
                case 1:
                        do {
                                printf("\nEnter the address:");
                                scanf("%d",&num);
                                printf("Enter The label:");
                                scanf("%s",l);
                                key=create(l); // Get index as per label (1601891 % max)
                                // printf("%d", key);
                                lprob(a,key,num); // Add to hash table
                                printf("\nContinue(y/n): "); // Add another term or not
                                scanf("%s",&ans); 
                        } while(ans=='y');
                        display(a); // Display hash table
                        break;
                case 2:
                        search(); // Search for label
                        break;
                }
        } while(ch<=2);
}
        
int create(char label[]) {
        // int temp[MAXBIT];
        int addr = 0;
        int key = 0;
        int len = strlen(label);
        for (int i=len-1; i>=0; i--){ // read label in reverse as we need the ascii of last bit first.
                int n = (int)label[i]; // Type cast the ASCII to integer
                int j = 0; // array pointer
                while (n>0) { // Binary creation
                        // Binary Number in reverse and creates key with formula (2^x + bit at position)
                        key += (int)pow(2, (((len-i-1)*MAXBIT)+j))*(n % 2); 
                        n /= 2; // division
                        j++; // increment array pointer

                }
                // DEBUG
                // for (int k=0; k < MAXBIT; k++){
                //         printf("%d", temp[k]);
                // }
                // printf("\n");
                
        }
        // printf("\n%d", key);
        // Key is ASCII appended % max
        return key%MAX;
}
        
// List probing to store to hash table
void lprob(int a[MAX],int key,int num) {
        int flag,i,count=0;
        void display(int a[]);
        flag=0;
        if(a[key]==0) { // Checking empty or not
                a[key]=num;
                sy[key].add=num; // Adding to stuct
                strcpy(sy[key].label,l);
        } else {
                i=0;
                // If the index is already taken
                while(i<MAX) {
                        if(a[i]!=0)
                        count++; // Counting number of vacant space
                        i++;
                }
                if(count==MAX) { // If no empty space Count = Max size
                        printf("\nHash table is full");
                        display(a);
                        exit(1);
                }
                for(i=key+1;i<MAX;i++) // Checking very next index if key is alredy taken
                        if(a[i]==0) {
                                a[i]=num;
                                flag=1;
                                sy[key].add=num;
                                strcpy(sy[key].label,l);
                                break;
                        }
                for(i=0;i<key && flag==0;i++)
                        if(a[i]==0) {
                                a[i]=num;
                                flag=1;
                                sy[key].add=num;
                                strcpy(sy[key].label,l);
                                break;
                        }
        }
}

// Print to console and print to stmtab.txt
void display(int a[MAX]) {
        FILE *fp;
        int i;
        fp=fopen("symbol.txt","w");
        printf("\nThe Symbol Table is\n");
        printf("\nHashvalues\t address\t label");
        for(i=0;i<MAX;i++) {
                printf("\n%d\t\t %d\t\t %s",i,sy[i].add,sy[i].label);
                fprintf(fp,"\n%d %d %s",i,sy[i].add,sy[i].label);
        }
        fclose(fp);
        printf("\n");
        printf("\n");
}
        
// Search for label
void search() {
        FILE *fp1;
        char la[10];
        int set=0,s;
        int j,i;
        printf("Enter the label: ");
        scanf("%s",la);
        fp1=fopen("symbol.txt","r");
        for(i=0;i<MAX;i++) {
                fscanf(fp1,"%d%d",&j,&sy[i].add);
                if(sy[i].add!=0)
                fscanf(fp1,"%s",sy[i].label);
        }
        for(i=0;i<MAX;i++) {
                if(sy[i].add!=0) {
                        if(strcmp(sy[i].label,la)==0) {
                                set=1;
                                s=i;
                        }
                }
        }
        if(set==1)
        printf("\nThe label %s is present at address: %d\n",la,s);
        else
        printf("\nSymbol not present\n");
}
        
