    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    // Structure of Files and Directories
    struct node {
        char name[100];
        int file_count;
        struct node *dlink, *flink;
        char location[100];
        int type;
        int size;
        char created_on[100];
        char permissions[100];
    }*ptr, *ftop, *nodeptr, *dtop, *dirptr;
     
    void main() {
        int type, flag;
        char search[100], dname[100];
        ftop = NULL;
        dtop = NULL;
     
        printf("\n\nFILE ORGANIZATION TECHNIQUES");
        printf("\n1. SINGLE LEVEL");
        printf("\n2. TWO LEVEL");
        printf("\n3. EXIT");
        printf("\nEnter choice: ");
        scanf("%d", &type);
     
        if(type == 3) exit(0);
        else if(type > 3 || type < 1) {
            printf("\nInvalid Input!");
            exit(0);
        }
     
        // Creating Root Directory
        if(type == 1) printf("\n\nCreating ROOT Directory.");
        if(type == 2) printf("\n\nCreating MAIN Directory.");
        ptr = (struct node*)malloc(sizeof(struct node));
        if(type == 1) strcpy(ptr->name, "ROOT");
        if(type == 2) strcpy(ptr->name, "MAIN");
        ptr->file_count = 1;
        strcpy(ptr->location, "/");
        ptr->type = 0;
        ptr->size = 1;
        printf("\nEnter date of creation: ");
        scanf("%s", ptr->created_on);
        printf("Enter Permissions: ");
        scanf("%s", ptr->permissions);
        ptr->dlink = ptr->flink = NULL;
        ftop = dtop = ptr;
     
        while(1) {
            if(type == 1) printf("\n\n----------SINGLE LEVEL----------");
            if(type == 2) printf("\n\n----------TWO LEVEL----------");
            printf("\n1. Create Node");
            printf("\n2. Delete Node");
            printf("\n3. Search Node");
            printf("\n4. Display");
            printf("\n5. Directory Information");
            printf("\n6. Exit");
     
            int choice;
            printf("\nEnter choice: ");
            scanf("%d", &choice);
     
            switch(choice) {
                case 1: dirptr = dtop;
                        if(type == 2) {
                            printf("\n\n1. Create Directory\n2. Create File\nEnter choice: ");
                            scanf("%d", &choice);
                        }
                        if(type == 2 && choice == 2) {
                            printf("\nEnter name of directory: ");
                            scanf("%s", dname);
     
                            // Search for directory
                            flag = 0;
                            for(dirptr = dtop; dirptr != NULL; dirptr = dirptr->dlink) {
                                if(strcmp(dirptr->name, dname) == 0) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if(flag == 0) {
                                printf("\n\nDirectory %s does not exist", dname);
                                break;
                            }
                        }
     
                        // Creating new node
                        ptr = (struct node*)malloc(sizeof(struct node));
                        if(type == 2 && choice == 2) {
                            printf("\nEnter name of file: ");
                            scanf("%s", ptr->name);
                            ptr->type = 1;
                        }
                        else if(type == 2 && choice == 1) {
                            printf("\nEnter name of directory: ");
                            scanf("%s", ptr->name);
                            ptr->type = 0;
                        }
     
                        if(type == 1) {
                            printf("\nEnter name of file: ");
                            scanf("%s", ptr->name);
                            printf("Enter type (0: directory, 1: file): ");
                            scanf("%d", &ptr->type);
                        }
     
                        if(type == 1 && ptr->type != 1) {
                            printf("\n\nDirectories not allowed!");
                            break;
                        }
     
                        if(ptr->type == 0) ptr->size = 1;
                        else{
                            printf("Enter size: ");
                            scanf("%d", &ptr->size);
                        }
                        dirptr->size += ptr->size;
                        dirptr->file_count += 1;
                        printf("Enter date: ");
                        scanf("%s", ptr->created_on  );
                        printf("Enter permissions: ");
                        scanf("%s", ptr->permissions);
     
                        ptr->file_count = 1;
                        strcpy(ptr->location, "root");
                        ptr->dlink = NULL;
                        ptr->flink = NULL;
     
                        // Adding new directory
                        if(type == 2 && choice == 1) {
                            if(dirptr == NULL) break;
                            else {
                                flag = 0;
                                for(nodeptr = dirptr; nodeptr->dlink != NULL; nodeptr = nodeptr->dlink) if(strcmp(nodeptr->name, ptr->name) == 0) flag = 1;
                                if(flag == 1) {
                                    printf("\n\n%s cannot be created as %s already exists.", ptr->name, ptr->name);
                                    break;
                                }
                                nodeptr->dlink = ptr;
                            }
                        }
     
                        // Adding node into the directory
                        else {
                            if(dirptr == NULL) dirptr = ptr;
                            else {
                                flag = 0;
                                for(nodeptr = dirptr; nodeptr->flink != NULL; nodeptr = nodeptr->flink) if(strcmp(nodeptr->name, ptr->name) == 0) flag = 1;
                                if(flag == 1) {
                                    printf("\n\n%s cannot be created as %s already exists.",ptr->name, ptr->name);
                                    break;
                                }
                                nodeptr->flink = ptr;
                            }
                        }
     
                        break;
                case 2: // Deleting a node
                        dirptr = dtop;
                        if(type == 2) {
                            printf("\nEnter directory name: ");
                            scanf("%s", dname);
     
                            // Search for directory
                            flag = 0;
                            for(dirptr = dtop; dirptr->dlink != NULL; dirptr = dirptr->dlink) {
                                if(strcmp(dirptr->name, dname) == 0) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if(flag == 0) {
                                printf("\n\nDirectory %s does not exist", dname);
                                break;
                            }
                        }
     
                        flag = 0;
                        if(dirptr == NULL) break;
     
                        printf("\nEnter name of file: ");
                        scanf("%s", search);
     
                        for(nodeptr = dirptr; nodeptr->flink != NULL; nodeptr = nodeptr->flink) {
                            if(strcmp(nodeptr->flink->name, search) == 0) {
                                printf("\nFile %s Deleted", (nodeptr->flink)->name);
                                printf("\nDirectory: %s Directory", dirptr->name);
                                printf("\nNumber of files: %d", nodeptr->flink->file_count);
                                printf("\nLocation: /root/");
                                printf("\nSize: %d", nodeptr->flink->size);
                                printf("\nCreated on: %s", nodeptr->flink->created_on);
                                printf("\nPermisions: %s", nodeptr->flink->permissions);
                                flag = 1;
                                nodeptr->flink = (nodeptr->flink)->flink;
                                dirptr->size -= nodeptr->flink->size;
                                dirptr->file_count -= 1;
                                break;
                            }
     
                            if(flag == 0) printf("\nFile %s not found in %s directory", search, dirptr->name);
                        }
                        break;
                case 3: // Search for a node
                        dirptr = dtop;
                        if(type == 2) {
                            printf("\nEnter directory name: ");
                            scanf("%s", dname);
     
                            // Search for directory
                            flag = 0;
                            for(dirptr = dtop; dirptr != NULL; dirptr = dirptr->dlink) {
                                if(strcmp(dirptr->name, dname) == 0) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if(flag == 0) {
                                printf("\n\nDirectory %s does not exist", dname);
                                break;
                            }
                        }
     
                        printf("\nEnter the name of the file: ");
                        scanf("%s", search);
     
                        for(nodeptr = dirptr; nodeptr != NULL; nodeptr = nodeptr->flink) {
                            if(strcmp(nodeptr->name, search) == 0) {
                                printf("\n\nFile %s found", search);
                                printf("\nName: %s", nodeptr->name);
                                if(nodeptr->type == 0) printf("\nType: Directory");
                                else printf("\nType: File");
                                printf("\nLocation: /root/");
                                printf("\nSize: %d", nodeptr->size);
                                printf("\nCreated On: %s", nodeptr->created_on);
                                printf("\nPermission: %s", nodeptr->permissions);
                                printf("\nFile Count: %d", nodeptr->file_count);
     
                                break;
                            }
                        }
                        if(nodeptr == NULL) printf("\nFile %s does not exist in %s", search, dirptr->name);
     
                        break;
                case 4: // Display
                        printf("\n\nFILE STRUCTURE");
                        for(dirptr = dtop; dirptr != NULL; dirptr = dirptr->dlink) {
                            printf("\n");
                            for(nodeptr = dirptr; nodeptr != NULL;nodeptr = nodeptr->flink) printf("%s -> ", nodeptr->name);
                        }
                        break;
                case 5:
                        for(nodeptr = dtop; nodeptr != NULL; nodeptr = nodeptr->dlink) {
                            printf("\n\nName: %s", nodeptr->name);
                            printf("\nSize: %d", nodeptr->size);
                            printf("\nCreation Date: %s", nodeptr->created_on);
                            printf("\nFile Count: %d", nodeptr->file_count);
                            printf("\nPermissions: %s", nodeptr->permissions);
                        }
                        break;
                case 6: exit(0);
                default: printf("\n\nInvalid Input");
            }
        }
    }
