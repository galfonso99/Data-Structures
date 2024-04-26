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

typedef struct {
    int to;
    int weight;
} graph_edge;

typedef graph_edge** adjacency_list;

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

adjacency_list create_adjacency_list () {
    int nr_of_vertices = 5;
    adjacency_list adj_list = malloc(sizeof(int) * nr_of_vertices * nr_of_vertices);
    int edges_nr[] = {3,1,1,1,0};
    graph_edge list_of_edges[] = {
                                {.to =  1, .weight = 1},
                                {.to =  2, .weight = 4},
                                {.to =  3, .weight = 5},
                                {.to =  0, .weight = 1},
                                {.to =  3, .weight = 2},
                                {.to =  4, .weight = 5},
                                };
    int count = 0;
    for (int i = 0; i < nr_of_vertices; i++) {
        adj_list[i] = malloc(sizeof(int) * nr_of_vertices);
        int length = edges_nr[i];
        for (int j = 0; j < length; j++) {
            adj_list[i][j] = list_of_edges[count];
            count++;
        }
    }
    return adj_list;
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

bool dfs_walk (adjacency_list graph, int curr, int needle, bool * seen, int * path) {

}

int * find_dfs_adjacency_list (adjacency_list graph, int source, int needle) {

}

int main (int argc, char **argv) {
    // int length = sizeof(arr) / sizeof(int);
    adjacency_list graph = create_adjacency_list();
    int * path = find_dfs_adjacency_list(graph, 2, 4);
    for (int i = 0; i < arrlen(path); i++) {
        printf("%d, ", path[i]);
    }
}

