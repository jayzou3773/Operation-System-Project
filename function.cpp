#include <iostream>
#include "function.h"
using namespace std;

extern int fullNum;
extern int emptyNum;
void input_headline(int flag) { //�˺������ܣ������ͷһ����ʾ��Ϣ
	cout << "��������������Ŀ(��ɫ��������ɫ����)" << endl;
	cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
	/*if (flag == 2)
	{
		cout << "��ģʽΪ������ģʽ�������������������������ߣ����ڶ������������ߵĻ������" << endl;
		cout << "��һ�λس�����ģ�������ʾִ��һ��" << endl;
	}
	if (flag == 1)
	{
		cout << "��ģʽΪ��������ģʽ�������������������������ߺ������ߣ��������" << endl;
		cout << endl;
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);*/
}

void draw_buffer() { //�˺�����������Ļ�ϻ���buffer��
	cct_gotoxy(2, 2);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "�X";
	for (int i = 0; i < MAX_BUFFER-1; ++i) {
		cout << " �T "; 
		cout << "�j";
	}
	cout << " �T ";
	cout << "�[ " << endl;
	cct_gotoxy(2, 3);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK); 
	for (int i = 0; i < MAX_BUFFER; ++i) {
		cout << "�U   ";
	}
	cout << "�U " << endl;
	cct_gotoxy(2, 4);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "�^";
	for (int i = 0; i < MAX_BUFFER-1; ++i) {
		cout << " �T ";
		cout << "�m";
	}
	cout << " �T ";
	cout << "�a " << endl << endl;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

