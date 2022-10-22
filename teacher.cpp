#include"teacher.h"

Teacher::Teacher()
{
}

//�вι��캯��
Teacher::Teacher(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = pwd;
}

// �˵�����
void Teacher::openMenu()
{
	cout << "��ӭ��ʦ��" << this->m_Name << "��½��" << endl;
	cout << "�����ǽ�ʦ�˵���" << endl;
	cout << "1���鿴����ԤԼ" << endl;
	cout << "2�����ԤԼ" << endl;
	cout << "3��ע����½" << endl;
	cout << "���������ѡ����Ҫ���еĲ�����";
}

//��ӡԤԼ����
void printALLOrderData(OrderFile of, int i)
{
	cout << "ԤԼ��ѧ�ţ�" << of.mOrder[i]["stdId"] << "\t";
	cout << "������" << of.mOrder[i]["stdName"] << endl;
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

//�鿴����ԤԼ���鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
void Teacher::showALLOrder()
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
		cout << i + 1 << "��";
		printALLOrderData(of, i);
	}
	system("pause");
	system("cls");
}

//ȡ��ԤԼ��ȡ������ԤԼ��ԤԼ�ɹ���������е�ԤԼ������ȡ��
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "����ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��ǰ����˵�ԤԼ��¼���£�" << endl;
	int index = 1;
	//�������������е��±���
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.mOrder[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "��";
			printALLOrderData(of, i);
		}
	}
	cout << "��������Ҫ��˵�ԤԼ��¼����������0���أ�";
	int iSel = 0;
	int ret = 0;//������˽��
	while (true)
	{
		cin >> iSel;
		if (iSel >= 0 && iSel <= v.size())
		{
			if (iSel == 0)
			{
				break;
			}
			cout << "��������˽����1�����ͨ����2����˲�ͨ����";
			cin >> ret;
			if (ret == 1)
			{
				//����ԤԼ��¼��״̬
				of.mOrder[v[iSel - 1]]["status"] = "2";
			}
			else
			{
				//����ԤԼ��¼��״̬
				of.mOrder[v[iSel - 1]]["status"] = "-1";
			}
			of.updateOrder();
			cout << "��˽�����" << endl;
			break;
		}
		cout << "�����������������룺";
	}
	system("pause");
	system("cls");
}

Teacher::~Teacher()
{
}