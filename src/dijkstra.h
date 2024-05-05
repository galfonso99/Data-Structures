#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define STB_DS_IMPLEMENTATION
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "map.h"

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

adjacency_list create_adjacency_list3 (int length) {
    adjacency_list adj_list = (graph_edge **) malloc(sizeof(graph_edge) * length * length);
    int edges_nr[] = {2,1,2,1,0};
    graph_edge list_of_edges[] = {
                                {.to =  1, .weight = 7},
                                {.to =  2, .weight = 2},
                                {.to =  4, .weight = 2},
                                {.to =  1, .weight = 3},
                                {.to =  3, .weight = 4},
                                {.to =  4, .weight = 3},
                            };
    int count = 0;
    for (int i = 0; i < length; i++) {
        adj_list[i] = (graph_edge *) malloc(sizeof(graph_edge) * length);
        int length = edges_nr[i];
        adj_list[i] = NULL;
        for (int j = 0; j < length; j++) {
            /* adj_list[i][j] = list_of_edges[count]; */
            arrput(adj_list[i], list_of_edges[count]);
            count++;
        }
    }
    return adj_list;
}

void initialize_2d_array (int ** arr, int y, int x, int val) {
    for (int i = 0; i < y; i++) {
        arr[i] = (int*) malloc(sizeof(int) * 5);
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
    int * distances = (int*) malloc(sizeof(int) * vertex_count);
    initialize_with_infinity(distances, vertex_count);
    int ** paths = (int**) malloc(sizeof(int) * vertex_count * 5);
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

int parent(int child_idx) {
    return (child_idx - 1) / 2;
}

int left_child (int parent_idx) {
    return (parent_idx * 2) + 1;
}

int right_child(int parent_idx) {
    return (parent_idx * 2) + 2;
}

typedef struct {
    int length;
    graph_edge ** data;
    hashmap * map;
} priority_queue;

priority_queue * create_priority_queue (int vertex_count) {
    priority_queue * pq = (priority_queue*) malloc(sizeof(priority_queue));
    pq->length = 0;
    pq->data = NULL;
    pq->map = hashmap_create();
    return pq;
}

int hm_get(hashmap * map, void * key) {
    uintptr_t out;
    hashmap_get(map, key, sizeof(int), &out);
    return (int) out;
}

void hm_set(hashmap * map, void * key, int value) {
    hashmap_set(map, key, sizeof(int), value);
}

void print_hashmap (priority_queue * pq) {
    for (int i = 0; i < pq->length; i++) {
        printf("HashMap Label %d: Index %d\n", pq->data[i]->to, hm_get(pq->map, &pq->data[i]->to));
    }
}
void print_entry(void* key, size_t ksize, uintptr_t value, void* usr) {
	printf("Entry \"%d\": %i\n", *(int *) key, (int) value);
}

void swap (priority_queue * pq, int child_idx, int parent_idx) {
    graph_edge ** arr = pq->data;
    graph_edge * edge_1 = arr[child_idx];
    graph_edge * edge_2 = arr[parent_idx];
    arr[child_idx] = edge_2;
    arr[parent_idx] = edge_1;
    hm_set(pq->map, &edge_1->to, parent_idx);
    hm_set(pq->map, &edge_2->to, child_idx);
    print_hashmap(pq);
}

bool heapify_up (priority_queue * pq, int idx) {
    graph_edge ** arr = pq->data;
    graph_edge * edge = arr[idx];
    int parent_idx = parent(idx);
    while (parent_idx >= 0 && arr[parent_idx]->weight > edge->weight) {
        swap(pq, idx, parent_idx);
        idx = parent_idx;
        parent_idx = parent(parent_idx);
    }
    return true;
}
bool heapify_down (priority_queue * pq, int idx) {
    graph_edge ** arr = pq->data;
    int l_idx = left_child(idx);
    int r_idx = right_child(idx);
    while (r_idx < pq->length && (arr[l_idx]->weight < arr[idx]->weight 
                                    || arr[r_idx]->weight < arr[idx]->weight)) {
        int min_idx = l_idx;
        if (arr[r_idx]->weight < arr[l_idx]->weight) {
            min_idx = r_idx;
        }
        swap(pq, idx, min_idx);
        idx = min_idx;
        l_idx = left_child(min_idx);
        r_idx = right_child(min_idx);
    }
    if (l_idx < pq->length && arr[l_idx]->weight < arr[idx]->weight) {
        swap(pq, idx, l_idx);
    }
    return true;
}

bool enqueue(priority_queue * pq, graph_edge * edge) {
    // Insert the value into the end of the queue
    // Heapify up from that spot until parent is smaller or there is no more parents
    arrput(pq->data, edge);
    pq->length++;
    hm_set(pq->map, &edge->to, pq->length - 1);
    bool success = heapify_up(pq, pq->length - 1);
    return success;
}

graph_edge * deque(priority_queue * pq) {
    if (pq->length == 0) return NULL;
    // Swap first value with last value
    swap(pq, pq->length-1, 0);
    graph_edge * edge = arrpop(pq->data);
    pq->length--;
    heapify_down(pq, 0);
    return edge;
}

bool update_queue (priority_queue * pq, graph_edge * edge) {
    hashmap * map = pq->map;
    // hashmap_get(map, &idx, sizeof(int), &out);
    int real_idx = hm_get(pq->map, &edge->to);
    pq->data[real_idx] = edge;
    int parent_idx = parent(real_idx);
    bool success;
    if (edge->weight < pq->data[parent_idx]->weight) {
        success = heapify_up(pq, real_idx);
    } else {
        success = heapify_down(pq, real_idx);
    }
    return success;
}

// Implement dijkstras using a priority queue and implement heap up down and heap update which uses 
// a hashmap to keep the position of the nodes
int * dijkstra (int source, int sink, adjacency_list graph, int vertex_count) {
    int * path = NULL;

    // If starting point is same as ending point, we are already there
    if (source == sink) {
        arrput(path, source);
        return path;
    }
    priority_queue * pq = create_priority_queue(vertex_count);
    int prev[vertex_count];
    fill_with_int(prev, -1, vertex_count);
    int dists[vertex_count];
    fill_with_int(dists, int_max, vertex_count);
    dists[source] = 0;
    graph_edge source_edge = {.to = source, .weight = 0};
    enqueue(pq, &source_edge);
    while (pq->length > 0) {
        graph_edge * low_edge = deque(pq);
        int low = low_edge->to;
        for (int i = 0; i < arrlen(graph[low]); i++) {
            int edge = graph[low][i].to;
            int weight = graph[low][i].weight;
            int dist = dists[low] + weight;
            if (dist < dists[edge]) {
                int prev_dist = dists[edge];
                dists[edge] = dist;
                prev[edge] = low;
                enqueue(pq, &graph[low][i]);
            }
        }
    }
    // Retrace steps using prev array
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

void dijkstra_driver () {
    int graph_node_count = 5;
    adjacency_list graph = create_adjacency_list(graph_node_count);
    int graph2_node_count = 7;
    adjacency_list graph2 = create_adjacency_list2(graph2_node_count);
    adjacency_list graph3 = create_adjacency_list3(graph_node_count);

    /* int * path = dijkstra_no_help(0, 4, graph, graph_node_count); */
    /* int * path = dijkstra(0, 6, graph2, graph2_node_count); */
    /* int * path = dijkstra_with_pseudocode(0, 6, graph2, graph2_node_count); */
    /* int * path = dijkstra(0, 4, graph3, graph_node_count); */
    int * path = dijkstra(0, 6, graph2, graph2_node_count);

    if (!path) {
        printf("Path is NULL\n");
    }
    for (int i = 0; i < arrlen(path); i++) {
        printf("%d\n", path[i]);
    }
    /*
       The following code is testing the hashmap and the update_queue function which uses the hashmap
    */

   // priority_queue * pq = create_priority_queue(5);
   // graph_edge edge = {.to = 0, .weight = 6};
   // enqueue(pq, &edge);
   // graph_edge edge2 = {.to = 1, .weight = 7};
   // enqueue(pq, &edge2);
   // graph_edge edge3 = {.to = 2, .weight = 4};
   // enqueue(pq, &edge3);
   // graph_edge edge4 = {.to = 3, .weight = 9};
   // enqueue(pq, &edge4);
   // for (int i = 0; i < pq->length; i++) {
   //     printf("Edge label / weight pair %d: %d\n", pq->data[i]->to, pq->data[i]->weight);
   // }
   // graph_edge new_edge = {.to = 3, .weight = 5};
   // update_queue(pq, &new_edge);
   // for (int i = 0; i < pq->length; i++) {
   //     printf("Edge label / weight pair %d: %d\n", pq->data[i]->to, pq->data[i]->weight);
   // }
   // hashmap_iterate(pq->map, print_entry, NULL);
}


#endif
