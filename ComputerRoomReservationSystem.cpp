#include<iostream>
#include<fstream>
#include"globalFile.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"admin.h"
using namespace std;

//���Ż�������ļ�����������������ļ������򴴽��ļ���д�ļ�
//����������Դ�ļ�
void CreateFile()
{
	ofstream ofs;
	ofs.open(ADMIN_FILE, ios::out/*|ios::app*/);
	//���ļ�����ӹ���Ա��½����
	ofs << "admin" << " " << "123" << endl;
	ofs.close();
	ofs.open(STUDENT_FILE, ios::out | ios::app);
	ofs.close();
	ofs.open(TEACHER_FILE, ios::out | ios::app);
	ofs.close();
	ofs.open(COMPUTER_ROOM_FILE, ios::out /*| ios::app*/);
	//���ļ�����ӳ�ʼ��������
	ofs << 1 << " " << 20 <<  endl;
	ofs << 2 << " " << 50 << endl;
	ofs << 3 << " " << 100 << endl;
	ofs.close();
	ofs.open(ORDER_FILE, ios::out | ios::app);
	ofs.close();
}

//�������Ա�Ӳ˵�����
void AdminMenu(Identity*& person)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		person->openMenu();
		//������ָ��ת��Ϊ����ָ�룬���������������ӿ�
		Admin* admin = (Admin*)person;
		int iSel = 0;
		cin >> iSel;
		switch (iSel)
		{
		case 1:
			admin->addAccount();
			break;
		case 2:
			admin->showAccount();
			break;
		case 3:
			admin->showComputerRoom();
			break;
		case 4:
			admin->clearOrder();
			break;
		case 5:
		{
			//���ٶ�������
			delete admin;
			cout << "ע���ɹ�����ӭ�´�ʹ��" << endl;
			system("pause");
			system("cls");
			return;
		}
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
//����ѧ���Ӳ˵�����
void StudentMenu(Identity*& person)
{
	while (true)
	{
		//����ѧ���Ӳ˵�
		person->openMenu();
		//������ָ��ת��Ϊ����ָ�룬���������������ӿ�
		Student* student = (Student*)person;
		int iSel = 0;
		cin >> iSel;
		switch (iSel)
		{
		case 1:
			student->applyOrder();
			break;
		case 2:
			student->showMyOrder();
			break;
		case 3:
			student->showALLOrder();
			break;
		case 4:
			student->cancelOrder();
			break;
		case 5:
		{
			//���ٶ�������
			delete student;
			cout << "ע���ɹ�����ӭ�´�ʹ��" << endl;
			system("pause");
			system("cls");
			return;
		}
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
//�����ʦ�Ӳ˵�����
void TeacherMenu(Identity*& person)
{
	while (true)
	{
		//���ý�ʦ�Ӳ˵�
		person->openMenu();
		//������ָ��ת��Ϊ����ָ�룬���������������ӿ�
		Teacher* teacher = (Teacher*)person;
		int iSel = 0;
		cin >> iSel;
		switch (iSel)
		{
		case 1:
			teacher->showALLOrder();
			break;
		case 2:
			teacher->validOrder();
			break;
		case 3:
		{
			//���ٶ�������
			delete teacher;
			cout << "ע���ɹ�����ӭ�´�ʹ��" << endl;
			system("pause");
			system("cls");
			return;
		}
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//��½����
//fileName�������ļ����ƣ�type�������������
void LoginIn(string fileName, int type)
{
	//���������ָ��ָ���������
	Identity* person = NULL;
	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout<<"�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ж����
	int id = 0;
	string name, pwd;
	if (type == 1)
	{
		cout << "����������ѧ��ѧ�ţ�";
		cin >> id;
	}
	else if(type == 2)
	{
		cout << "���������Ľ�ʦְ���ţ�";
		cin >> id;
	}
	cout << "�����������û�����";
	cin >> name;
	cout << "�������������룺";
	cin >> pwd;

	//���Ż�����֤��ݵ�ʱ���ڹ���Ա���������ȥ���û����Ͳ���Ҫ�ļ�����
	//��֤���
	if (type == 1)
	{
		int fId;
		string fName, fPwd;
		while (ifs>>fId && ifs>>fName && ifs>>fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << name<<"��½��֤�ɹ���" << endl;
				//system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ�����ܵ��Ӳ˵�
				StudentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		int fId;
		string fName, fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << name<<"��½��֤�ɹ���" << endl;
				//system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				//�����ʦ���ܵ��Ӳ˵�
				person->openMenu();
				return;
			}
		}
	}
	else if (type == 3)
	{
		string fName, fPwd;
		while ( ifs >> fName && ifs >> fPwd)
		{
			if ( fName == name && fPwd == pwd)
			{
				cout << name<<"��½��֤�ɹ���" << endl;
				//system("pause");
				system("cls");
				person = new Admin(name, pwd);
				//�������Ա���ܵ��Ӳ˵�
				AdminMenu(person);
				return;
			}
		}
	}
	cout<<"��½��֤ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
}

int main()
{
	CreateFile();
	int iSel = 0;
	while (true)
	{
		//�˵�
		cout << "��ӭ�����½���棡��ѡ����ݽ�ȥϵͳ��" << endl;
		cout << "1��ѧ������" << endl;
		cout << "2����ʦ" << endl;
		cout << "3������Ա" << endl;
		cout << "4���˳���½" << endl;
		cout << "������������ݣ�";
		cin >> iSel;
		switch (iSel)
		{
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;
		case 4:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 1;
}
