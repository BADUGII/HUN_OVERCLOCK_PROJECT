#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void gotoxy(int row, int col);
void draw(void);
void move(void);
void rmove(void);

int tick = 0;  // 시계
int nx, ny;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int x = 2, y = 34;
int dir = 2;
char map[9][36], front[9][36];

typedef
struct {
    int rm;
    int rnx, rny;
    int rx, ry;
}PLAYER;

PLAYER player[4] = { 0 };

int main(void) {
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 4; i++) {
        player[i].rm = rand() % 10 + 1;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 36; j++) {
            if (i == 0 || i == 8 || j == 0 || j == 35)
                map[i][j] = '#';
            else
                map[i][j] = ' ';
        }
    }
    map[2][34] = '0';
    map[3][34] = '1';
    map[4][34] = '2';
    map[5][34] = '3';
    map[6][34] = '4';

    while (1) {
        if (_kbhit()) {
            int key = _getch();
            switch (key) {
            case 'w': dir = 0;
                move();
                break;
            case 's': dir = 1;
                move();
                break;
            case 'a': dir = 2;
                move();
                break;
            case 'd': dir = 3;
                move();
                break;
            case 'q': return 0;
            }
        }

        draw();
        Sleep(10);
        tick += 10;
    }
}

void gotoxy(int row, int col) {
    COORD pos = { col, row };  // 행, 열 반대로 전달
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        pos
    );
}

void draw(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 36; j++) {
            if (front[i][j] != map[i][j]) {
                front[i][j] = map[i][j];
                gotoxy(i, j);
                printf("%c", front[i][j]);
            }
        }
    }
}

void move(void) {
    nx = x + dx[dir];
    ny = y + dy[dir];
    if (nx > 0 && nx < 8 &&
        ny > 0 && ny < 35) {
        map[x][y] = ' ';
        x = nx; y = ny;
        map[x][y] = '0';
    }
}

void rmove(void) {
    rnx = rx + dx[dir];
    rny = ry + dy[dir];
    if (rnx > 0 && rnx < 8 &&
        rny > 0 && rny < 35) {
        map[rx][ry] = ' ';
        rx = rnx; ry = rny;
        map[rx][ry] = '0';
    }
}