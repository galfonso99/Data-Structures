#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stb_ds.h"
// #include "binary_search_tree.h"

typedef struct node {
    int value;

} graph_node;

typedef struct {
    int vertices_nr;
    int ** matrix;
} graph_matrix;

void create_matrix (graph_matrix * matrix) {
    matrix->vertices_nr = 5;
    matrix->matrix = malloc(sizeof(int) * matrix->vertices_nr * matrix->vertices_nr);
    int array[25] = {0,1,4,5,0,1,0,0,0,0,0,0,0,2,0,0,0,0,0,5,0,0,0,0,0};
    // memcpy(matrix->matrix, array, sizeof(int) * 2);
    // printf("%p\n", **matrix->matrix);
    for (int i = 0; i < matrix->vertices_nr; i++) {
        matrix->matrix[i] = malloc(sizeof(int) * matrix->vertices_nr);
        for (int j = 0; j < matrix->vertices_nr; j++) {
            matrix->matrix[i][j] = array[matrix->vertices_nr * i+j];
            // printf("%d\n", array[matrix->vertices_nr * i+j]);
            // printf("At %d, and at %d, %d\n", i, j, matrix->matrix[i][j]);
        }
    }
    // matrix->matrix[0][0] = 5;
    // matrix->matrix[0][1] = 7;
}

void print_matrix (graph_matrix * matrix) {
    for (int i = 0;i < matrix->vertices_nr;i++) {   
        for (int j = 0; j < matrix->vertices_nr; j++) {
            printf("%d\n", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}

void fill_prev (int * prev, int length) {
    for (int i = 0; i < length; i++) {
        prev[i] = -1;
    }
}

void reverse (int * path, int length) {
    for (int i = 0; i < length / 2; i++) {
        int tmp = path[i];
        path[i] = path[length - 1 - i];
        path[length - 1 - i] = tmp;
    }
}

int * bst_find_graph (graph_matrix * matrix, int source, int needle) {
    int * queue = NULL;
    int * path = NULL; 

    if (source == needle) {
        arrput(path, source);
        return path;
    }

    bool * seen = malloc(sizeof(bool) * matrix->vertices_nr);
    int prev_length = matrix->vertices_nr <= needle ? needle + 1 : matrix->vertices_nr;
    int * prev = malloc(sizeof(int) * prev_length);
    fill_prev(prev, prev_length);
    int idx = source;

    arrput(queue, source);

    while (arrlen(queue) != 0) {
        idx = queue[0];
        arrdel(queue, 0);
        if (idx == needle) break;
        seen[idx] = true;
        for (int i = 0; i < matrix->vertices_nr; i++) {
            int weight = matrix->matrix[idx][i];
            if (weight > 0 && !seen[i]) {
                arrput(queue, i);
                prev[i] = idx;
            }
        }
    }
    idx = needle;
    while (prev[idx] != -1) {
        arrput(path, idx);
        idx = prev[idx];
    }
    if (arrlen(path) == 0) return NULL;
    arrput(path, idx);
    reverse(path, arrlen(path));
    return path;

}

// Create a matrix to represent a graph
// Figure out a way to perform bfs on such a graph using adj matrix
int main (int argc, char **argv) {
    // int arr[13] = {12, 54, 15, 61, 77, 33, 34, 78, 80, 91, 100, 55, 77};
    // int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    // int length = sizeof(arr) / sizeof(int);
    graph_matrix * matrix = malloc(sizeof(graph_matrix));
    create_matrix(matrix);
    // print_matrix(matrix);
    int * path = bst_find_graph(matrix, 2, 4);
    // if (!path) {
    //     printf("Fuck\n");
    // }
    for (int i = 0; i < arrlen(path); i++) {
        printf("%d, ", path[i]);
    }
}

