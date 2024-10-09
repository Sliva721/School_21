#ifndef MYSTACK_H_
#define MYSTACK_H_

typedef struct stack {
    char c;
    struct stack *next;
} stack;
stack *push(stack *, char);
char delete (stack **);
int priority(char);
void parser(stack *operations, char *input_str, char *output_str);
int parser_inp(const char *output_string);
#endif  // MYSTACK_H_
