#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <windows.h>
#include "function.h"
#include "conio.h"
using namespace std;

struct Process {//进程
	bool state;    //进程状态，阻塞为false，就绪或执行为true
	string address;//被阻塞到哪个信号量阻塞队列
	string PID;    //进程标识符
	Process(string pid, bool a = true, string b = "\0") {
		PID = pid;
		state = a;
		address = b;
	}
};
struct Buffer {//缓冲区单元
	int num;      //缓冲区单元存储的数字
	string biaohao; //操作缓冲区单元的进程标号
	Buffer(int a = 0, string b = "\0") {
		num = a;
		biaohao = b;
	}
};
unordered_map<int, Process*> producer;//生产者进程P1-P5分别用数字1-5进行映射
unordered_map<int, Process*> consumer;//消费者进程C1-C5分别用数字1-5进行映射
unordered_map<int, queue<string>*> S; //阻塞队列S1-S5分别用数字1-5进行映射
//缓冲区空信号量
int empty_number = 20;    
queue<string> Empty;  
//缓冲区为满的信号量
int full_number = 0;      
queue<string> Full;   
//互斥信号量
int mutex = 1;        
queue<string> Mutex;  
int sindex[5] = { 0 };

Process P1("P1"), C1("C1"), P2("P2"), C2("C2"), P3("P3"), C3("C3"), P4("P4"), C4("C4"), P5("P5"), C5("C5");
//记录当前被从阻塞队列中重新唤醒的进程数量
int reawake = 0;      

Buffer buffer[20];     //用数组表示缓冲区
queue<string> readyqueue;   //就绪队列
queue<int> readyqueue_level; //就绪队列中各进程的信号量
queue<string> temp; //中间队列

queue<string> S1, S2, S3, S4, S5;//信号量s1-s5对应的5个阻塞队列
template <typename T>
void ReSort(queue<T>* q) {   //队列重排序，把队列中的最后一个进程提到最前面
	queue<T> tmp;
	if ((*q).size() < 2) {   //如果队列中只有一个或没有元素，重不重新排序效果一样
		return;
	}
	else {
		tmp.push((*q).back());      //先在新队列压入最后一个元素
		while ((*q).size() > 1) {   //然后再按照原队列元素顺序将各元素压入新队列
			tmp.push((*q).front());
			(*q).pop();
		}
		(*q).pop();
		while (!tmp.empty()) {      //相当于把排好序的中间队列复制给原队列
			(*q).push(tmp.front());
			tmp.pop();
		}
	}
}

string P(int* flag, queue<string>* q,string q_name,Process* process,int level) {//模拟P原语
	if (readyqueue_level.front() <= level) {      //此处level变量的意义：例如:进程A被阻塞在empty信号量的阻塞队列,执行P(mutex)
		(*flag) -= 1;                       
	}                                       
	if ((*flag) < 0 && readyqueue_level.front()<=level) {
		(*q).push((*process).PID);          
		readyqueue.pop();               
		readyqueue_level.pop();          
		(*process).state = false;   
		(*process).address = q_name;
		return (*process).PID;      
	}
	else { //当信号量≥0,该进程继续执行
		return "\0";
	}
}

string V(int* flag, queue<string>* q, queue<string>* qnext,int level) { //模拟V原语
	(*flag) += 1;
	if ((*flag) <= 0) {           
		string tmp = (*q).front(); 
		(*qnext).push(tmp);        
		readyqueue_level.push(level + 1);
		ReSort<string>(&readyqueue);   
		ReSort<int>(&readyqueue_level);
		++reawake;                
		(*q).pop();
		for (int i = 0; i < 5; ++i) {        
			if (tmp == producer[i]->PID) {
				producer[i]->address = "\0"; 
				producer[i]->state = true;   
				return tmp;
			}
		}
		for (int i = 0; i < 5; ++i) {
			if (tmp == consumer[i]->PID) {
				consumer[i]->address = "\0";  
				consumer[i]->state = true;    
				return tmp;
			}
		}
		return tmp;
	}
	else { //若信号量>0，该进程继续执行
		return "\0";
	}
}

void PAction(int index,int* si,int flag) {//执行生产者进程
	if (P(&empty_number, &Empty, "Empty", producer[index],0) == "\0") {  //P(empty)
		if (P(&mutex, &Mutex, "Mutex", producer[index],2) == "\0") { //P(mutex)
			for (int i = 0; i < 20; ++i) {//对buffer数组中的数据进行更新
				if (buffer[i].num == 0) {
					buffer[i].num = i + 1;
					buffer[i].biaohao = producer[index]->PID;
					if (flag == 1||flag==0)//黄色三角形指示当前buffer位置
					{
						cct_setcursor(CURSOR_INVISIBLE);
						cct_gotoxy(4 * (i + 1), 1);
						cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
						cout << "▼";
						if (flag == 1)
							Sleep(350);
						else
							Sleep(700);
						
						cct_gotoxy(4 * (i + 1), 1);
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cout << "  ";
					}
					readyqueue.pop();      //一个进程被执行完
					readyqueue_level.pop();
					break;
				}
			}
			V(&mutex, &Mutex, &readyqueue,2);//V(mutex)
			V(si, S[index], &readyqueue, 1); //V(Si)
			V(&full_number, &Full,&readyqueue,0);//V(full)
		}
	}
}

void CAction(int index, int* si,int flag) {//执行消费者进程
	if (P(&full_number, &Full, "Full", consumer[index],0) == "\0") {  //P(full)
		if (P(si, S[index], "S" + to_string(index + 1), consumer[index], 1) == "\0") {  //P(Si)
			if (P(&mutex, &Mutex, "Mutex", consumer[index], 2) == "\0") {   //P(mutex)
				for (int i = 0; i < 20; ++i) {  //对buffer数组中的数据进行更新
					if (buffer[i].biaohao == "P"+to_string(index+1)) {
						buffer[i].num = 0;
						buffer[i].biaohao = "\0";
						if (flag == 1||flag==0)////黄色三角形指示当前buffer位置
						{
							cct_setcursor(CURSOR_INVISIBLE);
							cct_gotoxy(4 * (i + 1), 1);
							cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
							cout << "▼";
							if (flag == 1)
								Sleep(350);
							else
								Sleep(1500);
							
							cct_gotoxy(4 * (i + 1), 1);
							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cout << "  ";
						}
						readyqueue.pop();       
						readyqueue_level.pop();
						break;
					}
				}
				V(&mutex, &Mutex,&readyqueue,2);    //V(mutex)
				V(&empty_number, &Empty,&readyqueue,0); //V(empty)
			}
		}
	}
}

void Push(string pname) { //将就绪的进程压入就绪队列
	readyqueue.push(pname);
	readyqueue_level.push(0);
}
void user_input() {  //此函数用于使得用户能够通过输入进程标识符在就绪队列中新增进程
	while (1) {       //同时检查用户是否输入了有效合法的进程标识名
		cct_gotoxy(0,20 + readyqueue.size() / 18);
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 100; ++j) {
				cout << ' ';
			}
		}
		cct_gotoxy(0,20 + readyqueue.size() / 18);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cout << "加入进程输入(P1-P5,C1-C5)" << endl;
		cout << "按回车进行下一步" << endl;
		cout << "若您输入了不存在的进程名,则程序不会响应,当就绪队列为空时程序结束:";
		//******************************************
		string tmpName = "\0";
		getline(cin, tmpName);
		if (tmpName.length() == 0) {//此情况说明用户不需要再输入内容，直接敲击了回车键
			return ;
		}
		else {  //无效输入
            if (tmpName.length() != 2 || (tmpName[0] != 'P' && tmpName[0] != 'C') || tmpName[1] < '1' || tmpName[1] > '5') {
				cct_gotoxy(strlen("若您输入了不存在的进程名,则程序不会响应,当就绪队列为空时程序结束:"), 17 + readyqueue.size() / 18);
				for (int i = 0; i < tmpName.length(); i++)
				{
					cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
					cout << " ";
				}
				continue;
			}
			else { //正确输入
				readyqueue.push(tmpName); 
				readyqueue_level.push(0);  
				buffer_paint();     //更新屏幕上的buffer画面
				continue;
			}
		}
	}
}
void buffer_paint() { 
	for (int i = 0; i < 20; ++i) {               
		if (empty_number >= 0 && full_number >= 0) {
			cct_setcolor(COLOR_HWHITE, COLOR_HGREEN);
		}
		else {
			cct_setcolor(COLOR_HWHITE, COLOR_HRED);
		}
		cct_gotoxy(4 * (i + 1), 3);
		if (buffer[i].num == 0) {
			cout << "  ";
		}
		else {
			cout << buffer[i].num;
		}
		if (empty_number >= 0 && full_number >= 0) {
			cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
		}
		else {
			cct_setcolor(COLOR_BLACK, COLOR_HRED);
		}
		cct_gotoxy(4 * (i + 1), 5);
		if (buffer[i].biaohao == "\0") {
			cout << "  ";
		}
		else {
			cout << buffer[i].biaohao;
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_gotoxy(0, 6);
	for (unsigned int i = 0; i < 14+readyqueue.size()/18; ++i) {
		for (int j = 0; j < 100; ++j) {
			cout << ' ';
		}
		cout << endl;
	}
	cct_gotoxy(0, 6);
	cout << "各信号量阻塞队列情况:";
	if (reawake>0) {
		cct_setcolor(COLOR_BLACK, COLOR_HBLUE);
		cout << "(被唤醒的进程将在下一步继续执行，未对齐的信号量将在此进程完成后对齐)";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		--reawake;
	}
	cout<< endl;
	cct_setcolor(COLOR_HRED, COLOR_WHITE);
	cout << "full: " << full_number << "   阻塞进程: ";
	temp = Full;
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cct_setcolor(COLOR_HBLUE, COLOR_WHITE);
	cout << "empty: " << empty_number << "   阻塞进程: ";
	temp = Empty;
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cct_setcolor(COLOR_HYELLOW, COLOR_WHITE);
	cout << "mutex: " << mutex ;
	temp = Mutex;
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	while (!temp.empty()) {
		temp.pop();
	}
	cout << endl;
	cout << "s1: " ;
	temp = (*S[0]);
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cout << "s2: " ;
	temp = (*S[1]);
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cout << "s3: " ;
	temp = (*S[2]);
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cout << "s4: " ;
	temp = (*S[3]);
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cout << "s5: " ;
	temp = (*S[4]);
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cout << "就绪进程队列:"<<endl;
	temp = readyqueue;
	int amount = 1;
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
		if (amount % 10 == 0) {
			cout << endl;
		}
		++amount;
	}
	amount = 1;
	cout << endl;
}

void Run() { //按序执行就绪队列中的进程
	while (!readyqueue.empty()) {  //只要就绪队列不空，就一直执行
		buffer_paint();    //更新buffer画面
		user_input();      //和用户交互
		string tmp = readyqueue.front();
		if (tmp[0] == 'P') {     //执行生产者进程
			for (int i = 0; i < 5; ++i) {
				if (tmp == producer[i]->PID) {
					PAction(i, &sindex[i],1);
					break;
				}
			}
		}
		else if (tmp[0] == 'C') { //执行消费者进程
			for (int i = 0; i < 5; ++i) {
				if (tmp == consumer[i]->PID) {
					CAction(i, &sindex[i],1);
					break;
				}
			}
		}
		else {
			cout << "未声明进程" << endl;
			break;
		}
	}
	buffer_paint(); //更新buffer画面
	user_input();
}
void run()
{
	while (!readyqueue.empty()) {  //只要就绪队列不空，就一直执行
		buffer_paint();    //更新buffer画面     
		string tmp = readyqueue.front();
		if (tmp[0] == 'P') {     //执行生产者进程
			for (int i = 0; i < 5; ++i) {
				if (tmp == producer[i]->PID) {
					PAction(i, &sindex[i], 0);
					break;
				}
			}
		}
		else if (tmp[0] == 'C') { //执行消费者进程
			for (int i = 0; i < 5; ++i) {
				if (tmp == consumer[i]->PID) {
					CAction(i, &sindex[i], 0);
					break;
				}
			}
		}
		else {
			cout << "未声明进程" << endl;
			break;
		}
	}
	buffer_paint(); //更新buffer画面
}

int main() {
	producer[0] = &P1;
	producer[1] = &P2;
	producer[2] = &P3;
	producer[3] = &P4;
	producer[4] = &P5;
	consumer[0] = &C1;
	consumer[1] = &C2;
	consumer[2] = &C3;
	consumer[3] = &C4;
	consumer[4] = &C5;
	S[0] = &S1;
	S[1] = &S2;
	S[2] = &S3;
	S[3] = &S4;
	S[4] = &S5;
	int enter;
	while (1){
		int choice = menu();
		for (int i = 0; i < 20; i++) {
			buffer[i].num = 0;
			buffer[i].biaohao = '\0';
		}
		if (choice == 1) {
			cct_cls();
			input_headline(1);
			draw_buffer();
			Push("C1");
			Push("P1");
			Push("C2");
			Push("P2");
			Push("C1");
			Push("C2");
			Push("P2");
			Push("P1");
			for (int i = 0; i < 20; ++i) {
				Push("P2");
			}
			Push("P3");
			Push("C2");
			Push("P2");
			Push("C2");
			Push("C2");
			Push("C2");
			Push("C2");
			Push("P2");
			Push("C2");
			run();
			cout << endl;
			cout << "按回车键继续";
			while (1) {
				if (enter = _getch() == 13)
				{
					cct_cls();
					break;
				}
			}
		}
		else if (choice == 2) {
			cct_cls();
			input_headline(2);
			draw_buffer();
			Push("C1");
			Push("P1");
			Push("C2");
			Push("P2");
			Push("C1");
			Push("C2");
			Push("P2");
			Push("P1");
			for (int i = 0; i < 20; ++i) {
				Push("P2");
			}
			Push("P3");
			Push("C2");
			Push("P2");
			Push("C2");
			Push("C2");
			Push("C2");
			Push("C2");
			Push("P2");
			Push("C2");
			Run();//按照PV机制执行就绪队列中的进程
			cout << endl;
			cout << "按回车键继续";
			while (1) {
				if (enter = _getch() == 13)
				{
					cct_cls();
					break;
				}
			}
		}
		else if (choice == 0)
			break;
		cct_cls();
	}
	system("pause");

	return 0;
}