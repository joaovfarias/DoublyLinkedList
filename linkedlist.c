#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Doubly Linked List 
// Inserting in alphabetical order
// Removing by string

typedef struct item{

    char item[20];
}item;

typedef struct node{

    item Nperson;
    struct node *next;
    struct node *prev;
}node;

node *Push(node *head, char *name);
int Empty(node *head);
void PrintList(node *head);
int ListLength(node *head);
node *Pop(node *head, char *name);

int main(){

    node *list = NULL;

    list = Push(list, "burguer");
    list = Push(list, "grill");
    list = Push(list, "sausage");
    list = Push(list, "heat");
    list = Push(list, "ketchup");

    PrintList(list);

    list = Pop(list, "grill");
    list = Pop(list, "ketchup");

    PrintList(list);

    printf("\n");
    
}

node *Pop(node *head, char *name){

    if (Empty(head)){
        printf("No name to Pop\n");
        return head;
    }

    for (node *tmp = head; tmp != NULL; tmp = tmp->next){
        if (strcmp(tmp->Nperson.item, name) == 0){
            if (tmp->prev == NULL){ // Element found is the first one
                head = tmp->next;
                head->prev = NULL;
                free(tmp);
                return head;
            }
            if (tmp->next == NULL){ // Element found is the last one
                tmp->prev->next = NULL;
                free(tmp);
                return head;
            }
            // Element found is between two
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            free(tmp);
            return head;
        }
    }

    printf("Name not found");
    return head;
}

node *Push(node *head, char *name){

    node *tmp = (node *)malloc(sizeof(node));

    strcpy(tmp->Nperson.item, name); 

    if (Empty(head)){
        head = tmp;
        tmp->next = NULL;
        tmp->prev = NULL;
        return head;
    }

    node *wP = head;
    node *bwP;

    while ( (wP != NULL) && (strcmp(wP->Nperson.item, tmp->Nperson.item) < 1) ){
        bwP = wP;
        wP = wP->next;
    }

    if (wP == NULL){ // Element has to be pushed in the last pos
        bwP->next = tmp;
        tmp->prev = bwP;
        tmp->next = NULL;
        return head;
    }

    if (wP->prev == NULL){ // Element has to be pushed in the first pos
        wP->prev = tmp;
        tmp->next = head;
        head = tmp;
        tmp->prev = NULL;
        return head;
    }

    // Element has to be pushed between two 
    wP->prev->next = tmp;
    tmp->next = wP;
    tmp->prev = wP->prev;
    wP->prev = tmp;
    return head;


}

int Empty(node *head){

    if (head == NULL){
        return 1;
    }
    return 0;
}

void PrintList(node *head){

    int counter = 1;

    printf("\n");
    for (node *tmp = head; tmp != NULL; tmp = tmp->next){
        printf("Item: %d\n", counter);
        printf("%s\n", tmp->Nperson.item);
        counter++;
    }

    printf("\n");
}

int ListLength(node *head){

    int count = 0;

    for (node *tmp = head; tmp != NULL; tmp = tmp->next){
        count++;
    }
    return count;
}

