#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define CELL 'O'       // Символ для представления живой клетки
#define DEAD_CELL '.'  // Символ для представления мертвой клетки
#define PRESS_BUTTON_UP_SPEED 'a'    //Увеличить скорость
#define PRESS_BUTTON_DOWN_SPEED 'z'  //Уменьшить скорость

// Объявление функций
int **create_playing_board(int col, int row);
void filling_playing_board(int **data);
void show_playing_board(int **data, int col, int row);
int correctX(int x);
int correctY(int y);
int update_playing_board(int **data);
void copy_matrix(int **data, int **new_data);
int get_count_of_neighbors(int **data, int x, int y);
void dead_or_life(int **data, int x, int y, int neighbors);
int kbhit();   // Функция для проверки нажатия клавиши
char getch();  // Функция для считывания символа
int compare_matrix(int **data, int **new_data);

int main() {
    int col = WIDTH;
    int row = HEIGHT;
    int count = 0;
    double time = 2.5;
    int **data = NULL;
    data = create_playing_board(col, row);
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    filling_playing_board(data);         // Заполнение поля
    show_playing_board(data, col, row);  // Отображение начального состояния
    while (update_playing_board(data)) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'q') {
                break;  // Завершение игры при нажатии 'q'
            } else if (ch == PRESS_BUTTON_UP_SPEED) {
                time = (time > 0.1) ? time - 0.1 : time;  // Ускорение
            } else if (ch == PRESS_BUTTON_DOWN_SPEED) {
                time += 0.1;  // Замедление
            }
        }
        printf("Cell generation = %d\n", count++);  // Вывод текущего количества обновлений
        sleep(time);  // Задержка для управления обновлениями
        show_playing_board(data, col, row);  // Отрисовка обновленного поля
        printf("Speed = %lf\n", time);
    }
    free(data);
    data = NULL;
    return 0;
}

// Создание матрицы: динамическое выделение памяти для хранения игрового поля
int **create_playing_board(int col, int row) {
    int **data = NULL;
    data = malloc(row * sizeof(int *) + row * col * sizeof(int));  // Выделяем память
    if (data == NULL) return NULL;  // Проверка успешности выделения памяти

    int *ptr = (int *)(data + row);  // Указатель на старт матрицы
    for (int i = 0; i < row; i++) {
        data[i] = ptr + col * i;  // Запись адресов строк
    }
    return data;  // Возвращаем указатель на игровое поле
}

// Заполнение игровой доски из входных данных
void filling_playing_board(int **data) {
    char line[WIDTH + 1] = {'0'};
    int row_i = 0;

    // Считываем данные для заполнения доски
    while (row_i < HEIGHT && fgets(line, sizeof(line), stdin) != NULL) {
        for (int col_j = 0; col_j < WIDTH; col_j++) {
            if (line[col_j] == 'O') {
                data[row_i][col_j] = line[col_j];  // Заполнение живыми клетками
            } else {
                data[row_i][col_j] = DEAD_CELL;  // Установить мертвую клетку
            }
        }
        row_i++;
    }
    FILE *fp = NULL;
    fp = freopen("/dev/tty", "r", stdin);
    if (fp == NULL) {
        exit(1);
    }
}

// Отображение игровой доски
void show_playing_board(int **data, int col, int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (data[i][j] == 'O') {
                printf("O");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

// Обновление состояния игровой доски на основе правил
int update_playing_board(int **data) {
    int flag = 0;
    int **new_data = NULL;
    new_data = create_playing_board(WIDTH, HEIGHT);  // Создаем новую
    if (new_data == NULL) return flag;  // Проверка успешности выделения памяти

    copy_matrix(data, new_data);  // Копируем текущее состояние

    // Применяем правила игры "Жизнь"
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            int neighbors = 0;
            neighbors = get_count_of_neighbors(new_data, col, row);  // Считаем соседей
            if (neighbors > 0) {
                if (new_data[row][col] == CELL) {
                    dead_or_life(data, col, row, neighbors);  // Проверяем, должна ли клетка умереть
                }
                if (neighbors == 3) {
                    data[row][col] = CELL;  // Воскрешаем мертвую клетку
                }
            }
        }
    }
    flag = compare_matrix(data, new_data);
    free(new_data);  // Освобождаем память для новой матрицы
    return flag;
}

// Копирование содержимого одной матрицы в другую
void copy_matrix(int **data, int **new_data) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            new_data[row][col] = data[row][col];  // Копируем значение
        }
    }
}

// Сравнение содержимого одной матрицы в другую
int compare_matrix(int **data, int **new_data) {
    int comp_mat;
    comp_mat = 0;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (new_data[row][col] != data[row][col]) {
                comp_mat = 1;
            }
        }
    }
    return comp_mat;
}

// Подсчет количества живых соседей
int get_count_of_neighbors(int **data, int x, int y) {
    int count = 0;
    // Проверяем все 8 соседей
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Пропускаем саму клетку
            if (data[correctY(y + i)][correctX(x + j)] == CELL) {
                count += 1;  // Увеличиваем счетчик, если сосед живая клетка
            }
        }
    }
    return count;  // Возвращаем количество живых соседей
}

// Определение, остается ли клетка живой или умирает
void dead_or_life(int **data, int x, int y, int neighbors) {
    if (neighbors < 2 || neighbors > 3) {
        data[y][x] = DEAD_CELL;  // Клетка умирает
    }
}

// Коррекция координат для замкнутого поля
int correctX(int x) {
    return (x + WIDTH) % WIDTH;  // Циклическая корректировка координаты x
}

int correctY(int y) {
    return (y + HEIGHT) % HEIGHT;  // Циклическая корректировка координаты y
}

// Функция для проверки нажатия клавиши
int kbhit() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;  // Нажатие клавиши зафиксировано
    }
    return 0;  // Нет нажатий клавиш
}

// Функция для считывания символа
char getch() {
    char buf = 0;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    read(STDIN_FILENO, &buf, 1);  // Чтение одного символа

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return (buf);
}