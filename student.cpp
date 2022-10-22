#include"student.h"

Student::Student()
{
}

//�вι��캯��
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = pwd;
	this->initComVector();
}

// �˵�����
void Student::openMenu()
{
	cout << "��ӭѧ����" << this->m_Name << "��½��" << endl;
	cout << "������ѧ���˵���" << endl;
	cout << "1������ԤԼ" << endl;
	cout << "2���鿴�����ԤԼ" << endl;
	cout << "3���鿴����ԤԼ" << endl;
	cout << "4��ȡ��ԤԼ" << endl;
	cout << "5��ע����½" << endl;
	cout << "���������ѡ����Ҫ���еĲ�����";
}

//���Ż���ɾ���Ѿ�ԤԼ����ʱ��
//����ԤԼ��ԤԼ����
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ�����壬��ѡ��ԤԼʹ�û�����ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	cout << "��������ţ�" ;
	//����
	int date = 0;
	//ʱ���
	int interval = 0;
	//�������
	int room = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룺";
	}
	cout << "������ԤԼʹ�û�����ʱ��Σ�" << endl;
	cout << "1�����磨8:00-12:00��" << endl;
	cout << "2�����磨14:00-18:00��" << endl;
	cout << "��������ţ�";
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "�����������������룺";
	}
	cout << "������ԤԼ�����ı�ţ�" << endl;
	for (int i = 0; i < this->vComRoom.size(); i++)
	{
		cout << i+1 <<"��" << vComRoom[i].m_ComId << "�Ż������������"<< vComRoom[i] .m_MaxNum<<"��" << endl;
	}
	cout << "��������ţ�";
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= this->vComRoom.size())
		{
			break;
		}
		cout << "�����������������룺";
	}
	cout << "��ԤԼ�ɹ�����ȴ���ˡ�" << endl;

	//����׷�ӵķ�ʽд�ļ�
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);
	ofs << "stdId:" << this->m_Id << " ";
	ofs << "stdName:" << this->m_Name << " ";
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "room:" << room << " ";
	ofs << "status:" << 1 << endl;
	ofs.close();

	system("pause");
	system("cls");
}

//��ӡԤԼ����
void printOrderData(OrderFile of,int i)
{
	string sDate[5] = { "��һ","�ܶ�","����","����","����" };
	cout << "ԤԼ���ڣ�" << sDate[atoi(of.mOrder[i]["date"].c_str()) - 1] << "\t";
	cout << "ʱ��Σ�" << (of.mOrder[i]["interval"] == "1" ? "���磨8:00-12:00��" : "���磨14:00-18:00��") << "\t";
	cout << "�����ţ�" << of.mOrder[i]["room"] << "\t";
	string status = "���״̬��";
	if (of.mOrder[i]["status"] == "1")
	{
		status += "����У���ȴ���";
	}
	else if (of.mOrder[i]["status"] == "2")
	{
		status += "���ͨ����ԤԼ�ɹ���";
	}
	else if (of.mOrder[i]["status"] == "-1")
	{
		status += "���δͨ����ԤԼʧ�ܣ�������ԤԼ��";
	}
	else
	{
		status += "ԤԼ��ȡ����";
	}
	cout << status << endl;
}

//�鿴�����ԤԼ���鿴�Լ���ԤԼ״̬
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "����ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//stringתint����Ҫ��string.c_str()ת��const char * ,����atoiתint
		if (this->m_Id == atoi(of.mOrder[i]["stdId"].c_str()))
		{
			printOrderData(of, i);
		}
	}
	system("pause");
	system("cls");
}

//�鿴����ԤԼ���鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
void Student::showALLOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "����ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << "ԤԼ��ѧ�ţ�" << of.mOrder[i]["stdId"] << "\t";
		cout << "������" << of.mOrder[i]["stdName"] << endl;
		printOrderData(of, i);
	}
	system("pause");
	system("cls");
}

//ȡ��ԤԼ��ȡ������ԤԼ��ԤԼ�ɹ���������е�ԤԼ������ȡ��
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "����ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��ǰ��ȡ����ԤԼ��¼���£�" << endl;
	int index = 1;
	//�������������е��±���
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (this->m_Id == atoi(of.mOrder[i]["stdId"].c_str()))
		{
			if (of.mOrder[i]["status"] == "1" || of.mOrder[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				printOrderData(of, i);
			}
		}
	}
	cout << "��������Ҫȡ����ԤԼ��¼����������0���أ�";
	int iSel = 0;
	while (true)
	{
		cin >> iSel;
		if (iSel>=0&&iSel<=v.size())
		{
			if (iSel == 0)
			{
				break;
			}
			//����ԤԼ��¼��״̬
			of.mOrder[v[iSel - 1]]["status"] = "0";
			of.updateOrder();
			cout << "��ȡ��ԤԼ��" << endl;
			break;
		}
		cout << "�����������������룺";
	}
	system("pause");
	system("cls");
}

//��ʼ��������Ϣ������
void Student::initComVector()
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

Student::~Student()
{
}