// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LENGTH 80
#define WIDTH 25
#define racketLength 3

void moveRacketRight(char fieldPlaying[WIDTH][LENGTH], int unit, int *predRackR) {
    if ((unit < 0) && (fieldPlaying[*predRackR + unit][LENGTH - 4] != '#')) {
        fieldPlaying[*predRackR + unit][LENGTH - 4] = '|';
        fieldPlaying[*predRackR + racketLength + unit][LENGTH - 4] = ' ';
        *predRackR += unit;
    } else if ((unit > 0) && (fieldPlaying[*predRackR + racketLength][LENGTH - 4] != '#')) {
        fieldPlaying[*predRackR][LENGTH - 4] = ' ';
        fieldPlaying[*predRackR + racketLength][LENGTH - 4] = '|';
        *predRackR += unit;
    }
}

void moveRacketLeft(char fieldPlaying[WIDTH][LENGTH], int unit, int *predRackl) {
    if ((unit < 0) && (fieldPlaying[*predRackl + unit][2] != '#')) {
        fieldPlaying[*predRackl + unit][2] = '|';
        fieldPlaying[*predRackl + racketLength + unit][2] = ' ';
        *predRackl += unit;
    } else if ((unit > 0) && (fieldPlaying[*predRackl + racketLength][2] != '#')) {
        fieldPlaying[*predRackl][2] = ' ';
        fieldPlaying[*predRackl + racketLength][2] = '|';
        *predRackl += unit;
    }
}

void initBall(int *xBall, int *yBall) {
    *xBall = LENGTH / 2;
    *yBall = WIDTH / 2;
}

void moveBall(char fieldPlaying[WIDTH][LENGTH], int *xBall, int *yBall, int *vectorX, int *vectorY,
              int *leftPlayerGoal, int *rigthPlayerGoal) {
    fieldPlaying[*yBall][*xBall] = ' ';
    int predXBall, predYBall;

    predXBall = *xBall;
    predYBall = *yBall;

    *xBall += *vectorX;
    *yBall += *vectorY;

    if ((*yBall == WIDTH - 1) || (*yBall == 0)) {  //проверка на столкновение с верхними и нижними границами
        *vectorY = *vectorY * -1;
        *xBall = predXBall;
        *yBall = predYBall;
        fieldPlaying[predYBall][predXBall] = 'o';
    } else if ((*xBall >= LENGTH - 2) || (*xBall <= 1)) {  // проверка на столкновение боковыми границами
        if (*xBall <= 1) *rigthPlayerGoal += 1;  // если шарик слева, правый забил гол
        if (*xBall >= LENGTH - 2) *leftPlayerGoal += 1;  // если шарик справа, левый забил гол
        initBall(xBall, yBall);
        fieldPlaying[*yBall][*xBall] = 'o';
    } else if (fieldPlaying[*yBall][*xBall] == '|') {  // проверка на отбитие ракеткой
        *vectorX = -(*vectorX);
        *xBall = predXBall;
        *yBall = predYBall;
        fieldPlaying[predYBall][*xBall] = 'o';
    } else
        fieldPlaying[*yBall][*xBall] = 'o';
}

void initRacketLeft(char fieldPlaying[WIDTH][LENGTH], int *predRackl) {
    int yRacketLeft = (WIDTH - racketLength) / 2;
    *predRackl = yRacketLeft;
    for (int i = 0; i < racketLength; i++) {
        fieldPlaying[yRacketLeft + i][2] = '|';
    }
}

void initRacketRight(char fieldPlaying[WIDTH][LENGTH], int *predRackR) {
    int yRacketRight = (WIDTH - racketLength) / 2;
    *predRackR = yRacketRight;
    for (int i = 0; i < racketLength; i++) {
        fieldPlaying[yRacketRight + i][LENGTH - 4] = '|';
    }
}

void initFieldForPlaying(char fieldPlaying[WIDTH][LENGTH]) {
    for (int i = 0; i < LENGTH - 1; i++) {
        fieldPlaying[0][i] = '#';
        fieldPlaying[WIDTH - 1][i] = '#';
    }
    for (int i = 0; i < LENGTH - 1; i++) {
        if (i == 0 || i == LENGTH - 2)
            fieldPlaying[1][i] = '#';
        else
            fieldPlaying[1][i] = ' ';
    }
    for (int i = 2; i < WIDTH - 1; i++) {
        strcpy(fieldPlaying[i], fieldPlaying[1]);
    }
}

void showFieldForPlaying(char fieldPlaying[WIDTH][LENGTH], int *leftPlayerGoal, int *rigthPlayerGoal) {
    for (int i = 0; i < WIDTH; i++) {
        printw("%s\n", fieldPlaying[i]);
    }
    printw("Points left player: %d\n", *leftPlayerGoal);
    printw("Points right player: %d\n", *rigthPlayerGoal);
    refresh();
}

/*void showOfWinner(int leftPlayerGoal) {
    clear(); // очищаем экран
    if (leftPlayerGoal == 21) {
        printw("Левый игрок, поздравляем с победой игрок!\n");
    } else {
        printw("Правый игрок, поздравляем с победой игрок!\n");
    }
    napms(3000); // подождать 3000 миллисекунд (3 секунды) перед выходом
}*/

int main(void) {
    initscr();
    noecho();  // Отключаем эхо ввода
    cbreak();  // Отключаем буферизацию ввода
    int leftPlayerGoal, rigthPlayerGoal;
    leftPlayerGoal = 0;
    rigthPlayerGoal = 0;

    int xBall, yBall, vectorX, vectorY;
    vectorX = 1;
    vectorY = 1;
    int predRackl, predRackR, key;
    char fieldPlaying[WIDTH][LENGTH];

    initFieldForPlaying(fieldPlaying);
    initBall(&xBall, &yBall);
    initRacketLeft(fieldPlaying, &predRackl);
    initRacketRight(fieldPlaying, &predRackR);

    do {
        moveBall(fieldPlaying, &xBall, &yBall, &vectorX, &vectorY, &leftPlayerGoal, &rigthPlayerGoal);
        showFieldForPlaying(fieldPlaying, &leftPlayerGoal, &rigthPlayerGoal);
        halfdelay(1);
        key = getch();

        switch (key) {
            case 'a':
                moveRacketLeft(fieldPlaying, -1, &predRackl);
                break;
            case 'z':
                moveRacketLeft(fieldPlaying, 1, &predRackl);
                break;
            case 'k':
                moveRacketRight(fieldPlaying, -1, &predRackR);
                break;
            case 'm':
                moveRacketRight(fieldPlaying, 1, &predRackR);
                break;
        }
        if (leftPlayerGoal == 21 || rigthPlayerGoal == 21) key = 'q';
        clear();
    } while (key != 'q');

    // showOfWinner(leftPlayerGoal);
    endwin();
    return 0;
}

//-std=c11
