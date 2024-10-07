#include "draw.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculation.h"

char **calloc_matrix(int height, int width) {  //инициализация матрицы
    char **matrix;
    matrix = (char **)calloc(height + 1, sizeof(char *));
    for (int y = 0; y < height; y++) matrix[y] = (char *)calloc(width + 1, sizeof(char));
    return matrix;
}

void init_graph(char **graph, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            graph[y][x] = POINT;  //граф в точках(дро.Н)
        }
    }
    for (int y = 0; y < HEIGHT; y++) {
        graph[y][width + 1] = '\0';
    }
}

void draw_graph(char **graph, int height) {
    printf("\e[1;1H\e[2J");
    for (int y = 0; y < height - 1; y++) {
        printf("%s\n", graph[y]);
    }
}

void free_matrix(char **graph, int height) {
    for (int y = 0; y < height; y++) free(graph[y]);
    free(graph);
}
