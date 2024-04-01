#ifndef GENERIC_BINARY_TREE_H
#define GENERIC_BINARY_TREE_H

#define STB_DS_IMPLEMENTATION
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Confirmed that this binary tree works on any type 
// But I wont be using generic binary tree from now on because it is too 
// cumbersome in C Lang

typedef struct tree_node {
    void *data;
    struct tree_node* left;
    struct tree_node* right;
} TreeNode;

typedef struct tree {
    int size;
    TreeNode * root;
} Tree;

Tree * create_tree () {
    Tree* tree = (Tree*) malloc(sizeof(Tree));
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

TreeNode * create_tree_node (void * data) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* TreeNode* create_tree_from_array (int * array, int length) { */
/**/
/* } */

/* void add_to_tree (Tree *tree, void *data) { */
/*     TreeNode *new_node = (TreeNode*) malloc(sizeof(TreeNode)); */
/*     new_node->data = data; */
/*     new_node->next = list->head; */
/*     list->head = new_node; */
/*     list->length++; */
/* } */

void recurse_print (TreeNode *node) {
    if (!node) {
        return;
    }
    printf("%c\n", *(char*) node->data);
    recurse_print(node->left);
    recurse_print(node->right);
}

void pre_order_print (TreeNode *head, int length) {
    recurse_print(head);
}

void generic_tree_driver () {
    Tree *tree = create_tree();
    char a = 'a';
    TreeNode *root = create_tree_node(&a);
    char b = 'b';
    TreeNode *new1 = create_tree_node(&b);
    char c = 'c';
    TreeNode *new2 = create_tree_node(&c);
    char d = 'd';
    TreeNode *new3 = create_tree_node(&d);
    char e = 'e';
    TreeNode *new4 = create_tree_node(&e);
    char f = 'f';
    TreeNode *new5 = create_tree_node(&f);
    char g = 'g';
    TreeNode *new6 = create_tree_node(&g);
    root->left = new1;
    root->right = new2;
    new1->left = new3;
    new1->right = new4;
    new2->left = new5;
    new2->right = new6;
    int length = 7;
    tree->size = length;
    pre_order_print(root, length);
    
}

#endif
