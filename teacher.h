#pragma once
#include"identity.h"
#include"orderFile.h"
#include<vector>
//��ʦ��
class Teacher:public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);

	// �˵�����
	virtual void openMenu();

	//�鿴����ԤԼ���鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
	void showALLOrder();
	//���ԤԼ����ѧ����ԤԼ�������
	void validOrder();
	//ע����½���˳���½

	//ְ����
	int m_Id;

	~Teacher();

private:

};
