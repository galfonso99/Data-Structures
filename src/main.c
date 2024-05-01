#include "graph.h"
#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include "binary_search_tree.h"

#define int_max 2147483647

void fill_with_bool (bool * arr, bool boolean, int count) {
    for (int i = 0; i < count; i++) {
        arr[i] = boolean;
    }
}
void initialize_with_infinity (int * arr, int count) {
    for (int i = 0; i < count; i++) {
        arr[i] = int_max;
    }
}

adjacency_list create_adjacency_list2 (int length) {
    adjacency_list adj_list = (graph_edge **) malloc(sizeof(int) * length * length);
    int edges_nr[] = {2,3,3,3,3,3,2};
    graph_edge list_of_edges[] = {
                                {.to =  1, .weight = 3},
                                {.to =  2, .weight = 1},
                                {.to =  0, .weight = 3},
                                {.to =  2, .weight = 4},
                                {.to =  4, .weight = 1},
                                {.to =  1, .weight = 4},
                                {.to =  3, .weight = 7},
                                {.to =  0, .weight = 1},
                                {.to =  2, .weight = 7},
                                {.to =  4, .weight = 5},
                                {.to =  6, .weight = 1},
                                {.to =  1, .weight = 1},
                                {.to =  3, .weight = 5},
                                {.to =  5, .weight = 2},
                                {.to =  6, .weight = 1},
                                {.to =  4, .weight = 2},
                                {.to =  2, .weight = 18},
                                {.to =  3, .weight = 1},
                                {.to =  5, .weight = 1},
                                };
    int count = 0;
    for (int i = 0; i < length; i++) {
        adj_list[i] = (graph_edge *) malloc(sizeof(int) * length);
        int length = edges_nr[i];
        adj_list[i] = NULL;
        for (int j = 0; j < length; j++) {
            arrput(adj_list[i], list_of_edges[count]);
            count++;
        }
    }
    return adj_list;
}

void initialize_2d_array (int ** arr, int y, int x, int val) {
    for (int i = 0; i < y; i++) {
        arr[i] = malloc(sizeof(int) * 5);
        for (int j = 0; j < x; j ++) {
            arr[i][j] = val;
        }
    }
}

void initialize_paths (int ** arr, int length, int val) {
    for (int i = 0; i < length; i++) {
        arrput(arr[i], val);
    }
}

// For this algorithm which I naively created for shortest path I simply visit each node and for every node
// I visit all the adjacent nodes, then if the distance of curr path that arrived at the specific adjacent node
// is shorter than the previous shortest distance mark it as the new shortest distance and make the current path be 
// the new shortest path of that adjacent node
int * dijkstra_no_help (int source, int sink, adjacency_list graph, int vertex_count ) {
    bool processed_nodes[vertex_count];
    fill_with_bool(processed_nodes, false, vertex_count);
    int * distances = malloc(sizeof(int) * vertex_count);
    initialize_with_infinity(distances, vertex_count);
    int ** paths = malloc(sizeof(int) * vertex_count * 5);
    initialize_paths(paths,vertex_count, source);
    int * queue = NULL;
    int curr_node = source;
    distances[curr_node] = 0;
    while (curr_node != sink) {
        for (int i = 0; i < vertex_count; i++) {
            if (graph[curr_node][i].weight == 0) {
                break;
            }
            int curr_path_dist = distances[curr_node];
            int adjacent_node = graph[curr_node][i].to;
            int adjacent_dist = graph[curr_node][i].weight;
            if (curr_path_dist + adjacent_dist < distances[adjacent_node]) {
                distances[adjacent_node] = curr_path_dist + adjacent_dist;
                // Copy the path of curr into the path of adjacent then delete any overflowing leftover,
                // then append the adjacent_node into the array
                memcpy(paths[adjacent_node], paths[curr_node], sizeof(int) * arrlen(paths[curr_node]));
                arrdeln(paths[adjacent_node], arrlen(paths[curr_node]), arrlen(paths[adjacent_node]) - 
                                                                                arrlen(paths[curr_node]));
                arrput(paths[adjacent_node], adjacent_node);
                if (!processed_nodes[adjacent_node]) {
                    arrput(queue, adjacent_node);
                }
            }
        }
        processed_nodes[curr_node] = true;
        curr_node = queue[0];
        arrdel(queue, 0);
    }
    return paths[sink];
}
void fill_with_int(int * arr, int val, int count) {
    for (int i = 0; i < count; i++) {
        arr[i] = val;
    }
}

bool has_unvisited (bool * seen, int length) {
    for (int i = 0; i < length; i++) {
        if (!seen[i]) {
            return true;
        }
    }
    return false;
}

int get_lowest_unvisited (int * dists, bool * seen, int length) {
    int lowest_node = 0;
    int lowest_dist = int_max;
    for (int i = 0; i < length; i++) {
        if (!seen[i] && dists[i] < lowest_dist) {
            lowest_dist = dists[i];
            lowest_node = i;
        }
    }
    return lowest_node;
}

// This algorithm was made after the "no help" algorithm and uses external pseudocode from Primeagen as help
int * dijkstra_with_pseudocode (int source, int sink, adjacency_list graph, int vertex_count) {
    int prev[vertex_count];
    fill_with_int(prev, -1, vertex_count);
    bool seen[vertex_count];
    fill_with_bool (seen, false, vertex_count);
    int dists[vertex_count];
    fill_with_int(dists, int_max, vertex_count);
    dists[source] = 0;

    while (has_unvisited(seen, vertex_count)) {
        int low = get_lowest_unvisited(dists, seen, vertex_count);
        seen[low] = true;
        for (int i = 0; i < arrlen(graph[low]); i++) {
            int edge = graph[low][i].to;
            int weight = graph[low][i].weight;
            if (seen[edge]) {
                continue;
            }
            int dist = dists[low] + weight;
            if (dist < dists[edge]) {
                dists[edge] = dist;
                prev[edge] = low;
            }
        }
    }
    int * path = NULL;
    int curr = sink;
    while (prev[curr] != -1) {
        arrput(path, curr);
        curr = prev[curr];
    }
    if (arrlen(path) == 0) return NULL;
    arrput(path, curr);
    reverse(path, arrlen(path));
    return path;
}

// Implement dijkstras using a priority queue and implement heap up down and heap update which uses 
// a hashmap to keep the position of the nodes
//
// Implement a priority queue that takes graph edge as elements
// Implement heapify up for such prio queue
// Implement heapify down for such prio queue
// Implement heap update for such prio queue
// Implement the hashmap that will go alongside it 
// Write dijk using this prio queue
int * dijkstra (int source, int sink, adjacency_list graph, int vertex_count) {

}

int main (int argc, char **argv) {
    // int length = sizeof(arr) / sizeof(int);
    int graph_node_count = 5;
    adjacency_list graph = create_adjacency_list(graph_node_count);
    int graph2_node_count = 7;
    adjacency_list graph2 = create_adjacency_list2(graph2_node_count);
    // int * path = dijkstra_no_help(0, 4, graph, graph_node_count);
    // int * path = dijkstra_with_pseudocode(0, 4, graph, graph_node_count);
    int * path = dijkstra_with_pseudocode(0, 6, graph2, graph2_node_count);
    // printf("%d\n", paths[2]);
    for (int i = 0; i < arrlen(path); i++) {
        printf("%d\n", path[i]);
    }
}

