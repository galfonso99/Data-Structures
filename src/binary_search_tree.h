
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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
    struct node *parent;
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

bool find (binary_node *node, int needle) {
    if (!node) return false;
    if (node->val == needle) {
        return true;
    } else if (node->val < needle) {
        return find(node->right, needle);
    }
    return find(node->left, needle);
}

binary_node * get_node (binary_node *node, int needle) {
    if (!node) return NULL;
    if (needle == node->val) {
        return node;
    } else if (needle < node->val) {
        return get_node(node->left, needle);
    }
    return get_node(node->right, needle);
}

bool insert_bst (binary_node *node, int value) {
    if (!node) {
        return false;
    }

    if (value <= node->val) {
        if (!node->left) {
            node->left = create_binary_node(value);
            return true; 
        }
        return insert_bst(node->left, value);
    } else if (value > node->val) {
        if (!node->right) {
            node->right = create_binary_node(value);
            return true; 
        }
        return insert_bst(node->right, value);
    }
    return false;
}


bool insert_with_pointer (binary_node **node, int value) {
    if (!*node) {
        binary_node *new_node = create_binary_node(value);
        *node = new_node;
        return true;
    }
    if (value <= (*node)->val) {
        return insert_with_pointer(&(*node)->left, value);
    } else if (value > (*node)->val) {
        return insert_with_pointer(&(*node)->right, value);
    }
    return false;
}

bool insert_with_parent (binary_node *node, binary_node *parent, int value) {
    if (!node) {
        binary_node *new_node = create_binary_node(value);
        bool insert_left = value <= parent->val;
        if (insert_left) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        return true;
    }
    if (value <= node->val) {
        return insert_with_parent(node->left, node, value);
    } else if (value > node->val) {
        return insert_with_parent(node->right, node, value);
    }
    return false;
}

bool insert (binary_node *node, int value) {
   return insert_with_parent(node, NULL, value); 
}

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

int max (int a, int b) {
    if (b > a) {return b;} else {return a;}
}

int get_height(binary_node *node) {
    if (!node) return -1;
    return max(get_height(node->left), get_height(node->right)) + 1;
}

binary_node * get_inorder_predecessor (binary_node * root) {
    binary_node * pred_parent = root;
    binary_node * pred = root->left;
    while (pred->right != NULL) {
        pred_parent = pred;
        pred = pred->right;
    }
    if (pred_parent != root) {
        pred_parent->right = pred->left;   
    }
    else {
        pred_parent->left = pred->left;
    }

    root->val = pred->val;
    return root;
}

binary_node * get_inorder_successor (binary_node * root) {
    binary_node * succ_parent = root;
    binary_node * succ = root->right;
    while (succ->left != NULL) {
        succ_parent = succ;
        succ = succ->left;
    }
    if (succ_parent == root) {
        succ_parent->right = succ->right;
    }
    // There is an edge case where if succ_parent and succ have the same value, then the resulting BST
    // Will have a Node with its right child having the same value as the parent and this breaks the rules
    // of my BST (equal values go to the left and only higher values go to the right). For instance
    //          5
    //        /  \
    //      5     6
    //           / 
    //          6
    // If we try to remove 5 (the top root) the left child of the first 6 gets removed and the value of the second
    // 6 gets copied to where 5 was and we end up with
    //          6
    //        /  \
    //      5     6
    // Which as you can see breaks the rules of this BST by having a 6 to the right of a 6 which should be implossible
    // and that is why the following case check is necessary
    // If the inorder successor is exactly 2 nodes deep and succ and succ_parent have equal value, then
    else if (succ->val == root->right->val) {
        succ_parent->left = NULL;
        binary_node * root_right = root->right;
        root->right = root->right->right;
        root_right->right = NULL;
        root->val = succ->val;
        binary_node * child = root->left;
        while (child->right != NULL) {
            child = child->right;
        }
        child->right = root_right;
    }
    // If succ_parent does not equal root
    else {
        succ_parent->left = succ->right;   
    }
    root->val = succ->val;
    return root;
}


binary_node * delete_node (binary_node * root, int value) {
    if (root == NULL) return root;
    if (root->val > value) {
        root->left = delete_node(root->left, value);
        return root;
    }
    else if (root->val < value) {
        root->right = delete_node(root->right, value);
        return root;
    }
    if (root->left == NULL) {
        binary_node * temp = root->right;
        return temp;
    }
    else if (root->right == NULL) {
        binary_node * temp = root->left;
        return temp;
    }

    else {
        int left_h = get_height(root->left) + 1;
        int right_h = get_height(root->right) + 1;
        bool left_is_deeper = left_h >= right_h;
        binary_node * inorder_child;
        if (left_is_deeper) {
            inorder_child = get_inorder_predecessor(root);
        }
        else {
            inorder_child = get_inorder_successor(root);
        }
        return inorder_child;
    }
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

binary_node ** find_node (binary_node ** node, int value) {
    binary_node ** found_node = find_node_bfs(node, value);
    return found_node;
}

bool delete_node_old (binary_node * head, int value) {
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

void binary_search_tree_driver () {
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    binary_node *tree1 = create_binary_tree(arr, length);
    binary_tree_print(tree1);
    insert(tree1, 27);
    insert(tree1, 6);
    insert(tree1, 8);
    insert(tree1, 6);
    insert(tree1, 9);
    insert(tree1, 5);
    insert(tree1, 7);
    binary_tree_print(tree1);
    binary_node * deleted_root = delete_node(tree1, 5);
    binary_tree_print(tree1);
}
#endif
