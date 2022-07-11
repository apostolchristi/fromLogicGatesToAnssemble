//
// Created by Toor on 6/28/2022.
//

#include "LinkedList.h"

LinkedList create_LinkedList(void) {

    LinkedList newNode = malloc(sizeof(node_t));
    newNode->data = NULL;
    newNode->next = NULL;
    return newNode;
}

void insert_AtEndOf_LinkedList(LinkedList *head, char *data) {
    LinkedList current = *head;

    //Only once for head
    static char flag = 1;
    if (flag == 1) {
        current->data = malloc(strlen(data) * sizeof(*data) + 1);
        strcpy(current->data, data);
        flag = 0;
        return;
    }

    /* Make sure the list is not empty or at the end of it, and we traverse it */
    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }
        /* now we can add a new variable */
        current->next = malloc(sizeof(node_t));
        current->next->data = malloc(strlen(data) * sizeof(*data) + 1);
        strcpy(current->next->data, data);
        current->next->next = NULL;
    }
        /* We are at the end of the list */
    else {
        current = malloc(sizeof(node_t));
        current->data = malloc(strlen(data) * sizeof(*data) + 1);
        strcpy(current->data, data);
        current->next = NULL;
        *head = current;
    }
}

void print_LinkedList(LinkedList head) {
    if (head == NULL) {
        printf("LinkedList is empty, nothing to print\n");
        return;
    }

    printf("The list is:\n");
    while (head != NULL) {
        printf("-->%s\n", head->data);
        head = head->next;
    }
}


void delete_LinkedList(LinkedList *head) {

    LinkedList temPtr = NULL;

    if (*head == NULL) {
        printf("LinkedList is empty, nothing to delete\n");
        return;
    }

    while (*head != NULL) {
        temPtr = *head; /* hold onto node being removed*/
        *head = (*head)->next;  /* de-thread the node*/
        free(temPtr->data);
        free(temPtr);
    }

}
