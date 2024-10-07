#include "mystack.h"

#include <stdio.h>
#include <stdlib.h>

char delete (stack **HEAD) {  //удаление узла хед(2 выхода)
    stack *upper;
    char symbol;
    if (*HEAD == NULL) return '\0';
    upper = *HEAD;
    symbol = upper->c;
    *HEAD = upper->next;
    free(upper);
    return symbol;
}

stack *push(stack *HEAD, char symbol) {  //пуш над хедом
    stack *upper;
    if ((upper = malloc(sizeof(stack))) == NULL) {
        puts("no memory");
        exit(-1);
    }
    upper->c = symbol;
    upper->next = HEAD;
    return upper;
}

int priority(char symbol) {
    int flag = 0;  //приоритеты
    switch (symbol) {
        case 'c':  // cos
        case 's':  // sin
        case 't':  // tg
        case 'g':  // ctg
        case 'q':  // sqrt
        case 'l':  // ln
            flag = 4;
            break;
        case '*':
        case '/':
            flag = 3;
            break;

        case '-':
        case '+':
            flag = 2;
            break;

        case '(':
            flag = 1;
            break;
    }
    return flag;
}
