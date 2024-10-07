#ifndef GRAPH_H_
#define GRAPH_H_

#define WIDTH 81
#define HEIGHT 25
#define POINT '.'
#define STAR '*'

char **calloc_matrix(int height, int width);
void init_graph(char **graph, int height, int width);
void draw_graph(char **graph, int height);
void free_matrix(char **graph, int height);

#endif
