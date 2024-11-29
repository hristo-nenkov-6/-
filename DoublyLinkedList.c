#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* previous;
} Node;

Node* createNode(int data);
void insertAtBeggining(Node** head, int data);
void insertAtEnd(Node** head, int data);
void insertAtPos(Node** head, int data, int pos);
void deleteAtBeggining(Node** head);
void deleteAtEnd(Node** head);
void deleteAtPos(Node** head, int pos);
void printNodes(Node* head);
void printNodesReverse(Node* head);

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}

void insertAtBeggining(Node** head, int data) {
    Node* newNode = createNode(data);

    if(*head == NULL) { //Check if the list of nodes in empty (head is null)
        *head = newNode;
        return;
    }

    newNode->next = *head;
    (*head)->previous = newNode;
    *head = newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);

    if(*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->previous = temp;
}

void insertAtPos(Node** head,  int data, int position) {
    if(position < 0) {
        printf("Position cannot be less than 0");
        return;
    }

    if(position == 0) {
        insertAtBeggining(head, data);
    }

    Node* newNode = createNode(data);
    Node* temp = *head;
    for(int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Position is greater than number of nodes");
        return;
    }

    newNode->previous = temp->previous;
    newNode->next = temp;
    temp->previous = newNode;
}

void deleteAtBeggining(Node** head) {
    if(*head  == NULL) {
        printf("The list is empty");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    if(*head != NULL) {
        (*head)->previous = NULL;
    }
    free(temp);
}

void deleteAtEnd(Node** head) {
    if(*head == NULL) {
        printf("The list is empty");
        return;
    }

    Node* temp = *head;
    if(temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }

    temp->previous->next = NULL;
    free(temp);
}

void deleteAtPos(Node** head, int pos) {
    if(*head == NULL) {
        printf("List is empty");
        return;
    }

    if(pos == 0) {
        deleteAtBeggining(head);
        return;
    }

    Node* temp = *head;
    for(int i = 0; temp != NULL && i < pos; i++) {
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Position is greater than number of nodes");
        return;
    }

   if(temp->next == NULL) {
       temp->previous->next = NULL; //deletes at end
   }

    temp->previous->next = temp->next;
    temp->next->previous = temp->previous;
    free(temp);
}

void printNodes(Node* head) {
    Node* temp = head;
    if(head == NULL) {
        printf("List is empty");
        return;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

void printNodesReverse(Node* head) {
    Node* temp = head;
    if(head == NULL) {
        printf("List is empty");
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->previous;
    }

    printf("\n");
}

int main() {

    Node* head = NULL;

    insertAtEnd(&head, 10);
    printNodes(head);

    insertAtEnd(&head, 20);
    printNodes(head);

    insertAtBeggining(&head, 5);
    printNodes(head);

    insertAtPos(&head, 15, 2);
    printNodes(head);

    printNodes(head);
    printNodesReverse(head);

    deleteAtBeggining(&head);
    printNodes(head);

    deleteAtEnd(&head);
    deleteAtPos(&head, 1);

    printNodes(head);

    return 0;
}