// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	return 0;
}

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

int main(void) {
	intro();
	jjuggumi_init();
	sample();
	//mugunghwa();	
	//nightgame();
	//juldarigi();
	//jebi();
	return 0;
}
