#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "binary_tree.h"

binary_node ** find_node_bfs (binary_node ** node, int needle) {
    binary_node ** found_node = NULL;
    binary_node *** arr = NULL;
    arrput(arr, node);
    while (arrlen(arr) > 0) {
        binary_node **curr_node = arr[0];
        // free(*(arr[0]));
        arrdel(arr, 0);
        if ((*curr_node)->val == needle) {
            found_node = curr_node;
        }
        if ((*curr_node)->left) {
            arrput(arr, &(*curr_node)->left);
        }
        if ((*curr_node)->right) {
            arrput(arr, &(*curr_node)->right);
        }
    }
    return found_node;
}

binary_node ** find_node (binary_node ** node, int value) {
    binary_node ** found_node = find_node_bfs(node, value);
    return found_node;
}

int max (int a, int b) {
    if (b > a) {return b;} else {return a;}
}

int get_height(binary_node *node) {
    if (!node) return -1;
    return max(get_height(node->left), get_height(node->right)) + 1;
}

binary_node * get_biggest_child (binary_node ** node, binary_node *parent) {
    int val;
    binary_node * biggest_node = NULL;
    binary_node * walk = *node;
    if (!(*node)->right) {
        walk->parent = parent;
        biggest_node = walk;
    }
    else {
        while (walk->right) {
            parent = walk;
            walk = walk->right;
        }
        biggest_node = walk;
    }
    biggest_node->parent = parent;
    return biggest_node;
}

binary_node * get_smallest_child (binary_node ** node, binary_node *parent) {
    int val;
    binary_node * smallest_node = NULL;
    binary_node * walk = *node;
    if (!(*node)->left) {
        walk->parent = parent;
        smallest_node = walk;
    }
    else {
        while (walk->left) {
            parent = walk;
            walk = walk->left;
        }
        smallest_node = walk;
    }
    smallest_node->parent = parent;
    return smallest_node;
}

bool delete (binary_node * head, int value) {
    binary_node ** node_ptr = find_node(&head, value);
    binary_node * node = *node_ptr;
    if (!node) return false;
    if (!node->left && !node->right) {
        *node_ptr = NULL;
        return true;
    }
    int left_h = get_height(node->left) + 1;
    int right_h = get_height(node->right) + 1;
    if (left_h >= right_h) {
        printf("Went left\n");
        binary_node * found_child = get_biggest_child(&node->left, node);
        if (node == found_child->parent) {
            printf("One deep\n");
            binary_node * node_right = node->right;
            *node_ptr = found_child;
            (*node_ptr)->right = node_right;
        } else {
            printf("More than One deep\n");
            node->val = found_child->val;
            found_child->parent->right = found_child->left;
        }
    } else {
        printf("Went right\n");
        binary_node * found_child = get_smallest_child(&node->right, node);
        if (node == found_child->parent) {
            printf("One deep\n");
            binary_node * node_left = node->left;
            *node_ptr = found_child;
            (*node_ptr)->left = node_left;
        } else if (node->right == found_child->parent && found_child->parent->val == found_child->val) {
            printf("Two deep, but child and child's child have equal value\n");
            binary_node * node_left = node->left;
            *node_ptr = found_child->parent;
        } else {
            printf("More than One deep\n");
            node->val = found_child->val;
            found_child->parent->left = found_child->right;
        }
    }
    return true;
}

// Figured it out
int main (int argc, char **argv) {
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    binary_node *tree1 = create_binary_tree(arr, length);
    // bfs_print_sequencial(tree1);
    binary_tree_print(tree1);
    insert(tree1, 27);
    insert(tree1, 6);
    insert(tree1, 8);
    insert(tree1, 6);
    insert(tree1, 9);
    binary_tree_print(tree1);
    delete(tree1, 5);
    // bfs_print_sequencial(tree1);
    binary_tree_print(tree1);
}
