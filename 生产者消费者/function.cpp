#include <iostream>
#include "function.h"
using namespace std;

extern int fullNum;
extern int emptyNum;
void input_headline(int flag) { //此函数功能：输出开头一段提示信息
	cout << "生产者消费者题目(红色阻塞，绿色正常)" << endl;
	cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
	/*if (flag == 2)
	{
		cout << "此模式为可输入模式，就绪队列里已有若干生产者，用于对生产者消费者的基本理解" << endl;
		cout << "按一次回车键，模拟程序演示执行一步" << endl;
	}
	if (flag == 1)
	{
		cout << "此模式为不可输入模式，就绪队列里已有若干生产者和消费者，用于理解" << endl;
		cout << endl;
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);*/
}

void draw_buffer() { //此函数用于在屏幕上画出buffer框
	cct_gotoxy(2, 2);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "╔";
	for (int i = 0; i < MAX_BUFFER-1; ++i) {
		cout << " ═ "; 
		cout << "╦";
	}
	cout << " ═ ";
	cout << "╗ " << endl;
	cct_gotoxy(2, 3);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK); 
	for (int i = 0; i < MAX_BUFFER; ++i) {
		cout << "║   ";
	}
	cout << "║ " << endl;
	cct_gotoxy(2, 4);
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << "╚";
	for (int i = 0; i < MAX_BUFFER-1; ++i) {
		cout << " ═ ";
		cout << "╩";
	}
	cout << " ═ ";
	cout << "╝ " << endl << endl;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

