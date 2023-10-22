#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);
void intro();
void outro_p();
void outro_np();
void winner_outro_p();
void mugunghwa_ment();
void mugunghwa_ment_clean();

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

// �� �̴ֿ� ������ �����ͷ� ���� ������ 
void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}
	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 3, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	//mugunghwa_ment();
	print_status();
}

//����ȭ ���� �Ǿ����ϴ�
int mugunghwa_ment_count = 0;

void mugunghwa_ment() {
	//mugunghwa_ment_flag = 1; //����ȭ ��Ʈ �÷��� ���� �ǰ� ������ �������� ������. �÷��� ���� 1 / 0�϶� �����̸� �״°ɷ� ���
	//printf("%d\n", tick);
	if (yh_stop == 0 && tick % 100 == 0) {
		mugunghwa_ment_count = tick / 100;
		//printf("%d", mugunghwa_ment_count);
		if (tick == 100) {
			gotoxy(N_ROW + 1, 0);
			printf("��");
		}
		else if (tick == 200) {
			gotoxy(N_ROW + 1, 3);
			printf("��");
		}
		else if (tick == 400) {
			gotoxy(N_ROW + 1, 6);
			printf("ȭ");
		}
		else if (tick == 500) {
			gotoxy(N_ROW + 1, 9);
			printf("��");
		}
		else if (tick == 700) {
			gotoxy(N_ROW + 1, 12);
			printf("��");
		}
		else if (tick == 1000) {
			gotoxy(N_ROW + 1, 15);
			printf("��");
		}
		else if (tick == 1200) {
			gotoxy(N_ROW + 1, 18);
			printf("��");
		}
		else if (tick == 1400) {
			gotoxy(N_ROW + 1, 21);
			printf("��");
		}
		else if (tick == 1500) {
			gotoxy(N_ROW + 1, 24);
			printf("��");
		}
		else if (tick == 1600) {
			gotoxy(N_ROW + 1, 27);
			printf("��");
		}
		else if (tick == 1700) {
			gotoxy(N_ROW + 1, 30);
			printf(".");
			yh_stop = true;
		}
		if (yh_stop == false) {
			mugunghwa_ment_clean();
		}
	}
	Sleep(10);
}

void mugunghwa_ment_clean() {
	if (tick >= 1700) {
		gotoxy(N_ROW + 1, 0);
		printf("                                      ");
		gotoxy(N_ROW + 1, 0);
		tick = 0;
	}
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d \n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");		
	}
}

void dialog(char message[]) {
	//dialog���� �޾ƿ� char ���� ��� ���� �����ִ� �ڵ�
	//�Է����� 13�ڸ��� ������ �ȵ�.
	//����) dialog("1234567890123");
	int gotoxy_x = 5, gotoxy_y = 12;
	for (int message_count = DIALOG_DURATION_SEC; message_count >= 1; message_count--) {
		int message_length = strlen(message);
		int spaces = ((16 - message_length) / 2) - 1;
		gotoxy(gotoxy_x, gotoxy_y);
		printf("****************\n");
		gotoxy(gotoxy_x+1, gotoxy_y);
		printf("*");
		printf("%d", message_count);
		for (int i = 0; i < spaces; i++) {
			printf(" ");
		}
		printf("%s", message);
		if (message_length % 2 != 0) {
			for (int i = 0; i < spaces; i++) {
				printf(" ");
			}
		}else {
			for (int j = 0; j < spaces - 1; j++) {
				printf(" ");
			}
		}
		printf("*\n");
		gotoxy(gotoxy_x + 2, gotoxy_y);
		printf("****************\n");
		Sleep(1000);
	}
//�غ� �޼��� ����� �ڵ�
	for (int h = 0; h < 3; h++) {
		gotoxy(gotoxy_x, gotoxy_y);
		for (int j = 0; j < 16; j++) {
			printf(" ");
		}
		gotoxy_x=gotoxy_x + 1;
	}
}

//intro
void intro() {
	system("cls");
	//5�� ������ ������
	//Sleep(5000)
	printf("########################################################################################################################\n"); Sleep(150);
	printf("#     *                                                                                                                #\n"); Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n"); Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n"); Sleep(150);
	printf("#                       *                                                                           *          *       #\n"); Sleep(150);
	printf("#        *                                       *                           *                                         #\n"); Sleep(150);
	printf("#                                                                                            *               *         #\n"); Sleep(150);
	printf("#    *      #############################       * #########################                                 #          #\n"); Sleep(150);
	printf("#          *       #             #                         #              #                                 #      *   #\n"); Sleep(150);
	printf("#                 #  #         # #             *           #              #          ####################   #          #\n"); Sleep(150);
	printf("#   *           #     #        #   #                       #       *      #          #                  #   #          #\n"); Sleep(150);
	printf("#              #       #     #     #                       #              #          #        *         #   #    *     #\n"); Sleep(150);
	printf("#             #         #    #      #        *            #              #         * #                  #   #          #\n"); Sleep(150);
	printf("#     *      #      *   #  #         #                   #              #            #                  #   #          #\n"); Sleep(150);
	printf("#           #             #          #                  #              #             #                  #   #          #\n"); Sleep(150);
	printf("#       ##################################       ############################        ####################   #          #\n"); Sleep(150);
	printf("#                     *  #                      *             #                                             #     *    #\n"); Sleep(150);
	printf("#  *                     #                      *             #                                             #          #\n"); Sleep(150);
	printf("#         *              #            *                       #                *         *                  #          #\n"); Sleep(150);
	printf("#                 *      #                            *       #         *                           *       #          #\n"); Sleep(150);
	printf("#                        #                                    #                                             #          #\n"); Sleep(150);
	printf("#            *           #               *                    #                        *                               #\n"); Sleep(150);
	printf("#                    *                                                                                     *           #\n"); Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n"); Sleep(150);
	printf("#                               *                                       *                                              #\n"); Sleep(150);
	printf("#      *                                                                                                               #\n"); Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n"); Sleep(150);
	printf("#    *                                                                                                *                #\n"); Sleep(150);
	printf("#                                           *                                                                          #\n"); Sleep(150);
	printf("########################################################################################################################"); Sleep(500);
}

//�Ϲ����� outro.
void outro_p() {
	system("cls");
	//5�� ������ ������
	//Sleep(5000)
	printf("########################################################################################################################\n"); Sleep(150);
	printf("#     *                                                                                                                #\n"); Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n"); Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n"); Sleep(150);
	printf("#                       *                                                                           *          *       #\n"); Sleep(150);
	printf("#        *                                       *                           *                                         #\n"); Sleep(150);
	printf("#                                   *                                                         *               *        #\n"); Sleep(150);
	printf("#                  *            *                                   *                                                  #\n"); Sleep(150);
	printf("#                                                                                            *                         #\n"); Sleep(150);
	printf("#                         *                            *                                           *                   #\n"); Sleep(150);
	printf("#         *                                *                              *                                            #\n"); Sleep(150);
	printf("#                       *                                                            *                     *           #\n"); Sleep(150);
	printf("#            *         *                                                   *                                           #\n"); Sleep(150);
	printf("#           *                           ###########################################              *                     #\n");Sleep(150);
	printf("#          *      *                     #   ���� ���� �÷��̾ %d�� ���ҽ��ϴ�   #                                    #\n", n_alive); Sleep(150);
	printf("#                      *                ###########################################                  *                 #\n"); Sleep(150);
	printf("#                                  *              *                                   *                 *              #\n"); Sleep(150);
	printf("#      *            *                                                        *                                         #\n"); Sleep(150);
	printf("#                           *                                      *                           *                 *     #\n"); Sleep(150);
	printf("#        *                        *                                                                          *         #\n"); Sleep(150);
	printf("#                 *                             *                                       *                              #\n"); Sleep(150);
	printf("#                                                                        *                                             #\n"); Sleep(150);
	printf("#                    *                                                                                     *           #\n"); Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n"); Sleep(150);
	printf("#                               *                                       *                                              #\n"); Sleep(150);
	printf("#      *                                                                                                               #\n"); Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n"); Sleep(150);
	printf("#    *                                                                                                *                #\n"); Sleep(150);
	printf("#                                           *                                                                          #\n"); Sleep(150);
	printf("########################################################################################################################"); Sleep(500);
}

//�÷��̾ �ʹ� ������ ���̴� �ƿ�Ʈ��
void outro_np() {
	system("cls");
	//5�� ������ ������
	//Sleep(5000)
	printf("########################################################################################################################\n"); Sleep(150);
	printf("#     *                                                                                                                #\n"); Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n"); Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n"); Sleep(150);
	printf("#                       *                                                                           *          *       #\n"); Sleep(150);
	printf("#        *                                       *                           *                                         #\n"); Sleep(150);
	printf("#                                   *                                                         *               *        #\n"); Sleep(150);
	printf("#                  *            *                                   *                                                  #\n"); Sleep(150);
	printf("#                                                                                            *                         #\n"); Sleep(150);
	printf("#                         *                            *                                           *                   #\n"); Sleep(150);
	printf("#         *                                *                              *                                            #\n"); Sleep(150);
	printf("#                       *                                                            *                     *           #\n"); Sleep(150);
	printf("#            *         *                                                   *                                           #\n"); Sleep(150);
	printf("#           *                               ##################################      *            *                     #\n"); Sleep(150);
	printf("#          *      *                         #  -�÷��̾� ���� �ʹ� �����ϴ�- #    *                                    #\n"); Sleep(150);
	printf("#                      *                    ##################################       *               *                 #\n"); Sleep(150);
	printf("#                                  *              *                                   *                 *              #\n"); Sleep(150);
	printf("#      *            *                                                        *                                         #\n"); Sleep(150);
	printf("#                           *                                      *                           *                 *     #\n"); Sleep(150);
	printf("#        *                        *                                                                          *         #\n"); Sleep(150);
	printf("#                 *                             *                                       *                              #\n"); Sleep(150);
	printf("#                                                                        *                                             #\n"); Sleep(150);
	printf("#                    *                                                                                     *           #\n"); Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n"); Sleep(150);
	printf("#                               *                                       *                                              #\n"); Sleep(150);
	printf("#      *                                                                                                               #\n"); Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n"); Sleep(150);
	printf("#    *                                                                                                *                #\n"); Sleep(150);
	printf("#                                           *                                                                          #\n"); Sleep(150);
	printf("########################################################################################################################"); Sleep(500);
}

void winner_outro_p() {
	system("cls");
	//5�� ������ ������
	//Sleep(5000)
	printf("########################################################################################################################\n"); Sleep(150);
	printf("#     *                                                                                                                #\n"); Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n"); Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n"); Sleep(150);
	printf("#                       *                                                                           *          *       #\n"); Sleep(150);
	printf("#        *                                       *                           *                                         #\n"); Sleep(150);
	printf("#                                   *                                                         *               *        #\n"); Sleep(150);
	printf("#                  *            *                                   *                                                  #\n"); Sleep(150);
	printf("#                                                                                            *                         #\n"); Sleep(150);
	printf("#                         *                            *                                           *                   #\n"); Sleep(150);
	printf("#         *                                *                              *                                            #\n"); Sleep(150);
	printf("#                       *                                                            *                     *           #\n"); Sleep(150);
	printf("#            *         *                                                   *                                           #\n"); Sleep(150);
	printf("#           *                           ###########################################              *                     #\n"); Sleep(150);
	printf("#          *      *                     #     ���� ���� ����ڴ� %d�� �÷��̾�     #                                    #\n", winner_player); Sleep(150);
	printf("#                      *                ###########################################                  *                 #\n"); Sleep(150);
	printf("#                                  *              *                                   *                 *              #\n"); Sleep(150);
	printf("#      *            *                                                        *                                         #\n"); Sleep(150);
	printf("#                           *                                      *                           *                 *     #\n"); Sleep(150);
	printf("#        *                        *                                                                          *         #\n"); Sleep(150);
	printf("#                 *                             *                                       *                              #\n"); Sleep(150);
	printf("#                                                                        *                                             #\n"); Sleep(150);
	printf("#                    *                                                                                     *           #\n"); Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n"); Sleep(150);
	printf("#                               *                                       *                                              #\n"); Sleep(150);
	printf("#      *                                                                                                               #\n"); Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n"); Sleep(150);
	printf("#    *                                                                                                *                #\n"); Sleep(150);
	printf("#                                           *                                                                          #\n"); Sleep(150);
	printf("########################################################################################################################"); Sleep(500);
}