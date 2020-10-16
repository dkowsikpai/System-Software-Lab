        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
         
        struct node {
            char name[100];
            int file_count;
            struct node *dlink, *flink;
            char location[100];
            int type;
            int size;
            char created_on[100];
            char permissions[100];
        }*ptr, *top, *nodeptr,*x,*p;
         
        void main() {
            char search[100];
            top = NULL;    
            
            while(1) {
                printf("\n\nFILE ORGANISATION");
                printf("\n1. Create Node");
                printf("\n2. Delete Node");
                printf("\n3. Search Node");
                printf("\n4. Display");
                printf("\n5. Exit");
                
                int choice,f=0;
                printf("\nEnter choice: ");
                scanf("%d", &choice);
                
                switch(choice) {
                    case 1: 
                            ptr = (struct node*)malloc(sizeof(struct node));
                            printf("\nEnter name: ");
                            scanf("%s", ptr->name);
                            
                            // Creating new node
                            for(nodeptr = top; nodeptr != NULL; nodeptr = nodeptr->flink) {
                                if(strcmp(nodeptr->name, ptr->name) == 0) {
                                    printf("\nFile Already Exists");
                                    f++;
                                    break;
                                } 
                              }                     
                            if(f==0)
                            {
                            printf("Enter type: ");
                            scanf("%d", &ptr->type);
                            if(ptr->type == 0) ptr->size = 1;
                            else{ x=top;
                            while(x!=NULL){
                                if(strcmp(x->name, search)==0) {
                                    printf("\nFile Deleted");
                                    x->flink=x->flink->flink;
                                    break;
                                }
                                x=x->flink;
                                printf("Enter size: ");
                                scanf("%d", &ptr->size);
                            }
                            printf("Enter date: ");
                            scanf("%s", ptr->created_on  );
                            printf("Enter permissions: ");
                            scanf("%s", ptr->permissions);
                            
                            ptr->file_count = 1;
                            strcpy(ptr->location, "root");  
                            ptr->dlink = NULL;
                            ptr->flink = NULL;
                            
                            // Adding node into root directory
                            if(top == NULL) top = ptr;
                            else {
                                for(nodeptr = top; nodeptr->flink != NULL; nodeptr = nodeptr->flink);
                                nodeptr->flink = ptr;    
                             }   
                            }
                            
                            break;
                    case 2: if(top == NULL) 
                            {printf("Underflow😯️");
                            break;
                            }
                            printf("Enter name of file: ");
                            scanf("%s", search);
                            x=top;p=NULL;
                            while(x!=NULL){
                                if(strcmp(x->name, search)==0) {
                                if(p==NULL)
                                 top=x->flink;
                                 else
                                  p->flink=x->flink;
                                    printf("\nFile Deleted");
                                   free(x);
                                    break;
                                }
                                p=x;
                                x=x->flink;                    
                            }
                            if(x== NULL) printf("\nFile does not exist");
                            break;
                    case 3: printf("Enter the name of the file to be searched: ");
                            scanf("%s", search);
                            
                            for(nodeptr = top; nodeptr != NULL; nodeptr = nodeptr->flink) {
                                if(strcmp(nodeptr->name, search) == 0) {
                                    printf("\nFile Exists");
                                    break;
                                }                    
                            }
                            if(nodeptr == NULL) printf("\nFile does not exist");
                    
                            break;
                    case 4: printf("\n\nFile Structure\nroot -> ");
                            for(nodeptr = top; nodeptr != NULL; nodeptr = nodeptr->flink) printf("%s -> ", nodeptr->name);
                            break;
                    case 5: exit(0);
                    default: printf("\n\nInvalid Input");
                }
            }
       }
       }
