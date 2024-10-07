// реализует парсер, который преобразует математические выражения из инфиксной нотации 
// (стандартная форма записи с использованием скобок и операторов) в польскую (обратную) нотацию. 
// Польская нотация позволяет избежать использования скобок и обеспечивает простоту вычисления выражений.
// В коде используются структуры данных, такие как стек, для хранения операторов и функции для работы с ними (например, `push`, `delete`, `priority`) — 
// они не представлены в данном коде, но предположительно объявлены в файле `mystack.h`.

// Краткий анализ:
// - Данный код обрабатывает входную строку символ за символом.
// - Если встречается оператор или функция, он добавляет их в стек в зависимости от их приоритета.
// - Если находят закрывающую скобку, извлекаются все операторы до открывающей скобки.
// - В конце все оставшиеся операторы извлекаются в выходную строку.


#include <stdio.h>
#include "mystack.h" // Подключаем заголовочный файл, который содержит определения для работы со стеком

// Функция для разбора выражений в польской нотации
void parsing_in_polish_notation(struct st *operations, char *input_str, char *output_str) {
    int point; // Указатель на позицию в выходной строке
    point = 0; // Инициализируем позицию на 0

    // Проходим по всем символам входной строки до конца (до символа '\0')
    for (int i = 0; input_str[i] != '\0'; i++) {
        // Если встречаем закрывающую скобку
        if (input_str[i] == ')') {
            // Извлекаем все операторы из стека до тех пор, пока не найдем открывающую скобку
            while ((operations->c) != '(') 
                output_str[point++] = delete (&operations);
            delete (&operations); // Удаляем открывающую скобку из стека
        }
        
        // Обрабатываем числа и переменную 'x'
        if ((input_str[i] >= '0' && input_str[i] <= '9') || input_str[i] == 'x') {
            output_str[point++] = input_str[i]; // Добавляем число или 'x' в выходную строку
        }

        // Обработка тригонометрических функций и корней
        if (input_str[i] == 's' && input_str[i + 1] == 'i' && input_str[i + 2] == 'n') {
            // Обработка функции синуса
            if (operations == NULL) {
                operations = push(operations, 's'); // Если стек пуст, добавляем 's'
            } else if (priority(operations->c) < priority('s')) {
                operations = push(operations, 's'); // Добавляем 's', если его приоритет выше
            } else {
                // Извлекаем операции с более высоким или равным приоритетом и добавляем их в выходную строку
                while ((operations != NULL) && (priority(operations->c) >= priority('s')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 's'); // Добавляем 's'
            }
            i += 3; // Пропускаем обработанные символы
        }

        // Другие функции: cos, tg, ctg, sqrt, ln
        if (input_str[i] == 'c' && input_str[i + 1] == 'o' && input_str[i + 2] == 's') {
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
        if (input_str[i] == 'c' && input_str[i + 1] == 't' && input_str[i + 2] == 'g') {
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
        if (input_str[i] == 's' && input_str[i + 1] == 'q' && input_str[i + 2] == 'r' && input_str[i + 3] == 't') {
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
        if (input_str[i] == 'l' && input_str[i + 1] == 'n') {
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

        // Если мы встречаем открывающую скобку, мы добавляем её в стек
        if (input_str[i] == '(') 
            operations = push(operations, '(');

        // Обрабатываем арифметические операторы
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

    // После обработки всей строки, извлекаем все оставшиеся операторы из стека
    while (operations != NULL) 
        output_str[point++] = delete (&operations);
    
    output_str[point] = '\0'; // Завершаем выходную строку символом конца строки
}