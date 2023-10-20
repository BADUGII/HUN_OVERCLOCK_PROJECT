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
void mugunghwa_ment();

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
	print_status();
}


//����ȭ ���� �Ǿ����ϴ�
void mugunghwa_ment() {
	char mugunghwa_ment_li[50] = "����ȭ�����Ǿ����ϴ�.";
	for (int i = 0; i < strlen(mugunghwa_ment_li); i++) {
		printf("%c", mugunghwa_ment_li[i]);
		if (i < 6) {
			Sleep(500 + i * 15); //���� ������
		}
		else {
			Sleep(250 - i * 10); //���� ������
		}
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
	printf("no. of players left: %d\n", n_alive);
	for (int p = 0; p < n_player; p++) {
		printf("player %2d: %5s\n", p, player[p] ? "alive" : "DEAD");		
	}
}

void dialog(char message[]) {
	//dialog���� �޾ƿ� char ���� ��� ���� �����ִ� �ڵ�
	//�Է����� 13�ڸ��� ������ �ȵ�.
	//����) dialog("1234567890123");
	int gotoxy_x = 3, gotoxty_y = 10;
	for (int message_count = DIALOG_DURATION_SEC; message_count >= 1; message_count--) {
		int message_length = strlen(message);
		int spaces = ((16 - message_length) / 2) - 1;
		gotoxy(gotoxy_x, gotoxty_y);
		printf("****************\n");
		gotoxy(gotoxy_x+1, gotoxty_y);
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
		gotoxy(gotoxy_x + 2, gotoxty_y);
		printf("****************\n");
		Sleep(1000);
	}
//�غ� �޼��� ����� �ڵ�
	for (int h = 0; h < 3; h++) {
		gotoxy(gotoxy_x, gotoxty_y);
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
	printf("########################################################################################################################\n");
	Sleep(150);
	printf("#     *                                                                                                                #\n");
	Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n");
	Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n");
	Sleep(150);
	printf("#                       *                                                                           *          *       #\n");
	Sleep(150);
	printf("#        *                                       *                           *                                         #\n");
	Sleep(150);
	printf("#                                                                                            *               *         #\n");
	Sleep(150);
	printf("#    *      #############################       * #########################                                 #          #\n");
	Sleep(150);
	printf("#          *       #             #                         #              #                                 #      *   #\n");
	Sleep(150);
	printf("#                 #  #         # #             *           #              #          ####################   #          #\n");
	Sleep(150);
	printf("#   *           #     #        #   #                       #       *      #          #                  #   #          #\n");
	Sleep(150);
	printf("#              #       #     #     #                       #              #          #        *         #   #    *     #\n");
	Sleep(150);
	printf("#             #         #    #      #        *            #              #         * #                  #   #          #\n");
	Sleep(150);
	printf("#     *      #      *   #  #         #                   #              #            #                  #   #          #\n");
	Sleep(150);
	printf("#           #             #          #                  #              #             #                  #   #          #\n");
	Sleep(150);
	printf("#       ##################################       ############################        ####################   #          #\n");
	Sleep(150);
	printf("#                     *  #                      *             #                                             #     *    #\n");
	Sleep(150);
	printf("#  *                     #                      *             #                                             #          #\n");
	Sleep(150);
	printf("#         *              #            *                       #                *         *                  #          #\n");
	Sleep(150);
	printf("#                 *      #                            *       #         *                           *       #          #\n");
	Sleep(150);
	printf("#                        #                                    #                                             #          #\n");
	Sleep(150);
	printf("#            *           #               *                    #                        *                               #\n");
	Sleep(150);
	printf("#                    *                                                                                     *           #\n");
	Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n");
	Sleep(150);
	printf("#                               *                                       *                                              #\n");
	Sleep(150);
	printf("#      *                                                                                                               #\n");
	Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n");
	Sleep(150);
	printf("#    *                                                                                                *                #\n");
	Sleep(150);
	printf("#                                           *                                                                          #\n");
	Sleep(150);
	printf("########################################################################################################################");
	Sleep(500);
}

//�Ϲ����� outro.
void outro_p() {
	system("cls");
	//5�� ������ ������
	//Sleep(5000)
	printf("########################################################################################################################\n");
	Sleep(150);
	printf("#     *                                                                                                                #\n");
	Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n");
	Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n");
	Sleep(150);
	printf("#                       *                                                                           *          *       #\n");
	Sleep(150);
	printf("#        *                                       *                           *                                         #\n");
	Sleep(150);
	printf("#                                                                                            *               *         #\n");
	Sleep(150);
	printf("#    *      #############################       * #########################                                 #          #\n");
	Sleep(150);
	printf("#          *       #             #                         #              #                                 #      *   #\n");
	Sleep(150);
	printf("#                 #  #         # #             *           #              #          ####################   #          #\n");
	Sleep(150);
	printf("#   *           #     #        #   #                       #       *      #          #                  #   #          #\n");
	Sleep(150);
	printf("#              #       #     #     #                       #              #          #        *         #   #    *     #\n");
	Sleep(150);
	printf("#             #         #    #      #        *            #              #         * #                  #   #          #\n");
	Sleep(150);
	printf("#     *      #      *   #  #         #                   #              #            #                  #   #          #\n");
	Sleep(150);
	printf("#           #             #          #                  #              #             #                  #   #          #\n");
	Sleep(150);
	printf("#       ##################################       ############################        ####################   #          #\n");
	Sleep(150);
	printf("#                     *  #                      *             #                                             #     *    #\n");
	Sleep(150);
	printf("#  *                     #                      *             #                                             #          #\n");
	Sleep(150);
	printf("#         *              #            *                       #                *         *                  #          #\n");
	Sleep(150);
	printf("#                 *      #                            *       #         *                           *       #          #\n");
	Sleep(150);
	printf("#                        #                                    #                                             #          #\n");
	Sleep(150);
	printf("#            *           #               *                    #                        *                               #\n");
	Sleep(150);
	printf("#                    *                                                                                     *           #\n");
	Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n");
	Sleep(150);
	printf("#                               *                                       *                                              #\n");
	Sleep(150);
	printf("#      *                                                                                                               #\n");
	Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n");
	Sleep(150);
	printf("#    *                                                                                                *                #\n");
	Sleep(150);
	printf("#                                           *                                                                          #\n");
	Sleep(150);
	printf("########################################################################################################################");
	Sleep(500);
}

//�÷��̾ �ʹ� ������ ���̴� �ƿ�Ʈ��
void outro_np() {
	system("cls");
	//5�� ������ ������
	//Sleep(5000)
	printf("########################################################################################################################\n");
	Sleep(150);
	printf("#     *                                                                                                                #\n");
	Sleep(150);
	printf("#          *       *                                      *                        *                        *          #\n");
	Sleep(150);
	printf("#                                        *                *              *                      *                *     #\n");
	Sleep(150);
	printf("#                       *                                                                           *          *       #\n");
	Sleep(150);
	printf("#        *                                       *                           *                                         #\n");
	Sleep(150);
	printf("#                                   *                                                         *               *        #\n");
	Sleep(150); 
	printf("#                  *            *                                   *                                                  #\n");
	Sleep(150);
	printf("#                                                                                            *                         #\n");
	Sleep(150);                       
	printf("#                         *                            *                                           *                   #\n");
	Sleep(150);
	printf("#         *                                *                              *                                            #\n");
	Sleep(150);
	printf("#                       *          ##################################                *                     *           #\n");
	Sleep(150);
	printf("#            *         *           #  -�÷��̾� ���� �ʹ� �����ϴ�- #      *                                           #\n");
	Sleep(150);
	printf("#           *                      ##################################               *            *                     #\n");
	Sleep(150);
	printf("#          *      *                         *                                                                          #\n");
	Sleep(150);
	printf("#                                         *                       *                                  *                 #\n");
	Sleep(150);
	printf("#                                  *              *                                   *                 *              #\n");
	Sleep(150);
	printf("#      *            *                                                        *                                         #\n");
	Sleep(150);
	printf("#                           *                                      *                           *                 *     #\n");
	Sleep(150);
	printf("#        *                        *                                                                          *         #\n");
	Sleep(150);
	printf("#                 *                             *                                       *                              #\n");
	Sleep(150);
	printf("#                                                                        *                                             #\n");
	Sleep(150);
	printf("#                    *                                                                                     *           #\n");
	Sleep(150);
	printf("#    *                                        *              *                         *               *    *          #\n");
	Sleep(150);
	printf("#                               *                                       *                                              #\n");
	Sleep(150);
	printf("#      *                                                                                                               #\n");
	Sleep(150);
	printf("#                      *                                            *              *               *           *       #\n");
	Sleep(150);
	printf("#    *                                                                                                *                #\n");
	Sleep(150);
	printf("#                                           *                                                                          #\n");
	Sleep(150);
	printf("########################################################################################################################");
	Sleep(500);
}