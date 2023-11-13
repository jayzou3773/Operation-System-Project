#include <iostream>
#include <Windows.h>
#include "console.h"
using namespace std;
#define MAX_BUFFER 20

//extern int fullNum;
//extern int emptyNum;

void draw_buffer() { //�˺�����������Ļ�ϻ���buffer��
	cct_gotoxy(2, 7);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "��";
	for (int i = 0; i < MAX_BUFFER - 1; ++i) {
		cout << " �� ";
		cout << "��";
	}
	cout << " �� ";
	cout << "�� " << endl;
	cct_gotoxy(2, 8);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	for (int i = 0; i < MAX_BUFFER; ++i) {
		cout << "��   ";
	}
	cout << "�� " << endl;
	cct_gotoxy(2, 9);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "��";
	for (int i = 0; i < MAX_BUFFER - 1; ++i) {
		cout << " �� ";
		cout << "��";
	}
	cout << " �� ";
	cout << "�� " << endl << endl;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}

void drawLeft() {
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	for (int j = 0; j < 6; ++j) {
		cct_gotoxy(0, j * 3);
		cout << "��";
		for (int i = 0; i < 8; ++i) {
			cout << "��";
		}
		cout << "��" << endl;   //ĩβ���꣨19,0��
		cout << "��";
		if (j == 0) {
			cout << "  �����ϼ�Ŀ¼  ";
		}
		else if (j == 1) {
			cout << "      ��      ";
		}
		else if (j == 2) {
			cout << "      �ر�      ";
		}
		else if (j == 3) {
			cout << "      ɾ��      ";
		}
		else if (j == 4) {
			cout << "    �½��ļ�    ";
		}
		else if (j == 5) {
			cout << "   �½��ļ���   ";
		}
		cout << "��" << endl;
		cout << "��";
		for (int i = 0; i < 8; ++i) {
			cout << "��";
		}
		cout << "��";
	}
	for (int i = 0; i < 9; ++i) {
		cct_gotoxy(0, 18 + i);
		cout << "                    "; //20���ո�
	}
	/*cct_gotoxy(0, 21);
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��" << endl;   //ĩβ���꣨19,0��
	cout << "��";
	cout << " �ϻ��Ҳ��ļ��� ";
	cout << "��" << endl;
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��" << endl;
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��" << endl;   //ĩβ���꣨19,0��
	cout << "��";
	cout << " �»��Ҳ��ļ��� ";
	cout << "��" << endl;
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��";*/
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
void padding() {
	cct_setcolor(COLOR_HWHITE, COLOR_HWHITE);
	for (int j = 3; j < 27; ++j) {
		cct_gotoxy(20, j);
		for (int i = 0; i < 12; ++i) {
			cout << "          "; //10���ո�
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
void drawHeadline() {
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(20, 0);
	cout << "��";
	for (int i = 0; i < 58; ++i) {
		cout << "��";
	}
	cout << "��";   //ĩβ���꣨159,0��
	cct_gotoxy(20, 1);
	cout << "��";
	cout << "��ǰĿ¼:       ";
	for (int i = 0; i < 10; ++i) {
		cout << "          "; //10���ո�
	}
	cout << "��";
	cct_gotoxy(20, 2);
	cout << "��";
	for (int i = 0; i < 58; ++i) {
		cout << "��";
	}
	cout << "��";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
void drawMiddle(int y) {
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cct_gotoxy(20, (y + 1) * 3);
	cout << "��";
	for (int i = 0; i < 58; ++i) {
		cout << "��";
	}
	cout << "��";   //ĩβ���꣨159,0��
	cct_gotoxy(20, (y + 1) * 3 + 1);
	cout << "��";
	cct_gotoxy(138, (y + 1) * 3 + 1);
	cout << "��";
	cct_gotoxy(20, (y + 1) * 3 + 2);
	cout << "��";
	for (int i = 0; i < 58; ++i) {
		cout << "��";
	}
	cout << "��";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
void drawRight() {
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	for (int j = 0; j < 3; ++j) {
		cct_gotoxy(140, j * 3);
		cout << "��";
		for (int i = 0; i < 8; ++i) {
			cout << "��";
		}
		cout << "��";   //ĩβ���꣨159,0��
		cct_gotoxy(140, j * 3 + 1);
		cout << "��";
		if (j == 0) {
			cout << "      X��       ";
		}
		else if (j == 1) {
			cout << "      Y��       ";
		}
		else if (j == 2) {
			cout << "      Z��       ";
		}
		cout << "��";
		cct_gotoxy(140, j * 3 + 2);
		cout << "��";
		for (int i = 0; i < 8; ++i) {
			cout << "��";
		}
		cout << "��";
	}
	for (int i = 0; i < 18; ++i) {
		cct_gotoxy(140, 9 + i);
		cout << "                    "; //20���ո�
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
void drawAttribute() {
	cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
	cct_gotoxy(0, 27);
	for (int i = 0; i < 80; ++i) {
		cout << "��";
	}
	cct_gotoxy(0, 28);
	cout << " �·�Ϊ�ı������:";
	for (int i = 0; i < 15; ++i) {
		cout << "          "; //10���ո�
	}
	cct_gotoxy(0, 29);
	for (int i = 0; i < 80; ++i) {
		cout << "��";
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
void drawTextField() {
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cct_gotoxy(0, 30);
	for (int i = 0; i < 80; ++i) {
		cout << "��";
	}
	for (int j = 0; j < 7; ++j) {
		cct_gotoxy(0, 31 + j);
		for (int i = 0; i < 16; ++i) {
			cout << "          "; //10���ո�
		}
		cout << endl;
	}
	cct_gotoxy(0, 38);
	for (int i = 0; i < 80; ++i) {
		cout << "��";
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}
int clickLocation(int x, int y) {
	if (x >= 1 && x <= 18) {
		if (y >= 0 && y <= 2) {
			return 0;
		}
		else if (y >= 3 && y <= 5) {
			//return 140;
			return 3;
		}
		else if (y >= 6 && y <= 8) {
			//return 143;
			return 6;
		}
		else if (y >= 9 && y <= 11) {
			//return 146;
			return 9;
		}
		else if (y >= 12 && y <= 14) {
			return 12;
		}
		else if (y >= 15 && y <= 17) {
			return 15;
		}
		//else if (y >= 21 && y <= 23) {
			//return 21;
		//}
		//else if (y >= 24 && y <= 26) {
			//return 24;
		//}
		else {
			return -3;
		}
	}
	else if (x >= 141 && x <= 158) {
		if (y >= 0 && y <= 2) {
			//return 3;
			return 140;
		}
		else if (y >= 3 && y <= 5) {
			//return 6;
			return 143;
		}
		else if (y >= 6 && y <= 8) {
			//return 9;
			return 146;
		}
		//else if (y >= 9 && y <= 11) {
		//	return 149;
		//}
		//else if (y >= 12 && y <= 14) {
		//	return 152;
		//}
		else {
			return -3;
		}
	}
	else if (x >= 21 && x <= 138 && y >= 3 && y <= 26) {
		return 200 + y / 3;
	}
	else {
		return -3;
	}
}
void especiallyShow(int xy) {
	int x = -1;
	int y = -1;
	int xMouse = -1;
	int yMouse = -1;
	cct_getxy(xMouse, yMouse);
	if (0 <= xy && xy <= 24) {
		x = 0;
		y = xy;
	}
	else if (140 <= xy && xy <= 158) {
		x = 140;
		y = xy - 140;
	}
	cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
	cct_gotoxy(x, y);
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��";
	cct_gotoxy(x, y + 1);
	cout << "��";
	for (int i = 0; i < 16; ++i) {
		cout << ' ';
	}
	//cct_gotoxy(x + 18, y + 1);
	cout << "��";
	cct_gotoxy(x, y + 2);
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��";
	Sleep(200);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(x, y);
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��";
	cct_gotoxy(x, y + 1);
	cout << "��";
	for (int i = 0; i < 16; ++i) {
		cout << ' ';
	}
	//cct_gotoxy(x + 18, y + 1);
	cout << "��";
	cct_gotoxy(x, y + 2);
	cout << "��";
	for (int i = 0; i < 8; ++i) {
		cout << "��";
	}
	cout << "��";
	if (0 <= xy && xy <= 24) {
		drawLeft();
	}
	else if (140 <= xy && xy <= 158) {
		drawRight();
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(xMouse, yMouse);
}
void selectFile(int state) {
	cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
	cct_gotoxy(20, state * 3);
	cout << "��";
	for (int i = 0; i < 58; ++i) {
		cout << "��";
	}
	cout << "��";   //ĩβ���꣨159,0��
	cct_gotoxy(20, state * 3 + 1);
	cout << "��";
	cct_gotoxy(138, state * 3 + 1);
	cout << "��";
	cct_gotoxy(20, state * 3 + 2);
	cout << "��";
	for (int i = 0; i < 58; ++i) {
		cout << "��";
	}
	cout << "��";
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 31);
}