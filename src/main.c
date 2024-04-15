#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "binary_tree.h"
// #include "stb_ds.h"
// #include "min_heap.h"

binary_node * get_inorder_predecessor (binary_node * root) {
        printf("Predecessor \n");
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
        printf("Special case reached\n");
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

binary_node * delete (binary_node * root, int value) {
    if (root == NULL) return root;
    if (root->val > value) {
        root->left = delete(root->left, value);
        return root;
    }
    else if (root->val < value) {
        root->right = delete(root->right, value);
        return root;
    }
    if (root->left == NULL) {

        printf("Left is empty \n");
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


int main (int argc, char **argv) {
    // int arr[13] = {12, 54, 15, 61, 77, 33, 34, 78, 80, 91, 100, 55, 77};
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    // binary_tree_driver();
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
    binary_node * deleted_root = delete(tree1, 5);
    binary_tree_print(tree1);
}

// for (int i = 0; i < length; i++) {
//     printf("%d\n", arr[i]);
// }
