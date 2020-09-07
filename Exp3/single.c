#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Details{
    char crt[25];
    char perm[20];
    char size[20];
};

struct SingleL {
    char name[20];
    int isDir;
    struct SingleL *sibling;
    struct SingleL *parent;
    struct Details *details;
};

int traverseSL(struct SingleL *h){
    struct SingleL *s=h->sibling;
    int c=0;
    printf("%s:", h->name);
    while (s != NULL){
        printf("%s->", s->name);
        c++;
        s = s->sibling;
    }
    printf("\n\n");
    return c;
}

struct SingleL* createSL(char *name, int isDir, struct SingleL* parent){
    struct SingleL *node = (struct SingleL*)malloc(sizeof(struct SingleL)), *temp=parent;
    while (temp!=NULL){
        if (strcmp(temp->name, name)==0){
            printf("%s cannot be created as %s already exists\n", name, name);
            return NULL;
        }
        temp = temp->sibling;
    }
    strcpy(node->name, name);
    node->isDir = isDir;
    node->sibling = NULL;
    node->parent = parent;
    return node;
}

struct Details* detailsF(char *crt, char*size, char *perm){
    struct Details *det = (struct Details*)malloc(sizeof(struct Details));
    strcpy(det->crt, crt);
    strcpy(det->size, size);
    strcpy(det->perm, perm);
    return det;
}

void deleteSL(char *name, struct SingleL *parent){
    struct SingleL *temp = parent, *t;
    if (strcmp(parent->sibling->name, name) == 0){
        parent->sibling = parent->sibling->sibling;
        free(temp);
        return;
    } else {
        while(temp->sibling != NULL){
            if (strcmp(temp->sibling->name, name) == 0){
                t = temp->sibling;
                temp->sibling = temp->sibling->sibling;
                free(t);
                return;
            }
            temp = temp->sibling;
        }
    }
    printf("%s not found in %s\n", name, parent->name);
}

void main(){
    struct SingleL *root = createSL("Root Directory", 1, NULL), *temp;
    root->details = detailsF("5/6/18", "21kb", "R/W/X");

    temp = createSL("ABC", 0, root);
    if (temp != NULL)temp->details = detailsF("06/06/18", "0", "R/W");
    if (temp != NULL)root->sibling = temp;

    temp = createSL("TEST", 0, root);
    if (temp != NULL)temp->details = detailsF("06/06/18", "0", "R/W");
    if (temp != NULL)root->sibling->sibling = temp;

    deleteSL("NOTES", root);

    temp = createSL("TEST", 0, root);
    if (temp != NULL)temp->details = detailsF("06/06/18", "0", "R/W");
    if (temp != NULL)root->sibling->sibling = temp;


    printf("--------------File Content--------------\n");
    traverseSL(root);
    printf("\n");
}