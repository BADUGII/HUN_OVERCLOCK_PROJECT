#ifndef _CIO_H_
#define _CIO_H_

#include <stdbool.h>

// 화면 크기(맵 크기x. 맵 + 상태창)
#define ROW_MAX		40
#define COL_MAX		80

// 더블 버퍼링
// back_buf[][]가 맵이고, 
// front_buf[][]는 화면에 출력하기 위한 정보
// 참고: https://codevang.tistory.com/39
// 윈도우API로도 가능: https://game-happy-world.tistory.com/46
char front_buf[ROW_MAX][COL_MAX];
char back_buf[ROW_MAX][COL_MAX];

// 맵 크기(위의 buf는 텍스트까지 포함한 캔버스 크기)
int N_ROW, N_COL;

void map_init(int n_row, int n_col);

//dialog선언
void dialog(char message[]);

//앞에 뭐 있냐 확인 변수인 placable 선언
bool placable(int row, int col);

//display 선언
void display(void);

//커버 goto 선언
void gotoxy(int x, int y);

void printxy(char ch, int row, int col);

void intro();

void outro_p();

void outro_np();
#endif
