#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "binary_tree.h"

// Try to implement a generic Linked list and a generic Binary Tree 
// Only implement adding a value and printing the whole thing and then test it with int, char, uint32_t

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
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->length++;
}

int main (int argc, char **argv) {
    int arr[5] = {45, 23, 62, 58, 67};
    // int length = sizeof(arr) / sizeof(int);
    // linked_list *list = list_from_array(arr, length);
    List *list = create_list();
    float x = 23.4;
    add_to_list(list, &x);
    float y = 53.3;
    add_to_list(list, &y);
    float z = 85.2;
    add_to_list(list, &z);
    float g = 23.6;
    add_to_list(list, &g);
    Node *head = list->head;
    while (head) {
        printf("%f\n", *(float*) head->data);
        head = head->next;
    }

}
