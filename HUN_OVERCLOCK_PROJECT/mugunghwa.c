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

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // �� �÷��̾� ��ġ, �̵� �ֱ�

void mugunghwa_init(void) {
	map_init(11, 40);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
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

void camera(void) {

}

void sample(void) {
	mugunghwa_init();
	display();
	dialog("20232367");
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}
		// player 1 ���ʹ� �������� ������(8����)
		for (int i = 1; i < n_player; i++) {
			if (tick % period[i] == 0) {	
				move_random(i, -1); //�� �κ� move_manual() �κ����� �ٲٰ� ()��ȣ �ȿ� ���� �Լ��� ���� ����� �������� 10�ۼ�Ʈ.
			}
		}
		display();
		Sleep(10);
		tick += 10;
	}
}