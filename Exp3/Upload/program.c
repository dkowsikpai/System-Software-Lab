/**
 * Implementation of different file directory structure
 * Author: Kowsik Nandagopan D
*/

// Header File
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Details structure
// Common for all three dir structure
struct Details{
    char crt[25]; // Created date
    char perm[20]; // Permission string
    char size[20]; // Size string
};

// Single Level ---------------------------------------------------------------------------------------
// File/Dir structure
struct SingleL {
    char name[20]; // name
    int isDir; // whether directory or file
    struct SingleL *sibling; // has common parent/ has sibling
    struct SingleL *parent; // parent information (location)
    struct Details *details; // details structure
};

// Traverse and print all the parent child relation
int traverseSL(struct SingleL *h){
    // Init
    struct SingleL *s=h->sibling;
    int c=0;
    // Print parent
    printf("%s:", h->name);
    while (s != NULL){
        // Printing the info inside the parent dir
        printf("%s->", s->name);
        // Counting the files
        c++;
        s = s->sibling;
    }
    printf("\n\n");
    return c;
}

// Creating the file inside parent
struct SingleL* createSL(char *name, int isDir, struct SingleL* parent){
    struct SingleL *node = (struct SingleL*)malloc(sizeof(struct SingleL)), *temp=parent;
    // Checking file exists
    while (temp!=NULL){
        // Condition
        if (strcmp(temp->name, name)==0){
            // Exist
            printf("%s cannot be created as %s already exists\n", name, name);
            return NULL;
        }
        temp = temp->sibling;
    }
    // Creating if not exists
    strcpy(node->name, name);
    node->isDir = isDir; // dir or not
    node->sibling = NULL; // no sibling on init
    node->parent = parent; // parent info
    // temp = parent;
    // while (temp!=NULL){
    //     // Condition
    //     temp = temp->sibling;
    // }
    // temp = node;
    // printf("%s v\n", parent->sibling->name);
    return node;
}

// Details input function common for all 3
struct Details* detailsF(char *crt, char*size, char *perm){
    struct Details *det = (struct Details*)malloc(sizeof(struct Details));
    strcpy(det->crt, crt); // Created date
    strcpy(det->size, size); // Size
    strcpy(det->perm, perm); // Permission
    return det; // return
}

// Insert new item
void insertSL(struct SingleL **node, struct SingleL **parent){
    struct SingleL *temp = *parent;
    // printf("%s", parent->name);
    while (temp != NULL) {
        printf("%s->", temp->name);
        temp = temp->sibling;
    }
    temp = *node;
    printf("%s", (*parent)->sibling->name);
    // return parent;
}

// Count File nodes
int countFileSL(struct SingleL *parent){
    struct SingleL *temp=parent->sibling;
    int count = 0;
    while(temp != NULL){
        temp = temp->sibling;
        count++;
    }
    return count;
}

// Delete the node
void deleteSL(char *name, struct SingleL *parent){
    struct SingleL *temp = parent, *t;
    // If just adjacent to parent
    if (strcmp(parent->sibling->name, name) == 0){
        printf("Location: %s\n", parent->name);
        printf("No of files: 1\n");
        printf("Count: %d\n", countFileSL(parent)-1);
        printf("Created On: %s\n", temp->details->crt);
        printf("Size: %s\n", temp->details->size);
        printf("Permission: %s\n\n", temp->details->perm);
        temp = parent->sibling;
        parent->sibling = parent->sibling->sibling;
        
        free(temp);
        printf("File Deleted Successfully\n");
        return;
    } else {
        // if inside the linked list
        while(temp->sibling != NULL){
            if (strcmp(temp->sibling->name, name) == 0){
                printf("Location: %s\n", parent->name);
                printf("No of files: 1\n");
                printf("Count: %d\n", countFileSL(parent)-1);
                printf("Created On: %s\n", temp->details->crt);
                printf("Size: %s\n", temp->details->size);
                printf("Permission: %s\n\n", temp->details->perm);
                t = temp->sibling;
                temp->sibling = temp->sibling->sibling;
                free(t);
                printf("File Deleted Successfully\n");
                return;
            }
            temp = temp->sibling;
        }
    }
    // Print if not found
    printf("%s not found in %s\n", name, parent->name);
}

// Search
void searchSL(char *name, struct SingleL *parent){
    struct SingleL *temp=parent->sibling;
    while (temp){
        if (strcmp(temp->name, name)==0){
            printf("File %s found\n", temp->name);
            printf("Location: %s\n", parent->name);
            printf("Created On: %s\n", temp->details->crt);
            printf("Size: %s\n", temp->details->size);
            printf("Permission: %s\n\n", temp->details->perm);
            return;
        }
        temp = temp->sibling;
    }
    printf("%s NOT found in %s directory\n", name, parent->name);
}

// Two Level -----------------------------------------------------------------------------------
// Dir structure
struct TwoLRoot {
    char name[20]; // name
    int isDir; // is dir or not
    struct TwoLRoot *sibling; // has sibling
    struct TwoL *child; // contents of file
    struct TwoLRoot *parent; // Parent info (location)
    struct Details *details; // Details
};

// File structure
struct TwoL {
    char name[20]; //name
    int isDir; // is dir
    struct TwoL *sibling; // has no child
    struct TwoLRoot *parent; // Location
    struct Details *details; // details
};

// Create file in two level given parent
struct TwoL* createTwoL(char *name, int isDir, struct TwoLRoot* parent){
    struct TwoL *node = (struct TwoL*)malloc(sizeof(struct TwoL));
    strcpy(node->name, name); 
    node->isDir = isDir;
    node->sibling = NULL;
    node->parent = parent;
}

// Create directory in the root directory
struct TwoLRoot* createTwoLDir(char *name, int isDir, struct TwoLRoot* parent){
    struct TwoLRoot *node = (struct TwoLRoot*)malloc(sizeof(struct TwoLRoot));
    strcpy(node->name, name);
    node->child = NULL;
    node->isDir = isDir;
    node->sibling = NULL;
    node->parent = parent;
}

// Get Parent
struct TwoLRoot* getParent(char *name, struct TwoLRoot* root){
    struct TwoLRoot* temp=root;
    while(temp != NULL){
        if (strcmp(temp->name, name) == 0){
            return temp;
        }
        temp = temp->sibling;
    }
    return NULL;
}

// search for the file
void searchTwoL(struct TwoLRoot *h, char *name){
    struct TwoLRoot *tempRoot=h;
    struct TwoL *temp=NULL;
    int c = 0;
    printf("Search\n");
    // Searching in each child of root dir
    while (tempRoot != NULL){
        temp = tempRoot->child;
        // Searching in each dir
        while(temp != NULL){
            // Condition
            if (strcmp(temp->name, name)==0){
                printf("%d. %s\n", c+1, name);
                printf("Location: %s\n", temp->parent->name);
                printf("Date created: %s\n", temp->details->crt);
                printf("Permission: %s\n\n", temp->details->perm);
                // Counting
                c++;
            }
            temp = temp->sibling;
        }
        tempRoot = tempRoot->sibling;
    }
    printf("%d Results found\n", c);
}

// Traversing through all dir
int traverseTwoL(struct TwoLRoot *h){
    struct TwoLRoot *tempRoot=h;
    struct TwoL *temp=NULL;
    int c=0;
    // traversing throuch child
    while (tempRoot != NULL){
        // print parent
        printf("%s: ", tempRoot->name);
        c++;
        temp = tempRoot->child;
        // traversing through child contents
        while(temp != NULL){
            printf("%s->", temp->name);
            temp = temp->sibling;
            c++;
        }
        tempRoot = tempRoot->sibling;
        if (tempRoot!= NULL) printf("\n|\nv\n");
        else printf("\n");
    }
    return c;
}

// Counting files given parent
int countFileTwoL(struct TwoLRoot *h){
    struct TwoLRoot *tempRoot=h;
    struct TwoL *temp=NULL;
    int c=0;
    // traversing through each dir 
    while (tempRoot != NULL){
        temp = tempRoot->child;
        // traverse through files
        while(temp != NULL){
            temp = temp->sibling;
            c++;
        }
        tempRoot = tempRoot->sibling;
    }
    return c;
}

// Delete file/folder
void deleteTwoL(char *name, struct TwoLRoot *parent){
    struct TwoL *temp=parent->child, *t;
    // If file is adjacent to the parent
    if (strcmp(parent->child->name, name)==0){
        parent->child = parent->child->sibling;
        printf("%s deleted from the directory %s\n", name, parent->name);
        printf("Directory: %s\n", parent->name);
        printf("File Count: %d\n", countFileTwoL(parent));
        printf("Size: %s\n", temp->details->size);
        printf("Date created: %s\n", temp->details->crt);
        printf("Permission: %s\n", temp->details->perm);
        free(temp);
    } else {
        // if file isinside linked list
        while(temp->sibling != NULL){
            if (strcmp(temp->sibling->name, name)==0){
                printf("%s deleted from the directory %s\n", name, parent->name);
                printf("Directory: %s\n", parent->name);
                printf("File Count: %d\n", countFileTwoL(parent));
                printf("Size: %s\n", temp->sibling->details->size);
                printf("Date created: %s\n", temp->sibling->details->crt);
                printf("Permission: %s\n", temp->sibling->details->perm);
                t = temp->sibling;
                if (temp->sibling->sibling != NULL)temp->sibling = temp->sibling->sibling;
                else temp->sibling = NULL;
                free(t);
                break;
            }
            temp = temp->sibling;
        }
    }
    printf("\n");
}

// Insert to a location given parent
void insertFile(struct TwoL *node, struct TwoLRoot *parent){
    struct TwoL *temp=parent->child;
    while (temp!=NULL){
        temp=temp->sibling;
    }
    temp=node;
}

// print createion details
void printCrtTwoL(struct TwoL *node){
    printf("%s is created in %s directory.\n", node->name, node->parent->name);
    printf("Date created: %s\n", node->details->crt);
    printf("Permission: %s\n", node->details->perm);
    printf("Location: %s\n\n", node->parent->name);
}


//Hierarchy----------------------------------------------------------------------------------------------------
// Dir/File  structure
struct Hir {
    char name[20]; //name
    int isDir; // dir or not
    struct Hir *sibling; // siblings
    struct Hir *child; // children
    struct Hir *parent; // location
    struct Details *details; // details
};

// Traverse through all the n-tree
int traverseH(struct Hir *h, int c){
    struct Hir *ch=h->child, *s=h->sibling;
    c++;
    // print in format: name (parent)
    printf("%s (%s)\n", h->name, h->parent->name);
    if (s != NULL){
        // traverse through siblings
        c += traverseH(s, 0);
    }
    // traverse through children
    if (ch != NULL){
        c += traverseH(ch, 0);
    }
    return c;
}

// Count contents
int countH(struct Hir *h, int c){
    struct Hir *ch=h->child, *s=h->sibling;
    if(h->isDir == 0)c++;
    if (s != NULL){
        c += countH(s, 0);
    }
    if (ch != NULL){
        c += countH(ch, 0);
    }
    return c;
}

// search in tree and return pointer if found
struct Hir* search(struct Hir *h, char *name){
    struct Hir *ch=h->child, *s=h->sibling, *found=NULL;
    if (strcmp(h->name, name) == 0){
        // printf("Found %s\n ", h->name);
        return h;
    } else {
        if (s != NULL){
            found=search(s, name);
            if (found != NULL) return found;
        }
        if (ch != NULL){
            found=search(ch, name);
            if (found != NULL) return found;

        }
    }  
    return NULL; 
}

// Search for a file in n-tree
void searchFile(struct Hir *h, char *name){
    struct Hir *ch=h->child, *s=h->sibling;
    if(strcmp(h->name, name)==0 && h->isDir == 0){
        printf("File %s Found\n", h->name);
        printf("Location: %s\n", h->parent->name);
        printf("Date created: %s\n", h->details->crt);
        printf("Permission: %s\n\n", h->details->perm);
    }
    if (s != NULL){
        searchFile(s, name);
    }
    if (ch != NULL){
        searchFile(ch, name);
    }
}

// insert the filein the hierarchy, given parent
void insertH(struct Hir *par, struct Hir *createdNode){
    struct Hir *temp = par;
    if (par == NULL){
        printf("Cannot Insert at this postion.\n");
        return;
    }
    if (par->isDir){
        while (temp->sibling != NULL){
            temp = temp->sibling;
        }
        // printf("%s inser\n", temp->name);
        temp->sibling = createdNode;  
    } else {
        printf("Cannot Insert since Parent(%s) is not a folder.\n", par->name);
    }
}

// create node
struct Hir* create(char *name, int isDir, struct Hir* parent){
    struct Hir *node = (struct Hir*)malloc(sizeof(struct Hir));
    strcpy(node->name, name);
    node->child = NULL;
    node->isDir = isDir;
    node->sibling = NULL;
    node->parent = parent;
}

// delete item from the tree
void delete(struct Hir* h){
    if (h->parent == NULL){
        printf("No parent. So cannot delete");
    } else {
        // Parent have only one child and sibling
        // We can check only this only on child since, all the siblings have common parent. But parent have only one child. Other childeren are represented as siblings of that child
        if (h->parent->child == h) {
            h->parent->child = h->sibling;
            free(h);
            printf("File Deleted Successfully\n");
        } else {
            struct Hir* temp = h->parent;
            // Traversing through sibling linked list. And deleting one node from that linked list
            while (temp->sibling != h){
                temp = temp->sibling;
            }
            temp->sibling = h->sibling;
            printf("File Deleted Successfully\n");
            free(h);
        }
    }
}

// creation details print
void printCrt(struct Hir *node){
    printf("%s is created in %s directory.\n", node->name, node->parent->name);
    printf("Date created: %s\n", node->details->crt);
    printf("Permission: %s\n", node->details->perm);
    printf("Location: %s\n\n", node->parent->name);
}

// Deletion details
void printDel(struct Hir *node, struct Hir *root){
    printf("%s was deleted in %s directory.\n", node->name, node->parent->name);
    printf("Directory: %s\n", node->parent->name);
    printf("Count: %d\n", countH(root, 0)-1);
    printf("Location: Root\n");
    printf("Size: %s\n", node->details->size);
    printf("Permission: %s\n\n", node->details->perm);
}


// Test Case -----------------------------------------------------------------------------------------------------------------------------
// Single Level
void single(){
    // Creating the root dir
    struct SingleL *rootSL = createSL("Root Directory", 1, NULL), *tempSL, *nodeSL;
    rootSL->details = detailsF("5/6/18", "21kb", "R/W/X");
    char name[20], date[20], size[20], perm[20];

    int menu=4, flag=1;
    while(flag){
        printf("----------Single Level menu----------\n1. Create\n2. Delete\n3. Traverse\n4. Search\n5. Exit\nSelect Menu: ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                printf("Name: ");
                scanf("%s", name);
                printf("Created Date: ");
                scanf("%s", date);
                printf("Size: ");
                scanf("%s", size);
                printf("Permission: ");
                scanf("%s", perm);
                tempSL = createSL(name, 0, rootSL);
                if (tempSL != NULL)tempSL->details = detailsF(date, size, perm);
                if (tempSL != NULL){
                    nodeSL = rootSL->sibling;
                    rootSL->sibling = tempSL;
                    tempSL->sibling = nodeSL;
                    printf("File Created Successfully\n");
                }
                break;
            case 2:
                printf("Name: ");
                scanf("%s", name);
                deleteSL(name, rootSL);
                break;
            case 3:
                printf("--------------File Content--------------\n");
                traverseSL(rootSL);
                printf("\n");
                break;
            case 4:
                printf("Name: ");
                scanf("%s", name);
                searchSL(name, rootSL);
                break;
            case 5:
                flag = 0;
                break;
            default:
                printf("Invalid Meu\n");
                break;
        }
    }


    // create file inside root->ABC
    // tempSL = createSL("ABC", 0, rootSL);
    // if (tempSL != NULL)tempSL->details = detailsF("06/06/18", "0", "R/W");
    // if (tempSL != NULL){
    //     nodeSL = rootSL->sibling;
    //     rootSL->sibling = tempSL;
    //     tempSL->sibling = nodeSL;
    // }

    // tempSL = createSL("DEF", 0, rootSL);
    // if (tempSL != NULL)tempSL->details = detailsF("06/06/18", "0", "R/W");
    // if (tempSL != NULL){
    //     nodeSL = rootSL->sibling;
    //     rootSL->sibling = tempSL;
    //     tempSL->sibling = nodeSL;
    // }

    // // create file inside root->TEST
    // temp = createSL("TEST", 0, root);
    // if (temp != NULL)temp->details = detailsF("06/06/18", "0", "R/W");
    // if (temp != NULL)root->sibling->sibling = temp;

    // //trying to delete NOTES
    // deleteSL("DEF", rootSL);

    // // Trying to create TEST file again in root->TEST
    // temp = createSL("TEST", 0, root);
    // if (temp != NULL)temp->details = detailsF("06/06/18", "0", "R/W");
    // if (temp != NULL)root->sibling->sibling = temp;


    // printf("--------------File Content--------------\n");
    // traverseSL(rootSL);
    // printf("\n");
}

// Two Level
void two(){
    // Main dir
    struct TwoLRoot *rootTw = (struct TwoLRoot*)malloc(sizeof(struct TwoLRoot)), *tempDir, *nodeTwoRoot, *parPointer;
    struct TwoL *temp, *nodeTwoL;
    strcpy(rootTw->name, "Main");
    rootTw->isDir=1;
    rootTw->parent=NULL;
    rootTw->sibling=NULL;
    rootTw->child=NULL;

    char name[20], date[20], size[20], perm[20], parent[20];
    int menu=6, flag=1;
    while(flag){
        printf("-------------------Two Level Menu--------------\n1. Create Folder\n2. Create File\n3. Delete File\n4. Search File\n5. Traverse\n6. Exit\nSelect Menu: ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                printf("Name: ");
                scanf("%s", name);
                printf("Created Date: ");
                scanf("%s", date);
                // printf("Size: ");
                // scanf("%s", size);
                printf("Permission: ");
                scanf("%s", perm);
                tempDir = createTwoLDir(name, 1, rootTw);
                tempDir->details = detailsF(date, "0", perm);
                if (tempDir != NULL){
                    nodeTwoRoot = rootTw->sibling;
                    rootTw->sibling = tempDir;
                    tempDir->sibling = nodeTwoRoot;
                    printf("Directory Created Successfully\n");
                } else {
                    printf("Directory Creation Failed !!!\n");
                }
                break;
            case 2:
                printf("Parent Folder: ");
                scanf("%s", parent);
                printf("Name: ");
                scanf("%s", name);
                printf("Created Date: ");
                scanf("%s", date);
                printf("Size: ");
                scanf("%s", size);
                printf("Permission: ");
                scanf("%s", perm);
                parPointer = getParent(parent, rootTw);
                if (parPointer != NULL){
                    temp = createTwoL(name, 0, parPointer);
                    temp->details = detailsF(date, "0", perm);
                    if (temp != NULL){
                        nodeTwoL = parPointer->child;
                        temp->sibling = nodeTwoL;
                        parPointer->child = temp;
                        printf("File Created Successfully\n");
                    }
                } else {
                    printf("No parent folder exists !!!\n");
                }
                break;
            case 3:
                printf("Parent Folder: ");
                scanf("%s", parent);
                printf("Name: ");
                scanf("%s", name);
                parPointer = getParent(parent, rootTw);
                if (parPointer != NULL){
                    deleteTwoL(name, parPointer);
                } else {
                    printf("No parent folder exists !!!\n");
                }
                break;
            case 4:
                printf("Name: ");
                scanf("%s", name);
                searchTwoL(rootTw, name);
                break;
            case 5:
                printf("--------------File Content--------------\n");
                traverseTwoL(rootTw);
                printf("\n");
                break;
            case 6:
                flag=0;
                break;
            default:
                printf("Invalid Menu\n");
                break;
        }
    }

    // // Display file content
    // printf("--------------File Content--------------\n");
    // traverseTwoL(rootTw);
    // printf("\n");

    // // create file in root->Hello.txt
    // temp = createTwoL("Hello.txt", 0, rootTw);
    // temp->details = detailsF("10/7/18", "10Kb", "R/W/X");
    // rootTw->child = temp;

    // // create file root->Haha.img
    // temp = createTwoL("Haha.img", 0, rootTw);
    // temp->details = detailsF("11/7/18", "10Kb", "R/W/X");
    // rootTw->child->sibling = temp;

    // // create dir in root: Secondary
    // tempDir = createTwoLDir("Secondary", 1, rootTw);
    // rootTw->sibling = tempDir;

    // // Delete Hello.txt from root
    // deleteTwoL("Hello.txt", rootTw);

    // // Create file in secondary->hello.txt
    // temp = createTwoL("Hello.txt", 0, rootTw);
    // temp->details = detailsF("11/7/18", "10Kb", "R/W/X");
    // rootTw->sibling->child = temp;
    // printCrtTwoL(temp);

    // // Create file in secondary->hahaa.img
    // temp = createTwoL("Haha.img", 0, rootTw->sibling);
    // temp->details = detailsF("11/7/18", "10Kb", "R");
    // rootTw->sibling->child->sibling = temp;
    // printCrtTwoL(temp);

    // // Searching for hah.img in whole dir
    // searchTwoL(rootTw, "Haha.img");

    // Displaying the file contents
    // printf("--------------File Content--------------\n");
    // traverseTwoL(rootTw);
    // printf("\n");
}

// Hierarchy 
void hier(){
    // Creating Main Directory
    struct Hir *root = create("Main", 1, NULL), *temp, *s, *parPointer, *node;
    char name[20], date[20], size[20], perm[20], parent[20];
    int menu=6, flag=1;
    while(flag){
        printf("-------------------Hierarchy Level Menu--------------\n1. Create Folder\n2. Create File\n3. Delete File\n4. Search File\n5. Traverse\n6. Exit\nSelect Menu: ");
        scanf("%d", &menu);
        switch(menu){
            case 1:
                printf("Parent Folder: ");
                scanf("%s", parent);
                printf("Name: ");
                scanf("%s", name);
                printf("Created Date: ");
                scanf("%s", date);
                // printf("Size: ");
                // scanf("%s", size);
                printf("Permission: ");
                scanf("%s", perm);
                parPointer = search(root, parent);
                if (parPointer != NULL && parPointer->isDir == 1){
                    // printf("%s", parPointer->name);
                    temp = create(name, 1, parPointer);
                    temp->details = detailsF(date, "0", perm);
                    if (temp != NULL){
                        node = parPointer->child;
                        temp->child = node;
                        parPointer->child = temp;
                        printf("Directory Created Successfully\n");
                    }
                } else {
                    printf("Parent with name %s does not exists !!!\n", parent);
                }
                break;
            case 2:
                printf("Parent Folder: ");
                scanf("%s", parent);
                printf("Name: ");
                scanf("%s", name);
                printf("Created Date: ");
                scanf("%s", date);
                printf("Size: ");
                scanf("%s", size);
                printf("Permission: ");
                scanf("%s", perm);
                parPointer = search(root, parent);
                if (parPointer != NULL && parPointer->isDir == 1){
                    // printf("%s", parPointer->name);
                    temp = create(name, 0, parPointer);
                    temp->details = detailsF(date, size, perm);
                    if (temp != NULL){
                        node = parPointer->sibling;
                        temp->sibling = node;
                        parPointer->sibling = temp;
                        printf("File Created Successfully\n");
                    }
                } else {
                    printf("Parent with name %s does not exists !!!\n", parent);
                }
                break;
            case 3:
                printf("Parent Folder: ");
                scanf("%s", parent);
                printf("Name: ");
                scanf("%s", name);
                parPointer = search(search(root, parent), name);
                if (parPointer != NULL){
                    delete(parPointer);
                } else {
                    printf("Parent with name %s does not exists !!!\n", parent);
                }
                break;
            case 4:
                printf("Name: ");
                scanf("%s", name);
                searchFile(root, name);
                break;
            case 5:
                printf("--------------File Content--------------\n");
                traverseH(root, 0);
                printf("\n");
                break;
            case 6:
                flag=0;
                break;
            default:
                printf("Invalid Menu\n");
                break;
        }
    }

    // /* Test Cases*/
    // // Creating Directory Inside Main directory
    // temp = create("ABC", 1, root);
    // temp->details = detailsF("Aug2020", "0", "R/W/E");
    // root->child = temp;
    
    // // Creating File inside ABC. ie, inside root->ABC->CDE
    // temp = create("CDE", 0, root->child);
    // temp->details = detailsF("02/09/19", "0", "R");
    // root->child->child = temp;

    // // Creating File inside ABC. ie, inside root->ABC->Hello.txt
    // temp = create("Hello.txt", 0, root->child);
    // temp->details = detailsF("05/06/18", "22kb", "R/W/E");
    // root->child->sibling = temp;

    // // Creating Sibling Directory Secondary in Main Directory.
    // temp = create("Secondary", 1, NULL);
    // temp->details = detailsF("05/06/18", "0", "R/W/E");
    // root->sibling = temp;

    // // Creating file inside Secondary->ABC
    // temp = create("ABC.txt", 0, temp);
    // temp->details = detailsF("05/06/18", "15kb", "R/W/E");
    // root->sibling->child = temp;

    // // Traversing whole Directory
    // printf("------------------Directory Structure-------------\n");
    // traverseH(root, 0);
    // printf("\n");

    // // Printing the create operation
    // printCrt(root->child->child);

    // // Deleting File Hello.txt from root->ABC->Hello.txt
    // printDel(root->child->sibling, root);
    // delete(search(root->child, "Hello.txt"));

    // // Searching for file ABC from Root directory
    // searchFile(root, "ABC.txt");
    // // printf("%d\n", traverseH(root, 0));  
}

void main (){
    int menu=4, flag=1;

    // Menu Driver
    while(flag){
        printf("---------------Menu---------------\n1. Single Level\n2. Two Level\n3. Hierarchy\n4. Exit\nSelect menu: ");
        scanf("%d", &menu);
        // Menu
        switch(menu){
            case 1:
                // Single level Test case caller
                printf("-----------------------Single level-----------------------\n");
                single();
                break;
            case 2:
                // Two level Test case caller
                printf("-----------------------Two level-----------------------\n");
                two();
                break;
            case 3:
                // Hierarchy level Test case caller
                printf("-----------------------Hierarchy level-----------------------\n");
                hier();
                break;
            case 4:
                // Exit
                flag=0;
                break;
            default:
                // Invalid menu
                printf("Invalid Menu \n");
                break;
        }
    }
    printf("\n");
}