#pragma once
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"student.h"
#include"teacher.h"
#include<algorithm>

//����Ա
class Admin :public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Admin();

	//�вι��캯��
	Admin(string name, string pwd);

	// �˵�����
	virtual void openMenu();
	//����˺ţ����ѧ�����ʦ���˺ţ�����ѧ����ź�ְ�����Ƿ��ظ�
	void addAccount();
	//�鿴�˺ţ�����ѡ��鿴ѧ�����ʦ��ȫ����Ϣ
	void showAccount();
	//�鿴�������鿴���л�������Ϣ
	void showComputerRoom();
	//���ԤԼ���������ԤԼ��¼
	void clearOrder();
	//ע����½���˳���½

	//��ʼ��ѧ���ͽ�ʦ������
	void initVector();
	//ѧ������
	vector<Student>vStd;
	//��ʦ����
	vector<Teacher>vTea;
	//�����ӵ����˺��Ƿ��ظ�
	//id������id��type��1Ϊѧ��2Ϊ��ʦ
	bool checkRepeat(int id, int type);
	//���Ż�����������Ϣ��װ
	//������Ϣ����
	vector<ComputerRoom>vComRoom;
	//��ʼ��������Ϣ������
	void initComVector();
	~Admin();

private:

};

