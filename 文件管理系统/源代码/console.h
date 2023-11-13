#pragma once
#define INI -4//�����̸�
#define X_NUM 9//��������
#define Y_NUM 9//��������
#define ESC_1 27//ESC���⽨��1
#define ESC_2 -1//ESC���⽨��2(�Զ���)
#define COLOR_NUM 6//������ɫ����
#define X_SET 160//����̨������������
#define Y_SET 40//����̨������������
#define XX_SET 160//����̨��������������
#define YY_SET 40//����̨��������������
#define SCORE_NUM 5//�÷�Ҫ����������������
#define BEGIN_NUM 7//��Ϸ��ʼ����������ɵ�������
#define GAMING_NUM 3//��Ϸ����������ɵ�������
#define MARK 1000//��¼�������������(������Ϊ3)
#define NOT -3//���̸�Χ���޷�����Χ��ͨ��״̬
#define COLOR_MIN -10//���δת��ǰ����С��ɫ����
#define COLOR_DIS 19//��ʼ��ɫ����ת����ϵͳ��ɫ������Ҫ����ӵ�ֵ


/* ������ɫ���ú궨��ȡ�����֣�������䣩 */
#define COLOR_BLACK		0	//��
#define COLOR_BLUE		1	//��
#define COLOR_GREEN		2	//��
#define COLOR_CYAN		3	//��
#define COLOR_RED		4	//��
#define COLOR_PINK		5	//��
#define COLOR_YELLOW	6	//��
#define COLOR_WHITE		7	//��
#define COLOR_HBLACK	8	//����
#define COLOR_HBLUE		9	//����
#define COLOR_HGREEN	10	//����
#define COLOR_HCYAN		11	//����
#define COLOR_HRED		12	//����
#define COLOR_HPINK		13	//����
#define COLOR_HYELLOW	14	//����
#define COLOR_HWHITE	15	//����

/* ���������̲������� */
#define CCT_MOUSE_EVENT				0
#define CCT_KEYBOARD_EVENT			1

/* �������Ĳ��� */
#define MOUSE_NO_ACTION						0x0000	//��������
#define MOUSE_ONLY_MOVED					0x0001	//����ƶ�
#define MOUSE_LEFT_BUTTON_CLICK				0x0002	//�������
#define MOUSE_LEFT_BUTTON_DOUBLE_CLICK		0x0004	//˫�����
/* ���������̬ */
#define CURSOR_VISIBLE_FULL					0	//�����ʾ��ȫ��ɫ��
#define CURSOR_VISIBLE_HALF					1	//�����ʾ�����ɫ��
#define CURSOR_VISIBLE_NORMAL				2	//�����ʾ�����ߣ�ȱʡΪ�˷�ʽ��
#define CURSOR_INVISIBLE					3	//��겻��ʾ

/* cmdαͼ�ν��溯�������б� */
//����
void cct_cls(void);
//����ʹ�����
void cct_enable_mouse(void);
//��    �ܣ�������ƶ���ָ��λ��
void cct_gotoxy(const int X, const int Y);
//���ù��״̬����ʾ/����ʾ/ȫ��/���/���ߵȣ�
void cct_setcursor(const int options);
//��    �ܣ�����ָ������ɫ
void cct_setcolor(const int bg_color, const int fg_color);
//��ȡ��ǰcmd���ڵĴ�С����
void cct_getconsoleborder(int& cols, int& lines, int& buffer_cols, int& buffer_lines);
//����ꡢ������Ϊ����������Ӧ            
int my_read_keyboard_and_mouse(int& MX, int& MY, int& MAction, int& keycode1, int& keycode2);
//�ı�cmd���ڵĴ�С���������Ĵ�С
void cct_setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines);
//��ȡ��ǰ�������λ��
void cct_getxy(int& x, int& y);
//������
void drawLeft();
void drawMiddle(int y);
void padding();
void drawRight();
void drawHeadline();
void drawAttribute();
void drawTextField();

int clickLocation(int x, int y);
void especiallyShow(int xy);
void selectFile(int state);