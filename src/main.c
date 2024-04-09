#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "binary_tree.h"
// #include "generic_linked_list.h"
// #include "generic_binary_tree.h"

// Implement Deletion for BST 
// Quite complicated

binary_node ** find_node_dfs (binary_node ** node, int value, bool found) {
    if (!(*node)) {
        return NULL;
    }
    if ((*node)->val == value && !found)  {
        // binary_node ** found_node = node;
        return node;
    }
    find_node_dfs(&(*node)->left, value, found);
    find_node_dfs(&(*node)->right, value, found);
    return NULL;
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
binary_node * find_node_bfs_2 (binary_node * node, binary_node * parent, int needle) {
    binary_node * found_node = NULL;
    binary_node ** arr = NULL;
    arrput(arr, node);
    while (arrlen(arr) > 0) {
        binary_node *curr_node = arr[0];
        // free(arr[0]);
        arrdel(arr, 0);
        if (curr_node->val == needle) {
            found_node = curr_node;
        }
        if (curr_node->left) {
            arrput(arr, curr_node->left);
        }
        if (curr_node->right) {
            arrput(arr, curr_node->right);
        }
    }
    return found_node;
}

binary_node ** find_node (binary_node ** node, int value) {
    binary_node ** found_node = find_node_bfs(node, value);
    // if (*found_node && !(*found_node)->left && !(*found_node)->right) {
    //     *found_node = NULL;
    // }
    return found_node;
}


// binary_node * find_node (binary_node ** node, int value) {
//     if (!(*node)) return NULL;
//     if (value == (*node)->val) {
//         if (!(*node)->left && !(*node)->right) {
//             (*node) = NULL;
//         }
//         return *node;
//     } else if (value < (*node)->val) {
//         return find_node(&(*node)->left, value);
//     }
//     return find_node(&(*node)->right, value);
// }

void swap_with_child (binary_node * node) {
    if (node->left) {
        node->val = node->left->val;
        node->left = NULL;
    }
    node->val = node->right->val;
    node->right = NULL;
}
/* Add Heights to the nodes */
void add_heights (binary_node * node, int height) {
    if (!node) return;
    add_heights(node->left, height + 1);
    add_heights(node->right, height + 1);
    node->height = height;
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
        // *node = actual_root;
    }
    parent->left = walk->left;
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
        // *node = actual_root;
    }
    parent->right = walk->right;
    smallest_node->parent = parent;
    return smallest_node;
    
    
}

bool delete (binary_node * head, int value) {
    binary_node ** node_ptr = find_node(&head, value);
    binary_node * node = *node_ptr;
    // printf("%d\n", node->right);
    // binary_tree_print(node);
    // binary_node * node = *node_ptr;
    if (!node) printf("That shit is NULL cuh\n");
    if (!node) return false;
    if (!node->left && !node->right) {
        *node_ptr = NULL;
        return true;
    }
    // Node has both left and right
    int left_h = get_height(node->left);
    int right_h = get_height(node->right);
    if (left_h >= right_h) {
        printf("Went left\n");
        binary_node * found_node = get_biggest_child(&node->left, node);
        node->val = found_node->val;
        found_node->parent->left = found_node->left;
        found_node->parent->right = NULL;
    } else {
        printf("Went right\n");
        binary_node * found_node = get_smallest_child(&node->right, node);
        node->val = found_node->val;
        found_node->parent->right = found_node->right;
        found_node->parent->left = NULL;
    }
    return true;
}

// I was so close to getting it all right but alas things went awry
// So now I dont know how to delete a leaf node after I find it 
// But this is only if I want to find the last reference if I am ok with the first reference
// Then this part is fine
// Next thing is figuring out how deleting root node would work

// Actually figured out quite a bit before bed and now everything works except root deletion
// I mean everything works that I know of I did test every node but there might have been some edge cases missed

// Listen I dont even know anymore but when I try to delete 12 it breaks with a duplicate 9
int main (int argc, char **argv) {
    // int arr[7] = {7, 23, 5, 4, 3, 18, 21};
    // int arr2[7] = {7, 23, 5, 4, 3, 18, 21};
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    binary_node *tree1 = create_binary_tree(arr, length);
    // binary_node *tree2 = create_binary_tree(arr2, length);
    // bool is_equal = compare(tree1, tree2);
    // bool is_equal = compare_breath_first(tree1, tree2);
    // insert(&tree1, 49);
    // pre_order_print(tree1, 8);
    // bfs_print_sequencial(tree1);
    binary_tree_print(tree1);
    insert(tree1, 27);
    insert(tree1, 6);
    // insert(tree1, 9);
    insert(tree1, 8);
    // insert(tree1, 7);
    // insert(tree1, 10);
    // binary_tree_print(tree1);
    // printf("With zig\n");
    // binary_node * found_node = get_node(tree1, 4);
    // add_heights(tree1, 0);
    // bfs_print_sequencial(tree1);
    binary_tree_print(tree1);
    delete(tree1, 7);
    // bfs_print_sequencial(tree1);
    binary_tree_print(tree1);
    /* for ( int i = 0; i < length; i++) { */
    /*     printf("%d\n", traversal[i]);  */
    /* } */}
