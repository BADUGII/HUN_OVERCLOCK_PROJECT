#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void mugunghwa_init(void);
void move_manual(key_t key);
void move_random(int i, int dir);
void move_tail(int i, int nx, int ny);
void camera(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
int yh_camera = 0;
int yh_stop = 0;
int stop_moving = 0;
int x, y;

void mugunghwa_init(void) {
	map_init(13, 40);
	for (int i = 0; i < 3; i++) {
		x = i+5;
		y = 1;
		px[i] = x;
		py[i] = y;
		back_buf[px[i]][py[i]] = '#';
	} // 영희 생성 (고정)

	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		do {
			x = randint(1, N_ROW - 2);
			y = N_COL - 2;
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	tick = 0;
}

void move_manual(key_t key) {
	// 각 방향으로 움직일 때 x, y값 delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // 움직일 방향(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;	
	default: return;
	}

	// 움직여서 놓일 자리
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail(0, nx, ny);
}

// 0 <= dir < 4가 아니면 랜덤
void move_random(int player, int dir) {
	int p = player;  // 이름이 길어서...
	int nx = 0, ny = 0;  // 움직여서 다음에 놓일 자리
	int random_xy = 0;
	int percent = 0;

	// 움직일 공간이 없는 경우는 없다고 가정(무한 루프에 빠짐)
	do {
		percent = randint(1, 10);
		if (1 <= percent && percent <= 7) {
			random_xy = 1;
		}
		else if (percent == 8) {
			random_xy = 2;
		}
		else if (percent == 9) {
			random_xy = 3;
		}
		else if (percent == 10) {
			random_xy = 4;
		}
		switch (random_xy) {
		case 1: nx = px[p] + 0, ny = py[p] + -1; break; //앞으로
		case 2: nx = px[p] + 0, ny = py[p] + 0; break; //제자리
		case 3: nx = px[p] + -1, ny = py[p] + 0; break; //위로
		case 4: nx = px[p] + 1, ny = py[p] + 0; break; //아래로
		}
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}

// back_buf[][]에 기록
void move_tail(int player, int nx, int ny) {
	int p = player;  // 이름이 길어서...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}

void camera(void) {
	if (tick % 3000 == 0) {
		yh_stop = 1;
		for (int i = 0; i < 3; i++) {
			x = i + 4;
			y = 1;
			px[i] = x;
			py[i] = y;
			back_buf[px[i]][py[i]] = '@';
		}
	}
	yh_stop = 0;
}

void mugunghwa(void) {
	mugunghwa_init();
	display();
	dialog("20232367");
	while (1) {
		mugunghwa_ment();
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}
		// player 1 부터는 랜덤으로 움직임(8방향)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {	
				//camera();
				if (yh_stop == 1) {
					stop_moving = randint(1, 10);
					if (stop_moving == 1) {
						move_random(i, -1);
						stop_moving = 0;
					}
					if (tick % 3000) {
						stop_moving = 0;
						break;
					}
					yh_stop = 0;
				}
				else {
					move_random(i, -1); //이 부분 move_manual() 부분으로 바꾸고 ()괄호 안에 들어가는 함수를 따로 만드셈 랜덤으로 10퍼센트.
				}
			}
		}
		display();
		Sleep(10);
		tick += 10;
	}
}