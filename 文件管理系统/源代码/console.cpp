#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>//cmd_tools ��Ҫ
#include "console.h"
using namespace std;

//extern class City city;
static const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);		//ȡ��׼����豸��Ӧ�ľ��
static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE);		//ȡ��׼�����豸��Ӧ�ľ��

//��    �ܣ�����ָ������ɫ
void cct_setcolor(const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(__hout, bg_color * 16 + fg_color);
}
//��    �ܣ�������ƶ���ָ��λ��
void cct_gotoxy(const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(__hout, coord);
}
//��������
void cct_cls(void)
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo; /* to get buffer info */
	DWORD num;

	/* ȡ��ǰ��������Ϣ */
	GetConsoleScreenBufferInfo(__hout, &binfo);
	/* ����ַ� */
	FillConsoleOutputCharacter(__hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	/* ������� */
	FillConsoleOutputAttribute(__hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);

	/* ���ص�(0,0) */
	SetConsoleCursorPosition(__hout, coord);
	return;
}
//ȡ��ǰcmd���ڵĴ�С����
void cct_getconsoleborder(int& cols, int& lines, int& buffer_cols, int& buffer_lines)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(__hout, &binfo);

	cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;		//�ɼ����ڵ�����
	lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;		//�ɼ����ڵ�����
	buffer_cols = binfo.dwSize.X;			//������������
	buffer_lines = binfo.dwSize.Y;			//������������
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ��ı�cmd���ڵĴ�С���������Ĵ�С
  ���������const int cols         ���µ�����
			const int lines        ���µ�����
			const int buffer_cols  ���µĻ���������
			const int buffer_lines ���µĻ���������
  �� �� ֵ��
  ˵    �������������û������������ô��ڴ�С��
			���������ڴ�С���ڵ�ǰ��������δ����ǰ��������ʧ��
***************************************************************************/
void cct_setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines)
{
	/* ȡ��ǰϵͳ����Ĵ��ڵ��������ֵ */
	COORD max_coord;
	max_coord = GetLargestConsoleWindowSize(__hout); /* .X �� .Y �ֱ��Ǵ��ڵ��к��е����ֵ */

	/* �������ô��ڵ����еķǷ�ֵ */
	if (set_cols <= 0 || set_lines <= 0)
		return;
	if (set_cols > max_coord.X)
		set_cols = max_coord.X;
	if (set_lines > max_coord.Y)
		set_lines = max_coord.Y;

	/* ���ô��ڵ����д�С����0��ʼ��0 ~ lines-1, 0 ~ cols-1��*/
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Bottom = set_lines - 1;
	rect.Left = 0;
	rect.Right = set_cols - 1;

	/* ���û����������д�С(ȱʡ��С�ڴ���ֵ���봰��ֵһ��) */
	COORD cr;
	cr.X = (set_buffer_cols == -1 || set_buffer_cols < set_cols) ? set_cols : set_buffer_cols;		//δ�����������ֵС��set_cols����set_cols��δ��������
	cr.Y = (set_buffer_lines == -1 || set_buffer_lines < set_lines) ? set_lines : set_buffer_lines;	//δ�����������ֵС��set_lines����set_lines��δ��������

	/* ȡ��ǰ���ڼ��������Ĵ�С(����getconsoleborder) */
	int cur_cols, cur_lines, cur_buffer_cols, cur_buffer_lines;
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(__hout, &binfo);

	cur_cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;	//�ɼ����ڵ�����
	cur_lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;	//�ɼ����ڵ�����
	cur_buffer_cols = binfo.dwSize.X;							//������������
	cur_buffer_lines = binfo.dwSize.Y;							//������������

	cct_cls();
	/* ����˳��(��֤���ô��ڴ�Сʱ���ֻ���������ֵ>����ֵ) */
	if (cr.X <= cur_buffer_cols) {
		if (cr.Y <= cur_buffer_lines) {
			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
		}
		else { //cr.Y > cur_buffer_lines����Ҫ�û��������������
			COORD tmpcr;
			tmpcr.X = cur_buffer_cols;
			tmpcr.Y = cr.Y;
			SetConsoleScreenBufferSize(__hout, tmpcr);//���û�����

			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
		}
	}
	else {//cr.X > cur_buffer_cols
		if (cr.Y >= cur_buffer_lines) {
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
		}
		else {	//cr.Y < cur_buffer_lines
			COORD tmpcr;
			tmpcr.X = cr.X;
			tmpcr.Y = cur_buffer_lines;
			SetConsoleScreenBufferSize(__hout, tmpcr);//���û�����

			SetConsoleWindowInfo(__hout, true, &rect);//���ô���
			SetConsoleScreenBufferSize(__hout, cr);//���û�����
		}
	}

	return;
}
//����ʹ�����
void cct_enable_mouse(void)
{
	DWORD Mode;

	GetConsoleMode(__hin, &Mode);	/* ȡ�ÿ���̨ԭ����ģʽ */
	SetConsoleMode(__hin, Mode | ENABLE_MOUSE_INPUT);	//�������֧�֣�����ԭ����֧����꣬�ټ�Ҳû��
}
//���ù��״̬����ʾ/����ʾ/ȫ��/���/���ߵȣ�
void cct_setcursor(const int options)
{
	CONSOLE_CURSOR_INFO cursor_info;

	switch (options) {
	case CURSOR_VISIBLE_FULL:
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 100;
		break;
	case CURSOR_VISIBLE_HALF:
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 50;
		break;
	case CURSOR_INVISIBLE:
		cursor_info.bVisible = 0;
		cursor_info.dwSize = 1;
		break;
	case CURSOR_VISIBLE_NORMAL:
	default: //ȱʡ��ʾ��꣬����
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 25;
		break;
	}
	SetConsoleCursorInfo(__hout, &cursor_info);
}
//ȡ��ǰ�������λ�õ�����ֵ
void cct_getxy(int& x, int& y)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(__hout, &binfo);

	x = binfo.dwCursorPosition.X;
	y = binfo.dwCursorPosition.Y;

	return;
}
/*************************************************************/
/***            ����ꡢ������Ϊ����������Ӧ               ***/
/*************************************************************/
int my_read_keyboard_and_mouse(int& MX, int& MY, int& MAction, int& keycode1, int& keycode2)
{
	cct_enable_mouse();//����ʹ�����
	static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED, x = 0, y = 0, xx = 0, yy = 0;
	INPUT_RECORD InputRec;
	DWORD        res;
	COORD        crPos;

	while (1)
	{
		ReadConsoleInput(__hin, &InputRec, 1, &res);
		if (InputRec.EventType == KEY_EVENT)
		{
			if (InputRec.Event.KeyEvent.bKeyDown)
			{
				if (InputRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					return -1;
				else
					continue;
			}
			return 1;
		}
		if (InputRec.EventType == MOUSE_EVENT)
		{
			crPos = InputRec.Event.MouseEvent.dwMousePosition;
			MX = crPos.X;
			MY = crPos.Y;
			if (InputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{ //�������
				if (InputRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
					MAction = MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
				else
				{
					MAction = MOUSE_LEFT_BUTTON_CLICK;
					return -2;
				}				
			}
			else //�������������������
				continue;
		}
	}
}