#pragma once
#include<iostream>
#include<fstream>
#include"globalFile.h"
using namespace std;

//��ݳ������
class Identity
{
public:
	//�����˵�  ���麯��
	virtual void openMenu()=0;
	//�û���
	string m_Name;
	//����
	string m_Password;
};
