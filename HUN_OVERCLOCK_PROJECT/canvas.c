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

// (zero-base) row행, col열로 커서 이동
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row행, col열에 ch 출력
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

// 맵 이닛에 들어오는 데이터로 맵이 정해짐 
void map_init(int n_row, int n_col) {
	// 두 버퍼를를 완전히 비우기
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}
	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// 대입문 이렇게 쓸 수 있는데 일부러 안 가르쳐줬음
		back_buf[i][0] = back_buf[i][N_COL - 1] = '*';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '*' : ' ';
		}
	}
}

// back_buf[row][col]이 이동할 수 있는 자리인지 확인하는 함수
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// 상단에 맵을, 하단에는 현재 상태를 출력
void display(void) {
	draw();
	gotoxy(N_ROW + 3, 0);  // 추가로 표시할 정보가 있으면 맵과 상태창 사이의 빈 공간에 출력
	//mugunghwa_ment();
	print_status();
}

//무궁화 꽃이 피었습니다
int mugunghwa_ment_count = 0;

void mugunghwa_ment() {
	//mugunghwa_ment_flag = 1; //무궁화 멘트 플래그 실행 되고 있을때 움직여도 괜찮음. 플래그 상태 1 / 0일때 움직이면 죽는걸로 고고
	//printf("%d\n", tick);
	if (yh_stop == 0 && tick % 100 == 0) {
		mugunghwa_ment_count = tick / 100;
		//printf("%d", mugunghwa_ment_count);
		if (tick == 100) {
			gotoxy(N_ROW + 1, 0);
			printf("무");
		}
		else if (tick == 200) {
			gotoxy(N_ROW + 1, 3);
			printf("궁");
		}
		else if (tick == 400) {
			gotoxy(N_ROW + 1, 6);
			printf("화");
		}
		else if (tick == 500) {
			gotoxy(N_ROW + 1, 9);
			printf("꽃");
		}
		else if (tick == 700) {
			gotoxy(N_ROW + 1, 12);
			printf("이");
		}
		else if (tick == 1000) {
			gotoxy(N_ROW + 1, 15);
			printf("피");
		}
		else if (tick == 1200) {
			gotoxy(N_ROW + 1, 18);
			printf("었");
		}
		else if (tick == 1400) {
			gotoxy(N_ROW + 1, 21);
			printf("습");
		}
		else if (tick == 1500) {
			gotoxy(N_ROW + 1, 24);
			printf("니");
		}
		else if (tick == 1600) {
			gotoxy(N_ROW + 1, 27);
			printf("다");
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
	//dialog에서 받아온 char 값을 가운데 정렬 시켜주는 코드
	//입력으로 13자리가 넘으면 안됨.
	//예시) dialog("1234567890123");
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
//준비 메세지 지우는 코드
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
	//5초 안으로 끝내기
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

//일반적인 outro.
void outro_p() {
	system("cls");
	//5초 안으로 끝내기
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
	printf("#          *      *                     #   게임 종료 플레이어가 %d명 남았습니다   #                                    #\n", n_alive); Sleep(150);
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

//플레이어가 너무 많을때 쓰이는 아웃트로
void outro_np() {
	system("cls");
	//5초 안으로 끝내기
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
	printf("#          *      *                         #  -플레이어 수가 너무 많습니다- #    *                                    #\n"); Sleep(150);
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
	//5초 안으로 끝내기
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
	printf("#          *      *                     #     게임 종료 우승자는 %d번 플레이어     #                                    #\n", winner_player); Sleep(150);
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