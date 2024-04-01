#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define STB_DS_IMPLEMENTATION
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "stb_ds.h"

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} binary_node;

binary_node * create_binary_node (int value) {
    binary_node *node = (binary_node*) malloc(sizeof(binary_node));
    node->val = value;
    return node;
}

void recurse_print (binary_node *node) {
    if (!node) {
        return;
    }
    printf("%d\n", node->val);
    recurse_print(node->left);
    recurse_print(node->right);
}

void pre_order_print (binary_node *head, int length) {
    int *arr = (int*) calloc(length, sizeof(int));
    recurse_print(head);
}

int * pre_order_walk (binary_node *node, int ** path) {
    if (!node) {
        return *path;
    }
    arrput(*path, node->val);
    pre_order_walk(node->left, path);
    pre_order_walk(node->right, path);
    return *path;
    
}

int * pre_order_traversal (binary_node *head) {
    int *arr = NULL;
    int * path = pre_order_walk(head, &arr);
    return path;
}

int * in_order_walk (binary_node *node, int ** path) {
    if (!node) {
        return *path;
    }
    in_order_walk(node->left, path);
    arrput(*path, node->val);
    in_order_walk(node->right, path);
    return *path;
    
}

int * in_order_traversal (binary_node *head) {
    int *arr = NULL;
    int * path = in_order_walk(head, &arr);
    return path;
}

int * post_order_walk (binary_node *node, int ** path) {
    if (!node) {
        return *path;
    }
    post_order_walk(node->left, path);
    post_order_walk(node->right, path);
    arrput(*path, node->val);
    return *path;
}

int * post_order_traversal (binary_node *head) {
    int *arr = NULL;
    int * path = post_order_walk(head, &arr);
    return path;
}

bool bfs (binary_node *head, int needle) {
    binary_node **arr = NULL;
    arrput(arr, head);
    while (arrlen(arr) > 0) {
        binary_node *last_node = arr[arrlen(arr) - 1];
        if (last_node->val == needle) {
            return true;
        }

    }
}

void binary_tree_driver () {
    int arr[5] = {45, 23, 62, 58, 67};
    // int length = sizeof(arr) / sizeof(int);
    // linked_list *list = list_from_array(arr, length);
    // binary_tree_driver();
    binary_node *tree = create_binary_node(7);
    binary_node *new1 = create_binary_node(23);
    binary_node *new2 = create_binary_node(3);
    binary_node *new3 = create_binary_node(5);
    binary_node *new4 = create_binary_node(4);
    binary_node *new5 = create_binary_node(18);
    binary_node *new6 = create_binary_node(21);
    tree->left = new1;
    tree->right = new2;
    new1->left = new3;
    new1->right = new4;
    new2->left = new5;
    new2->right = new6;
    int length = 7;
    /* pre_order_print(tree, length); */
    // int * traversal = pre_order_traversal(tree);
    int * traversal = post_order_traversal(tree);
    for ( int i = 0; i < length; i++) {
        printf("%d\n", traversal[i]); 
    }
}



#endif
