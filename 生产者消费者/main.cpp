#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <windows.h>
#include "function.h"
#include "conio.h"
using namespace std;

struct Process {//����
	bool state;    //����״̬������Ϊfalse��������ִ��Ϊtrue
	string address;//���������ĸ��ź�����������
	string PID;    //���̱�ʶ��
	Process(string pid, bool a = true, string b = "\0") {
		PID = pid;
		state = a;
		address = b;
	}
};
struct Buffer {//��������Ԫ
	int num;      //��������Ԫ�洢������
	string biaohao; //������������Ԫ�Ľ��̱��
	Buffer(int a = 0, string b = "\0") {
		num = a;
		biaohao = b;
	}
};
unordered_map<int, Process*> producer;//�����߽���P1-P5�ֱ�������1-5����ӳ��
unordered_map<int, Process*> consumer;//�����߽���C1-C5�ֱ�������1-5����ӳ��
unordered_map<int, queue<string>*> S; //��������S1-S5�ֱ�������1-5����ӳ��
//���������ź���
int empty_number = 20;    
queue<string> Empty;  
//������Ϊ�����ź���
int full_number = 0;      
queue<string> Full;   
//�����ź���
int mutex = 1;        
queue<string> Mutex;  
int sindex[5] = { 0 };

Process P1("P1"), C1("C1"), P2("P2"), C2("C2"), P3("P3"), C3("C3"), P4("P4"), C4("C4"), P5("P5"), C5("C5");
//��¼��ǰ�����������������»��ѵĽ�������
int reawake = 0;      

Buffer buffer[20];     //�������ʾ������
queue<string> readyqueue;   //��������
queue<int> readyqueue_level; //���������и����̵��ź���
queue<string> temp; //�м����

queue<string> S1, S2, S3, S4, S5;//�ź���s1-s5��Ӧ��5����������
template <typename T>
void ReSort(queue<T>* q) {   //���������򣬰Ѷ����е����һ�������ᵽ��ǰ��
	queue<T> tmp;
	if ((*q).size() < 2) {   //���������ֻ��һ����û��Ԫ�أ��ز���������Ч��һ��
		return;
	}
	else {
		tmp.push((*q).back());      //�����¶���ѹ�����һ��Ԫ��
		while ((*q).size() > 1) {   //Ȼ���ٰ���ԭ����Ԫ��˳�򽫸�Ԫ��ѹ���¶���
			tmp.push((*q).front());
			(*q).pop();
		}
		(*q).pop();
		while (!tmp.empty()) {      //�൱�ڰ��ź�����м���и��Ƹ�ԭ����
			(*q).push(tmp.front());
			tmp.pop();
		}
	}
}

string P(int* flag, queue<string>* q,string q_name,Process* process,int level) {//ģ��Pԭ��
	if (readyqueue_level.front() <= level) {      //�˴�level���������壺����:����A��������empty�ź�������������,ִ��P(mutex)
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
	else { //���ź�����0,�ý��̼���ִ��
		return "\0";
	}
}

string V(int* flag, queue<string>* q, queue<string>* qnext,int level) { //ģ��Vԭ��
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
	else { //���ź���>0���ý��̼���ִ��
		return "\0";
	}
}

void PAction(int index,int* si,int flag) {//ִ�������߽���
	if (P(&empty_number, &Empty, "Empty", producer[index],0) == "\0") {  //P(empty)
		if (P(&mutex, &Mutex, "Mutex", producer[index],2) == "\0") { //P(mutex)
			for (int i = 0; i < 20; ++i) {//��buffer�����е����ݽ��и���
				if (buffer[i].num == 0) {
					buffer[i].num = i + 1;
					buffer[i].biaohao = producer[index]->PID;
					if (flag == 1||flag==0)//��ɫ������ָʾ��ǰbufferλ��
					{
						cct_setcursor(CURSOR_INVISIBLE);
						cct_gotoxy(4 * (i + 1), 1);
						cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
						cout << "��";
						if (flag == 1)
							Sleep(350);
						else
							Sleep(700);
						
						cct_gotoxy(4 * (i + 1), 1);
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cout << "  ";
					}
					readyqueue.pop();      //һ�����̱�ִ����
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

void CAction(int index, int* si,int flag) {//ִ�������߽���
	if (P(&full_number, &Full, "Full", consumer[index],0) == "\0") {  //P(full)
		if (P(si, S[index], "S" + to_string(index + 1), consumer[index], 1) == "\0") {  //P(Si)
			if (P(&mutex, &Mutex, "Mutex", consumer[index], 2) == "\0") {   //P(mutex)
				for (int i = 0; i < 20; ++i) {  //��buffer�����е����ݽ��и���
					if (buffer[i].biaohao == "P"+to_string(index+1)) {
						buffer[i].num = 0;
						buffer[i].biaohao = "\0";
						if (flag == 1||flag==0)////��ɫ������ָʾ��ǰbufferλ��
						{
							cct_setcursor(CURSOR_INVISIBLE);
							cct_gotoxy(4 * (i + 1), 1);
							cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
							cout << "��";
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

void Push(string pname) { //�������Ľ���ѹ���������
	readyqueue.push(pname);
	readyqueue_level.push(0);
}
void user_input() {  //�˺�������ʹ���û��ܹ�ͨ��������̱�ʶ���ھ�����������������
	while (1) {       //ͬʱ����û��Ƿ���������Ч�Ϸ��Ľ��̱�ʶ��
		cct_gotoxy(0,20 + readyqueue.size() / 18);
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 100; ++j) {
				cout << ' ';
			}
		}
		cct_gotoxy(0,20 + readyqueue.size() / 18);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cout << "�����������(P1-P5,C1-C5)" << endl;
		cout << "���س�������һ��" << endl;
		cout << "���������˲����ڵĽ�����,����򲻻���Ӧ,����������Ϊ��ʱ�������:";
		//******************************************
		string tmpName = "\0";
		getline(cin, tmpName);
		if (tmpName.length() == 0) {//�����˵���û�����Ҫ���������ݣ�ֱ���û��˻س���
			return ;
		}
		else {  //��Ч����
            if (tmpName.length() != 2 || (tmpName[0] != 'P' && tmpName[0] != 'C') || tmpName[1] < '1' || tmpName[1] > '5') {
				cct_gotoxy(strlen("���������˲����ڵĽ�����,����򲻻���Ӧ,����������Ϊ��ʱ�������:"), 17 + readyqueue.size() / 18);
				for (int i = 0; i < tmpName.length(); i++)
				{
					cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
					cout << " ";
				}
				continue;
			}
			else { //��ȷ����
				readyqueue.push(tmpName); 
				readyqueue_level.push(0);  
				buffer_paint();     //������Ļ�ϵ�buffer����
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
	cout << "���ź��������������:";
	if (reawake>0) {
		cct_setcolor(COLOR_BLACK, COLOR_HBLUE);
		cout << "(�����ѵĽ��̽�����һ������ִ�У�δ������ź������ڴ˽�����ɺ����)";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		--reawake;
	}
	cout<< endl;
	cct_setcolor(COLOR_HRED, COLOR_WHITE);
	cout << "full: " << full_number << "   ��������: ";
	temp = Full;
	while (!temp.empty()) {
		cout << temp.front() << "  ";
		temp.pop();
	}
	cout << endl;
	cct_setcolor(COLOR_HBLUE, COLOR_WHITE);
	cout << "empty: " << empty_number << "   ��������: ";
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
	cout << "�������̶���:"<<endl;
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

void Run() { //����ִ�о��������еĽ���
	while (!readyqueue.empty()) {  //ֻҪ�������в��գ���һֱִ��
		buffer_paint();    //����buffer����
		user_input();      //���û�����
		string tmp = readyqueue.front();
		if (tmp[0] == 'P') {     //ִ�������߽���
			for (int i = 0; i < 5; ++i) {
				if (tmp == producer[i]->PID) {
					PAction(i, &sindex[i],1);
					break;
				}
			}
		}
		else if (tmp[0] == 'C') { //ִ�������߽���
			for (int i = 0; i < 5; ++i) {
				if (tmp == consumer[i]->PID) {
					CAction(i, &sindex[i],1);
					break;
				}
			}
		}
		else {
			cout << "δ��������" << endl;
			break;
		}
	}
	buffer_paint(); //����buffer����
	user_input();
}
void run()
{
	while (!readyqueue.empty()) {  //ֻҪ�������в��գ���һֱִ��
		buffer_paint();    //����buffer����     
		string tmp = readyqueue.front();
		if (tmp[0] == 'P') {     //ִ�������߽���
			for (int i = 0; i < 5; ++i) {
				if (tmp == producer[i]->PID) {
					PAction(i, &sindex[i], 0);
					break;
				}
			}
		}
		else if (tmp[0] == 'C') { //ִ�������߽���
			for (int i = 0; i < 5; ++i) {
				if (tmp == consumer[i]->PID) {
					CAction(i, &sindex[i], 0);
					break;
				}
			}
		}
		else {
			cout << "δ��������" << endl;
			break;
		}
	}
	buffer_paint(); //����buffer����
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
			cout << "���س�������";
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
			Run();//����PV����ִ�о��������еĽ���
			cout << endl;
			cout << "���س�������";
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