#include "List.h"


List *list_create(int size) {
    List *set = (List *) malloc(sizeof(List));
    is_listNull(set);

    set->data = (char **) calloc(size, sizeof(char *));
    set->size = size;
    set->index = 0;
    return set;
}

bool list_addItem(List *list, char *value) {

    is_listNull(list);

    for (int i = 0; i <= list->index; ++i) {
        if (list->data[i] == NULL) {
            list->data[i] = malloc(strlen(value)+1 * sizeof(char));
            strcpy(list->data[i], value);
            list->index++;
            return 1;
        }
    }

//    list->data[list->index] = value;
//    list->index++;

    return 0;
}

bool list_lookup(List *list, char *name) {

    is_listNull(list);

    for (int i = 0; i < list->index; ++i) {
        if (strcmp(list->data[i], name) == 0) {
            return true;
        }
    }
    return false;
}

void list_print(List *list) {

    is_listNull(list);

    for (int i = 0; i < list->index; ++i) {
        printf("%d: %s\n", i, *(list->data + i));
    }
}

bool list_delete(List *list) {
    for (int i = 0; i < list->index ; ++i) {
        free(list->data[i]);
    }

    free(list->data);
    free(list); list = NULL;

    return true;
}

bool is_listNull(List *list) {

    if (list == NULL) {
        fprintf(stderr, "The list is NULL");
        exit(EXIT_FAILURE);
    }
    return false;
}