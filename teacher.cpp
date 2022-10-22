#include"teacher.h"

Teacher::Teacher()
{
}

//有参构造函数
Teacher::Teacher(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = pwd;
}

// 菜单界面
void Teacher::openMenu()
{
	cout << "欢迎教师：" << this->m_Name << "登陆！" << endl;
	cout << "以下是教师菜单：" << endl;
	cout << "1、查看所有预约" << endl;
	cout << "2、审核预约" << endl;
	cout << "3、注销登陆" << endl;
	cout << "请输入序号选择您要进行的操作：";
}

//打印预约数据
void printALLOrderData(OrderFile of, int i)
{
	cout << "预约的学号：" << of.mOrder[i]["stdId"] << "\t";
	cout << "姓名：" << of.mOrder[i]["stdName"] << endl;
	string sDate[5] = { "周一","周二","周三","周四","周五" };
	cout << "预约日期：" << sDate[atoi(of.mOrder[i]["date"].c_str()) - 1] << "\t";
	cout << "时间段：" << (of.mOrder[i]["interval"] == "1" ? "上午（8:00-12:00）" : "下午（14:00-18:00）") << "\t";
	cout << "机房号：" << of.mOrder[i]["room"] << "\t";
	string status = "审核状态：";
	if (of.mOrder[i]["status"] == "1")
	{
		status += "审核中，请等待！";
	}
	else if (of.mOrder[i]["status"] == "2")
	{
		status += "审核通过，预约成功！";
	}
	else if (of.mOrder[i]["status"] == "-1")
	{
		status += "审核未通过，预约失败，请重新预约！";
	}
	else
	{
		status += "预约已取消！";
	}
	cout << status << endl;
}

//查看所有预约：查看全部预约信息以及预约状态
void Teacher::showALLOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "暂无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";
		printALLOrderData(of, i);
	}
	system("pause");
	system("cls");
}

//取消预约：取消自身预约，预约成功或者审核中的预约都可以取消
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "暂无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "当前待审核的预约记录如下：" << endl;
	int index = 1;
	//存放在最大容器中的下标编号
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.mOrder[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "、";
			printALLOrderData(of, i);
		}
	}
	cout << "请输入想要审核的预约记录，或者输入0返回：";
	int iSel = 0;
	int ret = 0;//接收审核结果
	while (true)
	{
		cin >> iSel;
		if (iSel >= 0 && iSel <= v.size())
		{
			if (iSel == 0)
			{
				break;
			}
			cout << "请输入审核结果：1、审核通过，2、审核不通过：";
			cin >> ret;
			if (ret == 1)
			{
				//设置预约记录的状态
				of.mOrder[v[iSel - 1]]["status"] = "2";
			}
			else
			{
				//设置预约记录的状态
				of.mOrder[v[iSel - 1]]["status"] = "-1";
			}
			of.updateOrder();
			cout << "审核结束！" << endl;
			break;
		}
		cout << "输入有误，请重新输入：";
	}
	system("pause");
	system("cls");
}

Teacher::~Teacher()
{
}