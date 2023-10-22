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
void camera_on(void);
void camera_off(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�
int yh_camera = 0;
int stop_moving = 0;
int x, y;
int pass_player;
int clear_player;

int nx = 0, ny = 0;

bool hide(int x, int y) {
	for (int i = 0; i < n_player; i++) {
		if (px[i] == x && py[i] < y) {
			return true;
		}
	}
	return false;
}

bool pass(int x, int y) {
	for (int i = 0; i < n_player; i++) {
		if (py[i] == 1) {
			return true;
		}
	}
	return false;
}

void mugunghwa_init(void) {
	map_init(13, 40);
	for (int i = 0; i < 3; i++) {
		x = i+5;
		y = 1;
		px[i] = x;
		py[i] = y;
		back_buf[px[i]][py[i]] = '#';
	} // ���� ���� (����)

	for (int i = 0; i < n_player; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
		do {
			x = randint(1, N_ROW - 2);
			y = N_COL - 2;
		} while (!placable(x, y));
		px[i] = x;
		py[i] = y;
		period[i] = randint(40, 60);
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	tick = 0;
}
void move_manual(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_UP: dir = DIR_UP; break;
	case K_DOWN: dir = DIR_DOWN; break;
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;	
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	move_tail(0, nx, ny);
}
// 0 <= dir < 4�� �ƴϸ� ����
void move_random(int player, int dir) {
	int p = player;  // �̸��� ��...
	int nx = 0, ny = 0;  // �������� ������ ���� �ڸ�
	int random_xy = 0;
	int percent = 0;
	// ������ ������ ���� ���� ���ٰ� ����(���� ������ ����)
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
		case 1: nx = px[p] + 0, ny = py[p] + -1; break; //������
		case 2: nx = px[p] + 0, ny = py[p] + 0; break; //���ڸ�
		case 3: nx = px[p] + -1, ny = py[p] + 0; break; //����
		case 4: nx = px[p] + 1, ny = py[p] + 0; break; //�Ʒ���
		}
	} while (!placable(nx, ny));

	move_tail(p, nx, ny);
}
// back_buf[][]�� ���
void move_tail(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
}
void camera_on(void) {
	for (int i = 0; i < 3; i++) {
		gotoxy(i + 5, 1);
		printf("@");
	}
}
void camera_off(void) {
	for (int i = 0; i < 3; i++) {
		gotoxy(i + 5, 1);
		printf("#");
	}
}

void mugunghwa(void) {
	mugunghwa_init();
	display();
	dialog(" -�غ�- ");
	int a_flag = false;
	while (1) {
		clear_player = 0;
		for (int i = 0; i < n_player; i++) {
			pass_player = pass(px[i], py[i]);
		}
		for (int i = 0; i < n_player; i++) {
			if (py[i] == 1) {
				back_buf[px[i]][py[i]] = ' ';
				player[i] = true;
				clear_player++;
			}
		}
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}
		mugunghwa_ment();
		//printf("%d %d %d", player, nx, ny);
		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {
				move_random(i, -1);
			}
		}
		if (yh_stop == true) {
			camera_on();
			stop_moving = randint(1, 10); //10�ۼ�Ʈ
			for (int i = 1; i < n_player; i++) {
				if (player[i] == 0) {
					continue;
				}
				if (!pass_player && !randint(0,9) && !hide(px[i], py[i])) {
					move_random(i, -1);
					stop_moving = 0;
					back_buf[px[i]][py[i]] = ' ';
					player[i] = false;
					n_alive = n_alive - 1;
					char dialog_empty[100] = { (char)i + '0',' ','p','l','a','y','e','r',' ','d','i','e', NULL};
					dialog(dialog_empty);
				}
			}
			while (1) {
				key_t key = get_key();
				if (player[0] == 1) {
					if (key == K_QUIT) {
						break;
					}
					else if (key != K_UNDEFINED) {
						move_manual(key);
						draw();
						a_flag = true;
					}
				}
				if (stop_tick / 3000 == 1) {
					stop_tick = 0;
					break;
				}
				else {
					Sleep(10);
					stop_tick += 10;
				}
			}
			yh_stop = false;
			//!hide(px[i], py[i])
			if (a_flag && !hide(px[0], py[0])) {
				back_buf[px[0]][py[0]] = ' ';
				player[0] = false;
				n_alive = n_alive - 1;
				dialog("0 player die");
			}
			a_flag = false;
			camera_off();
		}
		camera_off();
		display();
		if (n_alive == 1) {
			for (int i = 0; i < n_player; i++) {
				if (player[i] == true) {
					winner_player = i;
				}
			}
			winner_outro_p();
			exit(0);
		}
		if (n_alive == clear_player) {
			outro_p();
			exit(0);
		}
		Sleep(10);
		tick += 10;
	}
}