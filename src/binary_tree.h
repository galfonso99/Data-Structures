#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define STB_DS_IMPLEMENTATION
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "stb_ds.h"

/* Only some nodes will have a parent node pointer for algo reasons */
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

binary_node *create_binary_tree (int *arr, int length) {
    binary_node *tree = create_binary_node(arr[0]);
    binary_node *new1 = create_binary_node(arr[1]);
    binary_node *new2 = create_binary_node(arr[2]);
    binary_node *new3 = create_binary_node(arr[3]);
    binary_node *new4 = create_binary_node(arr[4]);
    binary_node *new5 = create_binary_node(arr[5]);
    binary_node *new6 = create_binary_node(arr[6]);
    tree->left = new1;
    tree->right = new2;
    new1->left = new3;
    new1->right = new4;
    new2->left = new5;
    new2->right = new6;
    if (length > 7) {
        binary_node *new7 = create_binary_node(arr[7]);
        new2->right->right = new7;
    }
    return tree;
}

void recurse_print (binary_node *node) {
    if (!node) {
        return;
    }
    printf("%d\n", node->val);
    recurse_print(node->left);
    recurse_print(node->right);
}

void pre_order_print (binary_node *head) {
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

void bfs_print_sequencial (binary_node *head) {
    binary_node **arr = NULL;
    int i = 0;
    int h = 0;
    arrput(arr, head);
    while (arrlen(arr) > 0) {
        binary_node *curr_node = arr[0];
        /* free(arr[0]); */
        arrdel(arr, 0);
        /* curr_node ? printf("%d ", curr_node->val) : printf("| "); */
        if (curr_node) {
            printf("%d ", curr_node->val);
        }
        if (!curr_node) continue;
        arrput(arr, curr_node->left);
        arrput(arr, curr_node->right);
    }
    printf("\n");
    return;
}

void bfs_print (binary_node *head) {
    binary_node **arr = NULL;
    int i = 0;
    int h = 0;
    arrput(arr, head);
    while (arrlen(arr) > 0) {
        binary_node *curr_node = arr[0];
        /* free(arr[0]); */
        arrdel(arr, 0);
        /* int print_val = curr_node != NULL ? curr_node->val : -1; */
        /* printf("%d ", print_val); */
        curr_node ? printf("%d ", curr_node->val) : printf("| ");
        /* curr_node ? printf("%d (%d)", curr_node->val, curr_node->height > 6 ? -1  */
        /*                 : curr_node->height) : printf("| "); */
        i+=1;
        /* printf("%d, %d \n", i, ((1 << h))); */
        if (i == ((1 << h))) {
            /* printf("WE got there\n"); */
            printf("\n");
            i = 0;
            h += 1;
        }
        if (!curr_node) continue;
        arrput(arr, curr_node->left);
        arrput(arr, curr_node->right);
    }
    printf("\n");
    return;
}

void binary_tree_print (binary_node *head) {
    bfs_print(head);
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
        binary_node *curr_node = arr[0];
        free(arr[0]);
        arrdel(arr, 0);
        if (curr_node->val == needle) {
            return true;
        }

        if (curr_node->left) {
            arrput(arr, curr_node->left);
        }
        if (curr_node->right) {
            arrput(arr, curr_node->right);
        }
    }
    return false;
}

bool compare (binary_node *tree1, binary_node *tree2) {
    if (!tree1 && !tree2) {
        return true;
    }

    if (tree1 && tree2) {
        return tree1->val == tree2->val 
            && compare(tree1->left, tree2->left)
            && compare(tree1->right, tree2->right);
    }
    return false;
}

bool bad_depth_first_compare_that_doesnt_early_return (binary_node *tree1, binary_node *tree2) {
    // This one is mine I couldnt figure out how to early return;
    if (!tree1 && !tree2) {
        return true;
    }
    if (!tree1 || !tree2) {
        return false;
    }

    if (tree1->val != tree2->val) {
        return false;
    }
    bool left_is_equal = compare(tree1->left, tree2->left);
    bool right_is_equal = compare(tree1->right, tree2->right);
    return left_is_equal && right_is_equal;

}
bool fixed_dfs_compare_with_early_return (binary_node *tree1, binary_node *tree2) {
    // This one uses logic shortcircuiting to establish that if at any point a left
    // value is false the logic shortcircuits to false
    if (!tree1 && !tree2) {
        return true;
    }
    if (!tree1 || !tree2) {
        return false;
    }

    if (tree1->val != tree2->val) {
        return false;
    }
    return compare(tree1->left, tree2->left) && compare(tree1->right, tree2->right);

}

bool compare_breath_first (binary_node *tree1, binary_node *tree2) {
    binary_node **arr = NULL;
    arrput(arr, tree1);
    arrput(arr, tree2);
    while (arrlen(arr) > 0) {
        binary_node *node1 = arr[0];
        binary_node *node2 = arr[1];
        // Pop from the front twice 
        arrdel(arr, 0);
        arrdel(arr, 0);
        if (!node1 && !node2) {
            continue;
        }
        if (!node1 || !node2) {
            return false;
        }
        if (node1->val != node2->val) {
            return false;
        }
        
        arrput(arr, node1->left);
        arrput(arr, node2->left);
        arrput(arr, node1->right); 
        arrput(arr, node2->right); 
        for (int i = 0; i < arrlen(arr); i++) {
            if (arr[i]) {
                printf("%d, ", arr[i]->val);
            }
        }
        printf("\n");
        // Free the nodes
        free(node1);
        free(node2);
    }
    return true;
}


void binary_tree_driver () {
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    binary_node *tree1 = create_binary_tree(arr, length);
    bfs_print_sequencial(tree1);
    binary_tree_print(tree1);
}
#endif
