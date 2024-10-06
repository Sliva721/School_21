#include <stdio.h>

int leftScore = 0;   // счет очков первого игрока
int rightScore = 0;  // счет очков второго игрока
void game(int flag);
int print_pole(int max_pos_x, int max_pos_y, int leftRacketStart, int leftRacketEnd, int rightRacketStart,
               int rightRacketEnd, int pointX, int pointY, int leftRacketX, int rightRacketX);
int left_board_key(char key, int leftRacketStart, int leftRacketEnd, int min_pos_y, int max_pos_y);
int right_board_key(char key, int rightRacketStart, int rightRacketEnd, int min_pos_y, int max_pos_y);
int key_check(char key);

int main(void) {  // главная функция программы
    while (1) {
        int flag = 1;
        game(flag);
        if (leftScore == 21 || rightScore == 21) {
            break;
        }
    }
}

void game(int flag) {  // запуск игры срабатывает один раз при запуске
                       // размер поля
    int max_pos_y = 25;
    int max_pos_x = 80;
    int min_pos_y = 1;
    // начальные позиции ракеток
    // первая  ракетка
    int leftRacketStart = max_pos_y / 2;
    int leftRacketEnd = leftRacketStart + 2;
    int leftRacketX = 3;
    // вторая ракетка
    int rightRacketStart = (int)max_pos_y / 2;
    int rightRacketEnd = rightRacketStart + 2;
    int rightRacketX = 76;
    // позиция мячика
    int pointX = 39;
    int pointY = 12;
    int pointSpeedX = 1;
    int pointSpeedY = 1;
    while (flag) {  // бесконечный цикл который перерисовывает поле с обновлеными значаниями
        if (pointY == 23)  // направление мячика вниз
            pointSpeedY = -1;
        if (pointY == 1) pointSpeedY = 1;  // направление мячика вверх
        if (pointX == 79) {                // забитый мячик первым игроком
            leftScore++;
            //             printf("%d", leftScore);
            if (leftScore == 21) {  // проверка на победу
                printf("Win First player!");
                break;
            }
            flag = 0;
        }
        if (pointX == 0) {  // забитый мячик вторым игроком
            rightScore++;
            if (rightScore == 21) {  // проверка на победу
                printf("Win Second player!");
                break;
            }
            flag = 0;
        }
        if (rightRacketStart <= pointY && pointY <= rightRacketEnd &&
            pointX == rightRacketX) {  // отбивание мячика вторым игроком
            pointSpeedX = -1;
            pointX--;
        }
        if (leftRacketStart <= pointY && pointY <= leftRacketEnd &&
            pointX == leftRacketX) {  // отбивание мячика первым игроком
            pointSpeedX = 1;
            pointX++;
        }
        print_pole(max_pos_x, max_pos_y, leftRacketStart, leftRacketEnd, rightRacketStart, rightRacketEnd,
                   pointX, pointY, leftRacketX, rightRacketX);  // печать поля
        printf("Points First's player: %d\n", leftScore);
        printf("Points Second's player: %d\n", rightScore);
        char key;
        key = getchar();
        if (key_check(key) == 1) {
            if (left_board_key(key, leftRacketStart, leftRacketEnd, min_pos_y, max_pos_y) ==
                1) {  // движение ракетки первого игрока вниз
                leftRacketStart++;
                leftRacketEnd++;
            } else if (left_board_key(key, leftRacketStart, leftRacketEnd, min_pos_y, max_pos_y) ==
                       -1) {  // движение ракетки первого игрока вверх
                leftRacketStart--;
                leftRacketEnd--;
            }
            if (right_board_key(key, rightRacketStart, rightRacketEnd, min_pos_y, max_pos_y) == 1) {
                rightRacketStart++;
                rightRacketEnd++;
            } else if (right_board_key(key, rightRacketStart, rightRacketEnd, min_pos_y, max_pos_y) == -1) {
                rightRacketStart--;
                rightRacketEnd--;
            }
            pointX += pointSpeedX;
            pointY += pointSpeedY;
        }
    }
}
int left_board_key(char key, int leftRacketStart, int leftRacketEnd, int min_pos_y,
                   int max_pos_y) {  // проверка на действия первого игрока
    if (key == 'a' && leftRacketStart != min_pos_y) return -1;
    if (key == 'z' && leftRacketEnd != max_pos_y - 2) return 1;
    return 0;
}
int right_board_key(char key, int rightRacketStart, int rightRacketEnd, int min_pos_y,
                    int max_pos_y) {  // проверка на действия второго игрока
    if (key == 'k' && rightRacketStart != min_pos_y) return -1;
    if (key == 'm' && rightRacketEnd != max_pos_y - 2) return 1;
    return 0;
}

int print_pole(int max_pos_x, int max_pos_y, int leftRacketStart, int leftRacketEnd, int rightRacketStart,
               int rightRacketEnd, int pointX, int pointY, int leftRacketX, int rightRacketX) {
    // printf("\033[0d\033[2J");  // \033[0d - переносит курсор в левый верхний угол, \033[2J - очищает весь
    for (int i = 0; i < max_pos_y; i++) {  // цикл for для отрисовки поля
        for (int j = 0; j < max_pos_x; j++) {
            if (j == 0 || j == max_pos_x - 1) {         // вертикальные стенки
                printf("%c", '|');                      // pole[i][j] = vertical;
            } else if (i == 0 || i == max_pos_y - 1) {  // горизонтальные стенки
                printf("%c", '-');                      // pole[i][j] = horizontal;
            } else if (i == pointY && j == pointX) {    // мячик
                printf("%c", 'o');                      // pole[i][j] = point;
            } else if ((i >= leftRacketStart && i <= leftRacketEnd && j == leftRacketX) ||
                       (i >= rightRacketStart && i <= rightRacketEnd && j == rightRacketX)) {  // ракетки
                printf("%c", '|');  // pole[i][j] = vertical;
            } else {  // пропуски if ((i != 0 && i != max_pos_y - 1) || (j != 0 && j != max_pos_x - 1))
                printf("%c", ' ');  // pole[i][j] = space;
            }
        }
        printf("\n");
    }
    return 0;
}

int key_check(char key) {
    if (key == 'a' || key == 'z' || key == 'm' || key == 'k' || key == ' ') {
        return 1;
    }
    return -1;
}
