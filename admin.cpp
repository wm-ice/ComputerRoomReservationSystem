#include"admin.h"

Admin::Admin()
{

}

//�вι��캯��
Admin::Admin(string name, string pwd)
{
	this->m_Name = name;
	this->m_Password = pwd;

	this->initVector();
	this->initComVector();
}

// �˵�����
void Admin::openMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��½��" << endl;
	cout << "�����ǹ���Ա�˵���" << endl; 
	cout << "1������˺�" << endl;
	cout << "2���鿴�˺�" << endl;
	cout << "3���鿴����" << endl;
	cout << "4�����ԤԼ" << endl;
	cout << "5��ע����½" << endl;
	cout << "���������ѡ����Ҫ���еĲ�����";
}

//���Ż���ɾ���˺�
//����˺ţ����ѧ�����ʦ���˺ţ�����ѧ����ź�ְ�����Ƿ��ظ�
void Admin::addAccount()
{
	cout << "������˺��������£�" << endl;
	cout << "1�����ѧ���˺�" << endl;
	cout << "2����ӽ�ʦ�˺�" << endl;
	cout << "���������ѡ����Ҫ���еĲ�����";
	int iSel = 0;
	while (true)
	{
		cin >> iSel;
		if (iSel >= 1 && iSel <= 2)
		{
			break;
		}
		cout << "�����������������룺";
	}
	ofstream ofs;
	//Ҫ��ѯ���ļ�����������ʾ
	string fileName, tip;
	//������ظ���ʾ
	string errorTip;
	int type = 1;
	if (iSel == 2)
	{
		//��ӽ�ʦ
		fileName = TEACHER_FILE;
		tip = "������ְ����ţ�";
		type = 2;
		errorTip = "��ְ�����Ѵ��ڣ����������룡";
	}
	else
	{
		//���ѧ��
		fileName = STUDENT_FILE;
		tip = "������ѧ��ѧ�ţ�";
		type = 1;
		errorTip = "��ѧ��ѧ���Ѵ��ڣ����������룡";
	}
	//����׷�ӵķ�ʽд�ļ�
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name, pwd;
	while (true)
	{
		cout << tip;
		cin >> id;
		bool ret=checkRepeat(id, type);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "������������";
	cin >> name;
	cout << "���������룺";
	cin >> pwd;
	//���ļ����������
	ofs << id << " " << name << " " << pwd << endl;
	cout << "����³�Ա�ɹ�" << endl;
	this->initVector();
	system("pause");
	system("cls");
	ofs.close();
}

void printStudent(Student &s)
{
	cout << "ѧ�ţ�" << s.m_Id << "\tѧ��������" << s.m_Name << "\t���룺" << s.m_Password << endl;
}
void printTeacher(Teacher &t)
{
	cout << "ְ���ţ�" << t.m_Id << "\t��ʦ������" << t.m_Name << "\t���룺" << t.m_Password << endl;
}
void printComputerRoom(ComputerRoom& com)
{
	cout << "�����ţ�" << com.m_ComId << "\t�������������" << com.m_MaxNum << endl;
}

//for_each���Ի���forѭ������vector
//�鿴�˺ţ�����ѡ��鿴ѧ�����ʦ��ȫ����Ϣ
void Admin::showAccount()
{
	cout << "�鿴�˺��������£�" << endl;
	cout << "1��ѧ���˺�" << endl;
	cout << "2����ʦ�˺�" << endl;
	cout << "���������ѡ����Ҫ���еĲ���(Ĭ��Ϊ1)��";
	int iSel = 0;
	cin >> iSel;
	//Ҫ��ѯ���ļ�����������ʾ
	if (iSel == 2)
	{
		//��ʾ��ʦ��Ϣ
		cout << "���н�ʦ��Ϣ���£�" << endl;
		for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
	}
	else
	{
		//��ʾѧ����Ϣ
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(this->vStd.begin(), this->vStd.end(), printStudent);
	}
	system("pause");
	system("cls");
}

//���Ż������ӻ�����Ϣ��ɾ��������Ϣ
//�鿴�������鿴���л�������Ϣ
void Admin::showComputerRoom()
{
	cout << "���л�����Ϣ���£�" << endl;
	for_each(this->vComRoom.begin(), this->vComRoom.end(), printComputerRoom);
	system("pause");
	system("cls");
}

//���ԤԼ���������ԤԼ��¼
void Admin::clearOrder()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out|ios::trunc);
	ofs.clear();
	cout << "���������ԤԼ��Ϣ��" << endl;
	system("pause");
	system("cls");
}

//��ʼ��ѧ���ͽ�ʦ������
void Admin::initVector()
{
	vStd.clear();
	vTea.clear();
	//��ȡ��Ϣ��ѧ������ʦ�˺ţ�
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Student std;
	while (ifs>>std.m_Id&&ifs>>std.m_Name&&ifs>>std.m_Password)
	{
		vStd.push_back(std);
	}
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Teacher tea;
	while (ifs >> tea.m_Id && ifs >> tea.m_Name && ifs >> tea.m_Password)
	{
		vTea.push_back(tea);
	}
	ifs.close();
}

//�����ӵ����˺��Ƿ��ظ�
bool Admin::checkRepeat(int id, int type)
{
	//���ѧ��
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStd.begin(); it != vStd.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	//����ʦ
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	return false;
}

//��ʼ��������Ϣ������
void Admin::initComVector()
{
	this->vComRoom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vComRoom.push_back(com);
	}
	ifs.close();
}

Admin::~Admin()
{

}


