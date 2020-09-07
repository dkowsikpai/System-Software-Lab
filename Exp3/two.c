#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Details{
    char crt[25];
    char perm[20];
    char size[20];
};

struct TwoLRoot {
    char name[20];
    int isDir;
    struct TwoLRoot *sibling;
    struct TwoL *child;
    struct TwoLRoot *parent;
    struct Details *details;
};

struct TwoL {
    char name[20];
    int isDir;
    struct TwoL *sibling;
    struct TwoLRoot *parent;
    struct Details *details;
};

struct TwoL* createTwoL(char *name, int isDir, struct TwoLRoot* parent){
    struct TwoL *node = (struct TwoL*)malloc(sizeof(struct TwoL));
    strcpy(node->name, name);
    node->isDir = isDir;
    node->sibling = NULL;
    node->parent = parent;
}

struct TwoLRoot* createTwoLDir(char *name, int isDir, struct TwoLRoot* parent){
    struct TwoLRoot *node = (struct TwoLRoot*)malloc(sizeof(struct TwoLRoot));
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

void searchTwoL(struct TwoLRoot *h, char *name){
    struct TwoLRoot *tempRoot=h;
    struct TwoL *temp=NULL;
    int c = 0;
    printf("Search\n");
    while (tempRoot != NULL){
        temp = tempRoot->child;
        while(temp != NULL){
            if (strcmp(temp->name, name)==0){
                printf("%d. %s\n", c+1, name);
                printf("Location: %s\n", temp->parent->name);
                printf("Date created: %s\n", temp->details->crt);
                printf("Permission: %s\n\n", temp->details->perm);
                c++;
            }
            temp = temp->sibling;
        }
        tempRoot = tempRoot->sibling;
    }
}

int traverseTwoL(struct TwoLRoot *h){
    struct TwoLRoot *tempRoot=h;
    struct TwoL *temp=NULL;
    int c=0;
    while (tempRoot != NULL){
        printf("%s: ", tempRoot->name);
        c++;
        temp = tempRoot->child;
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

int countFileTwoL(struct TwoLRoot *h){
    struct TwoLRoot *tempRoot=h;
    struct TwoL *temp=NULL;
    int c=0;
    while (tempRoot != NULL){
        temp = tempRoot->child;
        while(temp != NULL){
            temp = temp->sibling;
            c++;
        }
        tempRoot = tempRoot->sibling;
    }
    return c;
}

void deleteTwoL(char *name, struct TwoLRoot *parent){
    struct TwoL *temp=parent->child, *t;
    // printf("hh");
    if (strcmp(parent->child->name, name)==0){
        parent->child = parent->child->sibling;
        printf("%s deleted from the directory %s\n", name, parent->name);
        printf("Directory: %s\n", parent->name);
        printf("File Count: %d\n", countFileTwoL(parent)-1);
        printf("Size: %s\n", temp->details->size);
        printf("Date created: %s\n", temp->details->crt);
        printf("Permission: %s\n", temp->details->perm);
        free(temp);
    } else {
        while(temp->sibling != NULL){
            if (strcmp(temp->sibling->name, name)==0){
                printf("%s deleted from the directory %s\n", name, parent->name);
                printf("Directory: %s\n", parent->name);
                printf("File Count: %d\n", countFileTwoL(parent)-1);
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

void insertFile(struct TwoL *node, struct TwoLRoot *parent){
    struct TwoL *temp=parent->child;
    while (temp!=NULL){
        temp=temp->sibling;
    }
    temp=node;
}

void printCrtTwoL(struct TwoL *node){
    printf("%s is created in %s directory.\n", node->name, node->parent->name);
    printf("Date created: %s\n", node->details->crt);
    printf("Permission: %s\n", node->details->perm);
    printf("Location: %s\n\n", node->parent->name);
}

void main(){
    struct TwoLRoot *rootTw = (struct TwoLRoot*)malloc(sizeof(struct TwoLRoot)), *tempDir;
    struct TwoL *temp;
    strcpy(rootTw->name, "Main Directory");
    rootTw->isDir=1;
    rootTw->parent=NULL;
    rootTw->sibling=NULL;
    rootTw->child=NULL;

    printf("--------------File Content--------------\n");
    traverseTwoL(rootTw);
    printf("\n");

    temp = createTwoL("Hello.txt", 0, rootTw);
    temp->details = detailsF("10/7/18", "10Kb", "R/W/X");
    rootTw->child = temp;

    temp = createTwoL("Haha.img", 0, rootTw);
    temp->details = detailsF("11/7/18", "10Kb", "R/W/X");
    rootTw->child->sibling = temp;

    tempDir = createTwoLDir("Secondary", 1, rootTw);
    rootTw->sibling = tempDir;

    deleteTwoL("Hello.txt", rootTw);

    temp = createTwoL("Hello.txt", 0, rootTw);
    temp->details = detailsF("11/7/18", "10Kb", "R/W/X");
    rootTw->sibling->child = temp;
    printCrtTwoL(temp);

    temp = createTwoL("Haha.img", 0, rootTw->sibling);
    temp->details = detailsF("11/7/18", "10Kb", "R");
    rootTw->sibling->child->sibling = temp;
    printCrtTwoL(temp);

    searchTwoL(rootTw, "Haha.img");

    printf("--------------File Content--------------\n");
    traverseTwoL(rootTw);
    printf("\n");
}