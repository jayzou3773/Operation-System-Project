#pragma once
#define MAX_BUFFER 20
/* ϵͳ�����ֶ�Ӧ��ɫ */
#define COLOR_BLACK		0	//��
#define COLOR_WHITE		7	//��
#define COLOR_HBLUE		9	//����
#define COLOR_HGREEN	10	//����
#define COLOR_HCYAN		11	//����
#define COLOR_HRED		12	//����
#define COLOR_HPINK		13	//����
#define COLOR_HYELLOW	14	//����
#define COLOR_HWHITE	15	//����

/* ���������̬ */
#define CURSOR_VISIBLE_FULL					0	//�����ʾ��ȫ��ɫ��
#define CURSOR_VISIBLE_HALF					1	//�����ʾ�����ɫ��
#define CURSOR_VISIBLE_NORMAL				2	//�����ʾ�����ߣ�ȱʡΪ�˷�ʽ��
#define CURSOR_INVISIBLE					3	//��겻��ʾ

/* cmdαͼ�ν��溯�������б� */
//����
void cct_cls(void);
//��    �ܣ�������ƶ���ָ��λ��
void cct_gotoxy(const int X, const int Y);
//���ù��״̬����ʾ/����ʾ/ȫ��/���/���ߵȣ�
void cct_setcursor(const int options);
//��    �ܣ�����ָ������ɫ
void cct_setcolor(const int bg_color, const int fg_color);
//��ȡ��ǰcmd���ڵĴ�С����
void cct_getconsoleborder(int& cols, int& lines, int& buffer_cols, int& buffer_lines);
//�ı�cmd���ڵĴ�С���������Ĵ�С
void cct_setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines);

void input_headline(int flag);
void draw_buffer();
void buffer_paint();
int menu();
