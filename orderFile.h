#pragma once
#include<iostream>
#include"globalFile.h"
#include<fstream>
#include<map>
using namespace std;

//ԤԼ�ļ���
class OrderFile
{
public:
	OrderFile();
	~OrderFile();
	//����ԤԼ��¼
	void updateOrder();
	//��¼ԤԼ��Ŀ
	int m_Size;
	//��¼����ԤԼ��Ϣ������
	//int��ԤԼ���(����)��map<string, string>��ԤԼ��Ϣ(���֣���Ϣ)
	map<int, map<string, string>>mOrder;

private:

};

