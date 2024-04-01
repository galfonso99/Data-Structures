#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H

#define STB_DS_IMPLEMENTATION
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    void *data;
    struct node* next;
} Node;

typedef struct list {
    int length;
    Node * head;
} List;

List * create_list () {
    List* list = (List*) malloc(sizeof(List));
    list->length = 0;
    list->head = NULL;
    return list;
}

void add_to_list (List *list, void *data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->length++;
}

#endif
