//
// Created by Toor on 6/28/2022.
//

#ifndef TESTFIELD_LINKEDLIST_H
#define TESTFIELD_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Self-referential structure */
typedef struct node {
    char *data;
    struct node *next;
}node_t;

typedef node_t *LinkedList ;

LinkedList create_LinkedList(void);
void insert_AtEndOf_LinkedList(LinkedList *head, char *data);
void delete_LinkedList(LinkedList *head);
void print_LinkedList(LinkedList head);


#endif //TESTFIELD_LINKEDLIST_H
