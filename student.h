#pragma once
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"

//ѧ����
class Student:public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Student();

	//�вι��캯��
	Student(int id, string name, string pwd);

	// �˵�����
	virtual void openMenu();

	//����ԤԼ��ԤԼ����
	void applyOrder();
	//�鿴�����ԤԼ���鿴�Լ���ԤԼ״̬
	void showMyOrder();
	//�鿴����ԤԼ���鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
	void showALLOrder();
	//ȡ��ԤԼ��ȡ������ԤԼ��ԤԼ�ɹ���������е�ԤԼ������ȡ��
	void cancelOrder();
	//ע����½���˳���½
	
	//ѧ��ѧ��
	int m_Id;

	//���Ż�����������Ϣ��װ
	//������Ϣ����
	vector<ComputerRoom>vComRoom;
	//��ʼ��������Ϣ������
	void initComVector();

	~Student();

private:

};

