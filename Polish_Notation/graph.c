#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculation.h"
#include "draw.h"
#include "mystack.h"

int main() {
    char **graph = calloc_matrix(HEIGHT, WIDTH + 1);  //выделение памяти
    stack *operations = NULL;                         //создание стэка,
    char input_string[80];                            //ввод вывод
    printf("\033[0d\033[2J");
    fgets(input_string, 80, stdin);  //считывание ввода
    if (parser_inp(input_string) == 1)
        printf("n/a");
    else {
        char output_string[80];
        parser(operations, input_string,
               output_string);  //разбор ввода, перевод в мат выражение, оутпут-польская нотация
        printf("%s", output_string);

        printf("\033[0d\033[2J");
        init_graph(graph, HEIGHT, WIDTH);
        add_func_for_graph(graph, HEIGHT, WIDTH, output_string);

        draw_graph(graph, HEIGHT);
    }
    free_matrix(graph, HEIGHT);
    return 0;
}
