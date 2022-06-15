//
// Created by Toor on 6/2/2022.
//

#ifndef COMPILER_LIST_H
#define COMPILER_LIST_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct List {
    char **data;
    int size;
    int index;
} List;


List *list_create(int size);
bool list_addItem(List *list, char *value);
void list_print(List *list);
bool list_delete(List *list);
bool list_lookup(List *list, char *name);
bool is_listNull(List *list);



#endif //COMPILER_LIST_H
