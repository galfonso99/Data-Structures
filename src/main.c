#define STB_DS_IMPLEMENTATION

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stb_ds.h"

const int DIRS[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

typedef struct Point {
    int x;
    int y;
    int length;
} Point;

typedef struct {
    char* ch;
    struct Point* pos;
} Spot;

typedef struct {
    int length;
    int width;
    char** maze;
} Layout;

bool walk (Layout *maze, char wall, Point* end_point, bool **seen, Point **path, Point curr) {

    if (curr.x < 0 || curr.x >= maze->width 
             || curr.y < 0 || curr.y >= maze->length) {
        return false;
    } else if (maze->maze[curr.y][curr.x] == wall) {
        return false;
    } else if (seen[curr.y][curr.x]) {
        return false;
    } else if (curr.x == end_point->x && curr.y == end_point->y) {
        arrput(*path, curr);
        return true;
    }

    // Pre recursion
    seen[curr.y][curr.x] = true;
    arrput(*path, curr);

    // Recurse
    for (int i = 0; i < 4; i++) {
        int y = DIRS[i][0], x = DIRS[i][1]; 

        if (walk(maze, wall, end_point, seen, path, (Point) {
         .x = curr.x + x,
         .y = curr.y + y,
         .length = curr.length + 1
        })) {
            return true;
        };
    }
    // Post recursion
    arrpop(*path);
    return false;
}

Point * solve (Layout *maze, char wall, Point *start, Point *end) {
    int length = maze->length;
    int width = maze->width;
    bool **seen = calloc(length, sizeof *seen);
    for (int i = 0; i < length; i++) {
        seen[i] = calloc(width, sizeof *(seen[i]));
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            seen[i][j] = false;
        }
    }
    Point *path = NULL;
    walk(maze, wall, end, seen, &path, *start);
    return path;
}

int main(int argc, char **argv) {
    char wall = 'x';
    int length = 6;
    int width = 12;
    char *maze[] = {"xxxxxxxxxx x",
                    "x        x x",
                    "x        x x",
                    "x xxxxxxxx x",
                    "x          x",
                    "x xxxxxxxxxx"};
    Point start = {.x = 10, .y = 0};
    Point end = {.x = 1, .y = 5};
    Layout layout = {.length = length, .width = width, .maze = (char**) maze};
    Point *path = solve(&layout, wall, &start, &end);
    // solve(&layout, wall, &start, &end);
    for (int i = 0; i < arrlen(path); i++) {
        printf("{%d, %d}\n", path[i].x, path[i].y);
    }
}
