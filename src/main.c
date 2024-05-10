#define STB_DS_IMPLEMENTATION
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "doubly_linked_list.h"


#define MAX_KEY_SIZE 15

typedef struct {
    // doubly-linked list
    uint32_t capacity;
    linked_list * list;
    hashmap * lookup;  // hashmap would be Map<string, ListNode>
    hashmap * reverse_lookup; //Map<uintptr * <list_node>, char *>
    hashmap * lookup_size;   // Map<char *, size_t>
} LRU;

uintptr_t hm_get(hashmap * map, void * key, size_t size) {
    uintptr_t out;
    hashmap_get(map, key, size, &out);
    return out;
}

void hm_set(hashmap * map, void * key, size_t size, uintptr_t value) {
    hashmap_set(map, key, size, value);
}

LRU * lru_create (uint32_t capacity) {
    LRU * lru = malloc(sizeof(LRU));
    lru->capacity = capacity;
    lru->list = malloc(sizeof(linked_list));
    lru->lookup = hashmap_create();
    lru->reverse_lookup = hashmap_create();
    lru->lookup_size = hashmap_create();
    return lru;
}

// This prob doesnt work not gonna test it, kinda useless except for testing
LRU * create_lru_with_array (void * array, int length, uint32_t capacity) {
    LRU * lru = malloc(sizeof(LRU));
    lru->capacity = capacity;
    lru->list = malloc(sizeof(linked_list));
    lru->lookup = hashmap_create();
    lru->reverse_lookup = hashmap_create();
    // run lru_set for each item in array
    for (int i = 0; i < length; i++) {
        // lru set for (array[i])
    }
    return lru;
}

node * lru_retrieve_node (LRU * lru, void * key, size_t size) {
    uintptr_t out = hm_get(lru->lookup, key, size);
    node * curr_node = (node * ) out;
    return curr_node;
}

void move_node_front (LRU * lru, node * curr_node) {
    if (lru->list->length == 0) {
        return;
    }
    node * next = curr_node->next;
    node * prev = curr_node->prev;
    if (next) {
        next->prev = prev;
    }
    if (prev) {
        prev->next = next;
    }
    if (curr_node == lru->list->tail) {
        lru->list->tail = lru->list->tail->prev;
    }
    curr_node->prev = NULL;
    curr_node->next = lru->list->head;
    lru->list->head->prev = curr_node;
    lru->list->head = curr_node;
}

void insert_front_lru (LRU * lru, void * key, size_t size, int value) {
    node * new_node = create_node(value);
    new_node->prev = NULL;
    new_node->next = lru->list->head;
    if (!lru->list->head) {
        lru->list->head = new_node;
        lru->list->tail = new_node;
    } else {
        lru->list->head->prev = new_node;
        lru->list->head = new_node;
    }
    lru->list->length++;
    hm_set(lru->lookup, key, size, (uintptr_t) new_node);
    hm_set(lru->lookup_size, key, MAX_KEY_SIZE, (uintptr_t) size);
    hm_set(lru->reverse_lookup, new_node, sizeof(node *), (uintptr_t)((char *) key));
}

bool delete_last_node(LRU * lru) {
    linked_list * list = lru->list;
    node * curr_tail = list->tail;
    printf("This is the last value: %d\n", curr_tail->val);
    if (list->length == 0) {
        return false;
    }
    if (curr_tail->prev) {
        curr_tail->prev->next = NULL;
    } else {
        printf("Tail has no prev\n");
        list->head = NULL;
        list->tail = NULL;
    }
    list->length--;
    char * string = (char *) hm_get(lru->reverse_lookup, curr_tail, sizeof(node *));
    printf("Deleting node with key :{%s}\n", string);
    size_t key_size = (size_t) hm_get(lru->lookup_size, string, MAX_KEY_SIZE);
    printf("Size of the key: %lu\n", key_size);
    hashmap_remove(lru->lookup, (void *) string, key_size);
    hashmap_remove(lru->reverse_lookup, curr_tail, sizeof(node *));
    free(curr_tail);
    return true;
}

void lru_insert (LRU * lru, void * key, size_t size, int value) {
    node * new_node = create_node(value);
    node * tail = lru->list->tail;
    lru->list->length++;
    new_node->next = NULL;
    new_node->prev = tail;
    if (tail) {
        tail->next = new_node;
        lru->list->tail = new_node;
    } else {
        lru->list->head = new_node;
        lru->list->tail = new_node;
    }
    hm_set(lru->lookup, key, size, (uintptr_t) new_node);
    hm_set(lru->lookup_size, key, MAX_KEY_SIZE, (uintptr_t) size);
    hm_set(lru->reverse_lookup, new_node, sizeof(node *), (uintptr_t)((char *) key));
}

bool lru_delete (LRU * lru, void * key, size_t size) {
    node * curr_node = lru_retrieve_node(lru, key, size);
    if (!curr_node) {
        return false;
    }
    if (curr_node->next) {
        curr_node->next->prev = curr_node->prev;
    }
    if (curr_node->prev) {
        curr_node->prev->next = curr_node->next;
    }
    lru->list->length--;
    hashmap_remove(lru->lookup, key, size);
    hashmap_remove(lru->reverse_lookup, curr_node, sizeof(node *));
    free(curr_node);
    return true;
}

int lru_get (LRU * lru, void * key, size_t size) {
    // check the cache to see if the the key value pair exists
    //     if not exist return null / -1 in the case of C cuz int cant return null
    //     if exists remove the node from where it was and move it to the front
    //     get the value out and return it
    node * curr_node = lru_retrieve_node(lru, key, size);
    if (!curr_node) {
        return -1; // equivalent of returning NULL
    }
    move_node_front(lru, curr_node);
    return curr_node->val;
}

void lru_update (LRU * lru, void * key, size_t size, int value) {
    // if key exist   
    //        Move the found node to front
    //        Update the value of the now front node
    // else insert but first
    //      check capacity and if over capacity delete last
    //
    // int output = lru_get(lru, key, size);
    node * curr_node = lru_retrieve_node(lru, key, size);
    if (curr_node) {
        move_node_front(lru, curr_node);
        lru->list->head->val = value;
    } else if (lru->list->length == lru->capacity) {
        printf("Capacity overflow, now deleting last visited node\n");
        delete_last_node(lru);
        insert_front_lru(lru, key, size, value);
    }else {
        insert_front_lru(lru, key, size, value);

    }

}

void print_entry(void* key, size_t ksize, uintptr_t value, void* usr) {
	printf("Entry \"%s\": %d\n", (char *) key, (int) ((node *) value)->val);
}

void print_reverse(void* key, size_t ksize, uintptr_t value, void* usr) {
	printf("The value of the node \"%d\": %s\n", ((node *) key)->val, ((char *) value));
}

// Note: Consider implementing a hash_map at the end of this course, there's a lot of components
int main (int argc, char **argv) {
    LRU * lru = lru_create(5);
    // lru_update(lru, "alpha", sizeof("alpha"), 55);
    // lru_update(lru, "bravo", sizeof("bravo"), 72);
    // lru_update(lru, "charlie", sizeof("charlie"), 88);
    // lru_update(lru, "delta", sizeof("delta"), 43);
    // lru_update(lru, "echo", sizeof("echo"), 669);
    // lru_update(lru, "bravo", sizeof("bravo"), 134);
    // lru_update(lru, "delta", sizeof("delta"), 777);
    lru_insert(lru, "alpha", sizeof("alpha"), 55);
    lru_insert(lru, "bravo", sizeof("bravo"), 72);
    lru_insert(lru, "charlie", sizeof("charlie"), 88);
    lru_insert(lru, "delta", sizeof("delta"), 43);
    // int b2 = lru_get(lru, "bravo", sizeof("bravo"));
    // lru_update(lru, "charlie", sizeof("charlie"), 45);
    // int charlie = lru_get(lru, "charlie", sizeof("charlie"));
    // lru_update(lru, "delta", sizeof("delta"), 73);
    // int delta = lru_get(lru, "delta", sizeof("delta"));
    // int echo = lru_get(lru, "echo", sizeof("echo"));
    // printf("the value of the last node: %d\n", lru->list->tail->val);
    // lru_update(lru, "golf", sizeof("golf"), 553);
    // int golf = lru_get(lru, "golf", sizeof("golf"));
    // printf("The head %d\n", lru->list->head->val);
    // printf("Bravo: %d\n", b2);
    // printf("Echo: %d\n", echo);
    // printf("Charlie %d\n", charlie);
    // printf("Delta: %d\n", delta);
    // printf("Golf: %d\n", golf);
    // printf("Alpha after deletion %lru_delete\n", lru_get(lru, "alpha", sizeof("alpha")));
    lru_delete(lru, "delta", sizeof("delta"));
    hashmap_iterate(lru->lookup, print_entry, NULL);
    hashmap_iterate(lru->reverse_lookup, print_reverse, NULL);
    // printf("%p\n", (void *) out);
    // printf("%d\n", my_node->val);
    printf("%d\n", lru->list->length);

}
