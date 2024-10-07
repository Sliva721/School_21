#include <stdio.h>

#include "mystack.h"
int parser_inp(const char *output_string) {
    int flag = 0;
    int flagx = 0;
    for (int i = 0; i < 80; i++) {
        if (output_string[i] == 's') {
            if (output_string[i + 1] != 'i' && output_string[i + 2] != 'n') {
                if (output_string[i + 2] == '\0')
                    flag = 1;
                else if (output_string[i + 1] != 'q' && output_string[i + 2] != 'r' &&
                         output_string[i + 3] != 't') {
                    flag = 1;
                } else {
                    i += 3;
                    continue;
                }
            } else {
                i += 2;
                continue;
            }
        }
        if (output_string[i] == 'c') {
            if (output_string[i + 1] != 'o' && output_string[i + 2] != 's') {
                if (output_string[i + 1] != 't' && output_string[i + 2] != 'g')
                    flag = 1;
                else {
                    i += 2;
                    continue;
                }
            } else {
                i += 2;
                continue;
            }
        }
        if (output_string[i] == 't') {
            if (output_string[i + 1] != 'g')
                flag = 1;
            else {
                i += 1;
                continue;
            }
        }
        if (output_string[i] == 'l') {
            if (output_string[i + 1] != 'n')
                flag = 1;
            else {
                i += 1;
                continue;
            }
        }
        if (output_string[i] == 'x') {
            flagx = 1;
        }
        if (output_string[i] == '/') {
            if (output_string[i + 1] == '0') flag = 1;
        }
        if (flag == 1) break;
        if (output_string[i] == '\0') break;
    }
    if (flagx != 1) flag = 1;
    return flag;
}
void parser(stack *operations, char *input_str,  //в стэке ст операции идет передача посимвольно ввода
            char *output_str) {
    int point = 0;
    for (int i = 0; input_str[i] != '\0'; i++) {
        if (input_str[i] == ')') {
            while ((operations->c) != '(')
                output_str[point++] = delete (&operations);  //ищем скобки если их встречаем
            delete (&operations);
        }
        if ((input_str[i] >= '0' && input_str[i] <= '9') || input_str[i] == 'x')
            output_str[point++] = input_str[i];
        if (input_str[i] == 's' && input_str[i + 1] == 'i' &&  // sin
            input_str[i + 2] == 'n') {
            if (operations == NULL) {
                operations = push(operations, 's');
            } else if (priority(operations->c) < priority('s'))
                operations = push(operations, 's');
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority('s')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 's');
            }
            i += 3;
        }
        if (input_str[i] == 'c' && input_str[i + 1] == 'o' && input_str[i + 2] == 's') {  // cos
            if (operations == NULL)
                operations = push(operations, 'c');
            else if (priority(operations->c) < priority('c'))
                operations = push(operations, 'c');
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority('c')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'c');
            }
            i += 3;
        }
        if (input_str[i] == 't' && input_str[i + 1] == 'g') {
            if (operations == NULL)
                operations = push(operations, 't');
            else if (priority(operations->c) < priority('t'))
                operations = push(operations, 't');
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority('t')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 't');
            }
            i += 2;
        }
        if (input_str[i] == 'c' && input_str[i + 1] == 't' && input_str[i + 2] == 'g') {  //котангенс
            if (operations == NULL)
                operations = push(operations, 'g');
            else if (priority(operations->c) < priority('g'))
                operations = push(operations, 'g');
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority('g')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'g');
            }
            i += 3;
        }
        if (input_str[i] == 's' && input_str[i + 1] == 'q' && input_str[i + 2] == 'r' &&
            input_str[i + 3] == 't') {  //корень
            if (operations == NULL)
                operations = push(operations, 'q');
            else if (priority(operations->c) < priority('q'))
                operations = push(operations, 'q');
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority('q')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'q');
            }
            i += 4;
        }
        if (input_str[i] == 'l' && input_str[i + 1] == 'n') {  //логарифм
            if (operations == NULL)
                operations = push(operations, 'l');
            else if (priority(operations->c) < priority('l'))
                operations = push(operations, 'l');
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority('l')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'l');
            }
            i += 2;
        }
        if (input_str[i] == '(') operations = push(operations, '(');
        if (input_str[i] == '+' || input_str[i] == '-' || input_str[i] == '/' || input_str[i] == '*') {
            if (operations == NULL)
                operations = push(operations, input_str[i]);
            else if (priority(operations->c) < priority(input_str[i]))
                operations = push(operations, input_str[i]);
            else {
                while ((operations != NULL) && (priority(operations->c) >= priority(input_str[i])))
                    output_str[point++] = delete (&operations);
                operations = push(operations, input_str[i]);
            }
        }
    }

    while (operations != NULL) output_str[point++] = delete (&operations);
    output_str[point] = '\0';
}
