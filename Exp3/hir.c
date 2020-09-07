#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Details{
    char crt[25];
    char perm[20];
    char size[20];
};

struct Hir {
    char name[20];
    int isDir;
    struct Hir *sibling;
    struct Hir *child;
    struct Hir *parent;
    struct Details *details;
};

int traverseH(struct Hir *h, int c){
    struct Hir *ch=h->child, *s=h->sibling;
    c++;
    printf("%s (%s)\n", h->name, h->parent->name);
    if (s != NULL){
        c += traverseH(s, 0);
    }
    if (ch != NULL){
        c += traverseH(ch, 0);
    }
    return c;
}

int countH(struct Hir *h, int c){
    struct Hir *ch=h->child, *s=h->sibling;
    if(h->isDir == 0)c++;
    // printf("%s (%s)\n", h->name, h->parent->name);
    if (s != NULL){
        c += countH(s, 0);
    }
    if (ch != NULL){
        c += countH(ch, 0);
    }
    return c;
}

struct Hir* search(struct Hir *h, char *name){
    struct Hir *ch=h->child, *s=h->sibling, *found=NULL;
    // printf("%s (%s)\n", h->name, h->parent->name);
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

struct Hir* create(char *name, int isDir, struct Hir* parent){
    struct Hir *node = (struct Hir*)malloc(sizeof(struct Hir));
    strcpy(node->name, name);
    node->child = NULL;
    node->isDir = isDir;
    node->sibling = NULL;
    node->parent = parent;
}

struct Details* detailsF(char *crt, char*size, char *perm){
    struct Details *det = (struct Details*)malloc(sizeof(struct Details));
    strcpy(det->crt, crt);
    strcpy(det->size, size);
    strcpy(det->perm, perm);
    return det;
}

void delete(struct Hir* h){
    if (h->parent == NULL){
        printf("No parent. So cannot delete");
    } else {
        // Parent have only one child and sibling
        // We can check only this only on child since, all the siblings have common parent. But parent have only one child. Other childeren are represented as siblings of that child
        if (h->parent->child == h) {
            h->parent->child = h->sibling;
            free(h);
        } else {
            struct Hir* temp = h->parent;
            // Traversing through sibling linked list. And deleting one node from that linked list
            while (temp->sibling != h){
                temp = temp->sibling;
            }
            temp->sibling = h->sibling;
            free(h);
        }
    }
}

void printCrt(struct Hir *node){
    printf("%s is created in %s directory.\n", node->name, node->parent->name);
    printf("Date created: %s\n", node->details->crt);
    printf("Permission: %s\n", node->details->perm);
    printf("Location: %s\n\n", node->parent->name);
}

void printDel(struct Hir *node, struct Hir *root){
    printf("%s was deleted in %s directory.\n", node->name, node->parent->name);
    printf("Directory: %s\n", node->parent->name);
    printf("Count: %d\n", countH(root, 0)-1);
    printf("Location: Root\n");
    printf("Size: %s\n", node->details->size);
    printf("Permission: %s\n\n", node->details->perm);
}



void main(){
    int menu, flag=1;
    // Creating Main Directory
    struct Hir *root = create("Main Directory", 1, NULL), *temp, *s;
    char name[20], parent[20], date[20], size[20], perm[20];

    /* Test Cases*/
    // Creating Directory Inside Main directory
    temp = create("ABC", 1, root);
    temp->details = detailsF("Aug2020", "0", "R/W/E");
    root->child = temp;
    
    // Creating File inside ABC. ie, inside root->ABC->CDE
    temp = create("CDE", 0, root->child);
    temp->details = detailsF("02/09/19", "0", "R");
    root->child->child = temp;

    // Creating File inside ABC. ie, inside root->ABC->Hello.txt
    temp = create("Hello.txt", 0, root->child);
    temp->details = detailsF("05/06/18", "22kb", "R/W/E");
    root->child->sibling = temp;

    // Creating Sibling Directory Secondary in Main Directory.
    temp = create("Secondary", 1, NULL);
    temp->details = detailsF("05/06/18", "0", "R/W/E");
    root->sibling = temp;

    // Creating file inside Secondary->ABC
    temp = create("ABC.txt", 0, temp);
    temp->details = detailsF("05/06/18", "15kb", "R/W/E");
    root->sibling->child = temp;

    // Traversing whole Directory
    printf("------------------Directory Structure-------------\n");
    traverseH(root, 0);
    printf("\n");

    // Printing the create operation
    printCrt(root->child->child);

    // Deleting File Hello.txt from root->ABC->Hello.txt
    printDel(root->child->sibling, root);
    delete(search(root->child, "Hello.txt"));

    // Searching for file ABC from Root directory
    searchFile(root, "ABC");
    // printf("%d\n", traverseH(root, 0));   
    
}