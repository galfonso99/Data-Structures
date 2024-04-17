#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include "binary_tree.h"
// #include "binary_search_tree.h"

 typedef struct trie {
    char ch;
    struct trie * children[26];
    bool is_word;
 } Trie;

int index_of (char ch) {
    int ascii = (int) ch;
    int index = ascii - ((int) 'a');
    return index;
}

Trie * create_trie (char ch) {
    Trie * trie = malloc(sizeof(Trie));
    trie->ch = ch;
    trie->is_word = false;
    return trie;
}

void print_arr (Trie * arr[26]) {
    for (int i = 0; i < 26; i++) {
        if (arr[i]) {
            printf("%c\t", arr[i]->ch);
        }
        else {
            printf("NULL\t");
        }
    }
}

bool insert (Trie * trie, char * word, int word_length) {
    for (int i = 0; i < word_length; i++) {
        char curr_ch = word[i];
        int index = index_of(curr_ch);
        if (trie->children[index]) {
            continue;
        }
        trie->children[index] = create_trie(curr_ch);
        if (i == word_length - 1) {
            trie->is_word = true;
        }
        trie = trie->children[index];
    }
    return true;
}

bool delete_word (Trie * trie, Trie * parent, char * word) {
    if (parent && parent->is_word) {
        return true;
    }
    delete_word(trie->children[index_of(*word)], trie, word+1);
    // print_arr(trie->children);
    if (parent) parent->children[index_of(trie->ch)] = NULL;
    return true;
}

// Starting now with tries
int main (int argc, char **argv) {
    // int arr[13] = {12, 54, 15, 61, 77, 33, 34, 78, 80, 91, 100, 55, 77};
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    printf("%d\n", index_of('g'));
    Trie * trie = create_trie('_');
    insert(trie, "car", 3);
    Trie * copy = trie;
    // printf("%c, %c, %c", trie->children[index_of('c')]->ch, trie->children[index_of('a')]->ch, 
    //        trie->children[index_of('r')]->ch);
    // print_arr(trie->children);
    // printf("END\n");
    // trie = trie->children[index_of('c')];
    // print_arr(trie->children);
    // printf("END\n");
    // trie = trie->children[index_of('a')];
    // print_arr(trie->children);
    // printf("END\n");
    // trie = trie->children[index_of('r')];
    // print_arr(trie->children);
    // printf("END\n");

    delete_word(copy, NULL, "car");
    print_arr(copy->children);
    printf("END\n");
    // binary_search_tree_driver();
}

// for (int i = 0; i < length; i++) {
//     printf("%d\n", arr[i]);
// }
