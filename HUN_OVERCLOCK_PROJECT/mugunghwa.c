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

int rnx, rny;
int rx = 3, ry = 34;
int rdir = 2;

int rpmove = 0;

int main(void) {
    srand((unsigned int)time(NULL));
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
        int p1rm = rand() % 10 + 1;

        if (p1rm == 8) {
            rpmove = 2;
        }
        else if (p1rm == 9) {
            rpmove = 3;
        }
        else if (p1rm == 10) {
            rpmove = 4;
        }
        else {
            rpmove = 1;
        }

        switch (rpmove) {
        case 1:
            rdir = 2;
            rmove();
            break;
        case 2:
            rdir = 0;
            rmove();
            break;
        case 3:
            rdir = 1;
            rmove();
            break;
        case 4:
            break;
        }

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
        ny > 0 && ny < 35 && (nx != rnx && ny != rny)) {
        map[x][y] = ' ';
        x = nx; y = ny;
        map[x][y] = '0';
    }
}

void rmove(void) {
    if (tick % 1000 == 0) {
        rnx = rx + dx[rdir];
        rny = ry + dy[rdir];
        if (rnx > 0 && rnx < 8 &&
            rny > 0 && rny < 35) {
            map[rx][ry] = ' ';
            rx = rnx; ry = rny;
            map[rx][ry] = '1';
        }
    }
}