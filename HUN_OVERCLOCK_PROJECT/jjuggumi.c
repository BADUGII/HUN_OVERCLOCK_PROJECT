// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"
#include "canvas.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

n_player_trigger = 0;

int jjuggumi_init(void) {
	system("cls");
	srand((unsigned int)time(NULL));
	printf("����ȭ ���� �ִ� �÷��̾� : %d\n", PLAYER_MAX);
	printf("�÷��̾� �� : ");
	scanf_s("%d", &n_player);
	if (n_player <= PLAYER_MAX) { //PLAYER_MAX �� = 10
		n_player_trigger = 0;
	}
	else {
		n_player_trigger =1;
	}
	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	system("cls");
	return 0;
}

int main(void) {
	intro();
	jjuggumi_init();
	if (n_player_trigger == 1) {
		outro_np();
		exit(0);
	}
	mugunghwa();
	outro_p();
	//mugunghwa();	
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}
