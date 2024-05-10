#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "doubly_linked_list.h"


node* create_node (int val) {
  node* list = malloc(sizeof(node));
  list->val = val;
  list->next = NULL;
  list->prev = NULL;
  return list;
}

linked_list* list_from_array (int* array, int length) {
  if (length == 0) {return NULL;}
  linked_list* list = malloc(sizeof(linked_list));
    list->length = length;
  list->head = create_node(array[0]);
    node *true_head = list->head;
  for (int i = 1; i < length; i++) {
    node* next_node = create_node(array[i]);
    list->head->next = next_node;
    list->head->next->prev = list->head;
    list->head = list->head->next;
  }
    list->tail = list->head;
    list->head = true_head;
  return list;
}

void print_list (linked_list * list) {
    node *true_head = list->head;
  while (list->head != NULL) {
    printf("%d\n", list->head->val);
    if (list->head->prev) printf("Value of prev %d\n", list->head->prev->val);
    if (list->head->next) printf("Value of next %d\n", list->head->next->val);
    list->head = list->head->next;
  }
    list->head = true_head;
}

void print_head (node *head) {
    node *true_head = head;
    while (head != NULL) {
        printf("%d\n", head->val);
        if (head->prev) printf("Value of prev %d\n", head->prev->val);
        if (head->next) printf("Value of next %d\n", head->next->val);
        head = head->next;
    }
    head = true_head;
}

void prepend(linked_list *list, int val) {
    node *new_node = create_node(val);
    node **head = &list->head;
    if (!*head) {
        *head = new_node;
        list->tail = new_node;
        list->length++;
        return;
    }
    list->length++;
    new_node->next = *head;
    (*head)->prev = new_node;
    *head = new_node;
}

node * append (linked_list *list, int val) {
    node *new_node = create_node(val);
    node **tail = &list->tail;
    if (!*tail) {
        *tail = new_node;
        list->head = new_node;
        list->length++;
        return new_node;
    }
    list->length++;
    (*tail)->next = new_node;
    new_node->prev = *tail;
    *tail = new_node;
    return new_node;
}

node* walk_list (linked_list *list, int index) {
    // If index is close to the head walk fron the head
    node *head = list->head;
    if (index <= list->length / 2) {
        for (int i = 0; i < index; i++) {
            head = head->next;
        }
        return head;
    }
    // If closer to the end walk back from the tail
    node *tail = list->tail;
    int steps = list->length - index - 1;
    for (int i = 0; i < steps; i++) {
        tail = tail->prev;
    }
    return tail;
}

int get (linked_list *list, int index) {
    node *node = walk_list(list, index);
    return node->val;
}

void add_first_node (linked_list *list, int value) {
    node *new_node = create_node(value);
    list->head = new_node;
    list->tail = new_node;
    list->length++;
}

void insert_at (linked_list *list, int index, int value) {
    node *new_node = create_node(value);
    if (!list->head) { add_first_node(list, value); return; }
    if (index == 0) { prepend(list, value); return; }
    if (index >= list->length) { append(list, value); return; }
    node *curr_node = walk_list(list, index);

    node *prev = curr_node->prev;
    new_node->prev = prev;
    new_node->next = curr_node;
    curr_node->prev = new_node;
    prev->next = new_node;

    list->length++;
    return; 
}

int remove_value (linked_list *list, int value) {
    node *curr_node = list->head;
    if (curr_node->val == value) {
        list->head = list->head->next;
        list->head->prev = NULL;
        free(curr_node);
        return 0;
    }
    if (list->tail->val == value) { 
        int index = list->length - 1;
        remove_back(list); 
        return index;
    }
    int i;
    for (i = 0; i < list->length && curr_node->val != value; i++) {
        curr_node = curr_node->next;
    }
    if (!curr_node) {
        return -1;
    }
    node *prev = curr_node->prev;
    prev->next = curr_node->next;
    curr_node->next->prev = prev;
    free(curr_node);

    list->length--;
    return i;
}

void remove_back (linked_list *list) {
    if (!list->head) {return;}
    if (list->length == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->length--;
        return;
    }

    node *tail = list->tail;
    node *prev = tail->prev;
    prev->next = NULL;
    list->tail = prev;
    free(tail);
    list->length--;
    return; 
}

void remove_at (linked_list *list, int index) {
    if (!list->head) {return;}
    if (index == 0) {
        node *head = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(head);
        return;
    }
    if (index >= list->length - 1) {remove_back(list); return;}
    node *curr_node = walk_list(list, index);

    node *prev = curr_node->prev;
    prev->next = curr_node->next;
    curr_node->next->prev = prev;
    free(curr_node);

    list->length--;
    return; 
}

void dl_list_driver () {
    int arr[5] = {45, 23, 62, 58, 67};
    int length = sizeof(arr) / sizeof(int);
    linked_list *list = list_from_array(arr, length);
    // prepend(list, 59);
    // append(list, 145);
    // printf("%d\n", get(list, 1));
    // remove_back(list);
    // remove_at(list, 2);
    printf("%d\n", remove_value(list, 58));
    insert_at(list, 2, 157);
    print_list(list);
}

