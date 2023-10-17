#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

void gotoxy(int row, int col);
void draw(void);
void move(void);
void rmove1(void);
void rmove2(void);
void rmove3(void);
void rmove4(void);

int tick = 0;  // 시계
int nx, ny;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int x = 2, y = 34;
int dir = 2;
char map[9][36], front[9][36];

int rnx1, rny1;
int rx1 = 3, ry1 = 34;

int rnx2, rny2;
int rx2 = 4, ry2 = 34;

int rnx3, rny3;
int rx3 = 5, ry3 = 34;

int rnx4, rny4;
int rx4 = 6, ry4 = 34;

int rdir = 2;

int rpmove1 = 0;
int rpmove2 = 0;
int rpmove3 = 0;
int rpmove4 = 0;

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
		int prm1 = rand() % 10 + 1;
		int prm2 = rand() % 10 + 1;
		int	prm3 = rand() % 10 + 1;
		int prm4 = rand() % 10 + 1;

		if (prm1 == 8) {
			rpmove1 = 2;
		}
		else if (prm1 == 9) {
			rpmove1 = 3;
		}
		else if (prm1 == 10) {
			rpmove1 = 4;
		}
		else {
			rpmove1 = 1;
		}

		switch (rpmove1) {
		case 1:
			rdir = 2;
			rmove1();
			break;
		case 2:
			rdir = 0;
			rmove1();
			break;
		case 3:
			rdir = 1;
			rmove1();
			break;
		case 4:
			break;
		}

		if (prm2 == 8) {
			rpmove2 = 2;
		}
		else if (prm2 == 9) {
			rpmove2 = 3;
		}
		else if (prm2 == 10) {
			rpmove2 = 4;
		}
		else {
			rpmove2 = 1;
		}

		switch (rpmove2) {
		case 1:
			rdir = 2;
			rmove2();
			break;
		case 2:
			rdir = 0;
			rmove2();
			break;
		case 3:
			rdir = 1;
			rmove2();
			break;
		case 4:
			break;
		}

		if (prm3 == 8) {
			rpmove3 = 2;
		}
		else if (prm3 == 9) {
			rpmove3 = 3;
		}
		else if (prm3 == 10) {
			rpmove3 = 4;
		}
		else {
			rpmove3 = 1;
		}

		switch (rpmove3) {
		case 1:
			rdir = 2;
			rmove3();
			break;
		case 2:
			rdir = 0;
			rmove3();
			break;
		case 3:
			rdir = 1;
			rmove3();
			break;
		case 4:
			break;
		}

		if (prm4 == 8) {
			rpmove4 = 2;
		}
		else if (prm4 == 9) {
			rpmove4 = 3;
		}
		else if (prm4 == 10) {
			rpmove4 = 4;
		}
		else {
			rpmove4 = 1;
		}

		switch (rpmove4) {
		case 1:
			rdir = 2;
			rmove4();
			break;
		case 2:
			rdir = 0;
			rmove4();
			break;
		case 3:
			rdir = 1;
			rmove4();
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
		ny > 0 && ny < 35) {
		map[x][y] = ' ';
		x = nx; y = ny;
		map[x][y] = '0';
	}
}

void rmove1(void) {
	if (tick % 1000 == 0) {
		rnx1 = rx1 + dx[rdir];
		rny1 = ry1 + dy[rdir];
		if (rnx1 > 0 && rnx1 < 8 &&
			rny1 > 0 && rny1 < 36 && (map[nx][ny] != map[rnx1][rny1])) {
			map[rx1][ry1] = ' ';
			rx1 = rnx1; ry1 = rny1;
			map[rx1][ry1] = '1';
		}
	}
}

void rmove2(void) {
	if (tick % 1000 == 0) {
		rnx2 = rx2 + dx[rdir];
		rny2 = ry2 + dy[rdir];
		if (rnx2 > 0 && rnx2 < 8 &&
			rny2 > 0 && rny2 < 36 && (map[nx][ny] != map[rnx2][rny2])) {
			map[rx2][ry2] = ' ';
			rx2 = rnx2; ry2 = rny2;
			map[rx2][ry2] = '2';
		}
	}
}

void rmove3(void) {
	if (tick % 1000 == 0) {
		rnx3 = rx3 + dx[rdir];
		rny3 = ry3 + dy[rdir];
		if (rnx3 > 0 && rnx3 < 8 &&
			rny3 > 0 && rny3 < 36 && (map[nx][ny] != map[rnx3][rny3])) {
			map[rx3][ry3] = ' ';
			rx3 = rnx3; ry3 = rny3;
			map[rx3][ry3] = '3';
		}
	}
}

void rmove4(void) {
	if (tick % 1000 == 0) {
		rnx4 = rx4 + dx[rdir];
		rny4 = ry4 + dy[rdir];
		if (rnx4 > 0 && rnx4 < 8 &&
			rny4 > 0 && rny4 < 36 && (map[nx][ny] != map[rnx4][rny4])) {
			map[rx4][ry4] = ' ';
			rx4 = rnx4; ry4 = rny4;
			map[rx4][ry4] = '4';
		}
	}
}