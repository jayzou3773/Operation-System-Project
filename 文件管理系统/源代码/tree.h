#pragma once
#include <iostream>
#include <string>
#include <direct.h>
#include <io.h>
using namespace std;
#define KID 0 //�궨������������Ϊ0
#define BROTHER 1 //�궨������������Ϊ1

struct FCB {
	string fileName;
	int index;
	int length;
	string address;

	FCB(string a, int b = -1, int c = 0,string d = "C:\\2151601") {
		fileName = a;
		index = b;
		length = c;
		address = d;
	}
};


class TreeNode//���ڵ���
{
private:
	FCB data;
	TreeNode* LeftNode, * RightNode, * Parent;
public:
	TreeNode(FCB item, TreeNode* parent = NULL, TreeNode* left = NULL, TreeNode* right = NULL) :data(item), Parent(parent), LeftNode(left), RightNode(right) {}
	string GetFCBFileName() { return data.fileName; }//���ؽڵ㱾���������Ϣ
	string GetFCBAddress() { return data.address; }//���ؽڵ㱾���������Ϣ
	int GetFCBIndex() { return data.index; }
	int GetFCBLength() { return data.length; }
	TreeNode* GetParent() { return Parent; }//��ȡ��ǰ�ڵ�ĸ��ڵ�
	TreeNode* GetLeft() { return LeftNode; }//��ȡ��ǰ�ڵ�����ӽڵ�
	TreeNode* GetRight() { return RightNode; }//��ȡ��ǰ�ڵ�����ӽڵ�
	void SetData(string a, int b, int c, string d) { data.fileName = a; data.index = b; data.length = c; data.address = d; }//�趨��ǰ�ڵ������
	void SetDataIndex(int a) { data.index = a; }
	void SetDataLength(int a) { data.length = a; }
	void SetDataFileName(string a) { data.fileName = a; }
	void SetParent(TreeNode* parent) { Parent = parent; }//�趨��ǰ�ڵ�ĸ��ڵ�
	void SetLeft(TreeNode* left = NULL) { LeftNode = left; }//�趨��ǰ�ڵ�����ӽڵ�
	void SetRight(TreeNode* right = NULL) { RightNode = right; }//�趨��ǰ�ڵ�����ӽڵ�
};

class BinaryTree//��������
{
private:
	TreeNode* root, * current;//���ڵ㡢��ǰ�ڵ�
public:
	BinaryTree(FCB value)//���캯��
	{
		root = current = new TreeNode(value);
	}
	~BinaryTree() { destroy(root); }//��������
	TreeNode* GetRoot()//��ȡ���ڵ�
	{
		if (root == NULL)
			return NULL;
		return root;
	}
	TreeNode* Insert(FCB item, int direction, TreeNode* location);//�ڵ�ǰ�ڵ������ҷ������ֵΪitem�����ӽڵ�
	TreeNode* FindTarget(string name, TreeNode* start);//��startλ�ÿ�ʼѰ��ֵΪitem�ĵ�һ���ڵ�
	TreeNode* FindParent(TreeNode* node)//Ѱ��node�ڵ�����������ϵĸ�ĸ��ע���븸�ڵ������
	{
		if (node == NULL && current != NULL)//�趨����Ĭ�ϵĲ���
			node = current;
		if ((node == NULL && current == NULL) || node == root)//�����ڸ��ڵ�����
			return NULL;
		else
		{
			while (node->GetParent()->GetLeft() != node)//ֻҪû�ҵ���һֱ���Ͽ���
			{
				if (node->GetParent() == NULL)//�����ڸ��ڵ�����
					return NULL;
				else
					node = node->GetParent();//û�ҵ��ͼ�������Ѱ��
			}
			current = node->GetParent();//ע��ѭ����������
			return current;//���ظ��ڵ��ַ
		}
	}
	void ForwardTravel(TreeNode* start);//ǰ�����������
	void MiddleTravel(TreeNode* start);//�������������
	void BackwardTravel(TreeNode* start);//��������������
	TreeNode* GetParent(TreeNode* location)
	{
		if (location == NULL || location == root || location->GetParent() == NULL)//���ڵ㲻���ڵ����
			return NULL;
		return location->GetParent();//���ظ��ڵ�
	}
	int Brother(TreeNode* location);//���location�ڵ�����������ֵܣ��˴���NOT_SHOW���ڵ������ʱ�����ĳЩ�ַ�
	int Kid(TreeNode* location)//���location�ڵ������������Ů
	{
		int count = 0;
		if (location == NULL || location->GetLeft() == NULL)//����Ů�����
		{
			//cout << "����Ů" << endl;
			return 0;
		}
		else
		{
			/*cout << location->GetLeft()->GetFCBFileName()<< ' '
				<< location->GetLeft()->GetFCBIndex() << ' '
				<< location->GetLeft()->GetFCBLength() << ' '
				<< location->GetLeft()->GetFCBAddress() << endl;*/
			count = 1;
			if (location->GetLeft()->GetRight() != NULL) {//��һ����Ů�ڵ���ҷ����ֵܽڵ����������Ů���ڵ�λ��
				count += Brother(location->GetLeft());
			}
			return count;
		}
	}
	TreeNode* GetTargetSon(TreeNode* location, int num) {
		int count = 0;
		if (location == NULL || location->GetLeft() == NULL) {//����Ů�����
			return NULL;
		}
		else{
			count = 1;
			if (num == count) {
				return location->GetLeft();
			}
			else if (location->GetLeft()->GetRight() != NULL) {//��һ����Ů�ڵ���ҷ����ֵܽڵ����������Ů���ڵ�λ��
				location = location->GetLeft();
				while (location->GetRight() != NULL)//������֦������
				{
					location = location->GetRight();
					++count;
					if (count == num) {
						return location;
					}
					continue;
				}
			}
			return NULL;
		}
	}
	void destroy(TreeNode* location);//����ɾ��location�����к��
	void kill(TreeNode* location)//����ɾ���ض���Ҷ�ڵ���߹����ڵ�
	{
		if (location != root)
		{
			if (location->GetParent()->GetLeft() == location) {
				location->GetParent()->SetLeft(location->GetRight());//SetLeft�޲�����ʹ��Ĭ�ϲ���NULL���������丸�ڵ�����ӽڵ�ָ��NULL
				if(location->GetRight()!= NULL)
				    location->GetRight()->SetParent(location->GetParent());
			}
			else {
				location->GetParent()->SetRight(location->GetRight());
				if (location->GetRight() != NULL)
				    location->GetRight()->SetParent(location->GetParent());
			}
		}
		delete location;//�ͷŸ�Ҷ�ڵ���ռ�Ŀռ�
	}
};
void BinaryTree::destroy(TreeNode* location)//ɾ����locationΪ���ڵ����
{
	if (location != NULL)//�൱���ú��������������ͷŸ��ڵ���ռ�õ��ڴ�ռ�
	{
		destroy(location->GetLeft());
		destroy(location->GetRight());
		if (location != root)
		{
			if (location->GetParent()->GetLeft() == location)
				location->GetParent()->SetLeft();//SetLeft�޲�����ʹ��Ĭ�ϲ���NULL���������丸�ڵ�����ӽڵ�ָ��NULL����ͬ
			else
				location->GetParent()->SetRight();
		}
		//if (location->GetParent()->GetLeft() == location) {
		//	location->GetParent()->SetLeft(location->GetRight());//SetLeft�޲�����ʹ��Ĭ�ϲ���NULL���������丸�ڵ�����ӽڵ�ָ��NULL
		//	location->GetRight()->SetParent(location->GetParent());
		//}
		//else {
		//	location->GetParent()->SetRight(location->GetRight());
		//	location->GetRight()->SetParent(location->GetParent());
		//}
		delete location;
	}
}
void BinaryTree::MiddleTravel(TreeNode* start)//���������NOT_SHOW���ڿ������ʱ�����ĳЩ�����ڴ��ڵ�����
{
	if (start != NULL)//�ݹ�˼·
	{
		MiddleTravel(start->GetLeft());
		cout << start->GetFCBFileName() << ' ' << start->GetFCBIndex() << ' ' << start->GetFCBLength() << ' ' << start->GetFCBAddress() << endl;
		MiddleTravel(start->GetRight());
	}
}
void BinaryTree::ForwardTravel(TreeNode* start)//ǰ�������NOT_SHOW���ڿ������ʱ�����ĳЩ�����ڴ��ڵ�����
{
	if (start != NULL)//�ݹ�˼·
	{
		cout << start->GetFCBFileName() << ' ' << start->GetFCBIndex() << ' ' << start->GetFCBLength() << ' ' << start->GetFCBAddress() << endl;
		ForwardTravel(start->GetLeft());
		ForwardTravel(start->GetRight());
	}
}
void BinaryTree::BackwardTravel(TreeNode* start)//���������NOT_SHOW���ڿ������ʱ�����ĳЩ�����ڴ��ڵ�����
{
	if (start != NULL)//�ݹ�˼·
	{
		BackwardTravel(start->GetLeft());
		BackwardTravel(start->GetRight());
		cout << start->GetFCBFileName() << ' ' << start->GetFCBIndex() << ' ' << start->GetFCBLength() << ' ' << start->GetFCBAddress() << endl;
	}
}
int BinaryTree::Brother(TreeNode* location)//���location�ڵ�����������ֵܣ�����������ڵ�������һ֦�ϵĳ��ýڵ������еĽڵ�
{
	if (location == NULL || location->GetRight() == NULL)//���ֵܽ������
	{
		return 0;
	}
	else
	{
		int count = 0;
		while (location->GetRight() != NULL)//������֦������
		{
			location = location->GetRight();
			++count;
			continue;
		}
		return count;
	}
}
TreeNode* BinaryTree::Insert(FCB item, int direction, TreeNode* location)//�ڵ�ǰ�ڵ������ҷ������ֵΪitem�����ӽڵ�
{
	if (location == NULL)//�Ƿ�����λ��
	{
		cout << "����λ�÷Ƿ�������ʧ��" << endl;
		return NULL;
	}
	current = new TreeNode(item);
	if (direction == KID)           //�����ӽڵ�
	{
		TreeNode* temp = location->GetLeft();
		if (temp == NULL)//��ǰû���ӽڵ���ֱ���趨leftָ��
		{
			location->SetLeft(current);
			current->SetParent(location);
		}
		else//��ǰ���ӽڵ������ӽڵ����ԭ����Ů�������ֵ�֮��
		{
			while (temp->GetRight() != NULL)
				temp = temp->GetRight();
			temp->SetRight(current);
			current->SetParent(temp);
		}
		//current = temp;
		return current;
	}
	else if (direction == BROTHER)//�����ֵܽڵ�
	{
		TreeNode* temp = location->GetRight();
		if (temp == NULL)//��ǰû���ֵܽڵ���ֱ���趨rightָ��
		{
			location->SetRight(current);
			current->SetParent(location);
		}
		else//��ǰ���ֵܽڵ����½ڵ���뵽�����ֵ�֮��
		{
			while (temp->GetRight() != NULL)
				temp = temp->GetRight();
			temp->SetRight(current);
			current->SetParent(temp);
		}
		return current;
	}
	else//�������ķǷ����������Ѿ��궨������ӽڵ㴫�����0���ֵܽڵ㴫�����1������������������
	{
		cout << "δ����Ĳ���ڵ�����" << endl;
		return NULL;
	}
}
TreeNode* BinaryTree::FindTarget(string target, TreeNode* start)//��startλ�ÿ�ʼѰ�����е�һ��ֵΪtarget�Ľڵ㣬��������λ��
{
	if (start == NULL)//��Ч��������ʼλ��
		return NULL;
	else if (start->GetFCBAddress() == target)//�ݹ��������
		return start;
	else     //�ݹ�˼·��������û�ҵ��ͼ�������������
	{
		TreeNode* temp = FindTarget(target, start->GetLeft());
		if (temp == NULL && start != NULL && (start->GetRight() != NULL))
			temp = FindTarget(target, start->GetRight());
		return temp;
	}
}