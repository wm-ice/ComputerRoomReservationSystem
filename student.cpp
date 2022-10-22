#include"student.h"

Student::Student()
{
}

//有参构造函数
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = pwd;
	this->initComVector();
}

// 菜单界面
void Student::openMenu()
{
	cout << "欢迎学生：" << this->m_Name << "登陆！" << endl;
	cout << "以下是学生菜单：" << endl;
	cout << "1、申请预约" << endl;
	cout << "2、查看自身的预约" << endl;
	cout << "3、查看所有预约" << endl;
	cout << "4、取消预约" << endl;
	cout << "5、注销登陆" << endl;
	cout << "请输入序号选择您要进行的操作：";
}

//可优化：删除已经预约满的时间
//申请预约：预约机房
void Student::applyOrder()
{
	cout << "机房开放时间为周一至周五，请选择预约使用机房的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	cout << "请输入序号：" ;
	//日期
	int date = 0;
	//时间段
	int interval = 0;
	//机房编号
	int room = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入：";
	}
	cout << "请输入预约使用机房的时间段：" << endl;
	cout << "1、上午（8:00-12:00）" << endl;
	cout << "2、下午（14:00-18:00）" << endl;
	cout << "请输入序号：";
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入：";
	}
	cout << "请输入预约机房的编号：" << endl;
	for (int i = 0; i < this->vComRoom.size(); i++)
	{
		cout << i+1 <<"、" << vComRoom[i].m_ComId << "号机房，最大容量"<< vComRoom[i] .m_MaxNum<<"人" << endl;
	}
	cout << "请输入序号：";
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= this->vComRoom.size())
		{
			break;
		}
		cout << "输入有误，请重新输入：";
	}
	cout << "已预约成功！请等待审核。" << endl;

	//利用追加的方式写文件
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

//打印预约数据
void printOrderData(OrderFile of,int i)
{
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

//查看自身的预约：查看自己的预约状态
void Student::showMyOrder()
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
		//string转int，需要先string.c_str()转成const char * ,再用atoi转int
		if (this->m_Id == atoi(of.mOrder[i]["stdId"].c_str()))
		{
			printOrderData(of, i);
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约：查看全部预约信息以及预约状态
void Student::showALLOrder()
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
		cout << "预约的学号：" << of.mOrder[i]["stdId"] << "\t";
		cout << "姓名：" << of.mOrder[i]["stdName"] << endl;
		printOrderData(of, i);
	}
	system("pause");
	system("cls");
}

//取消预约：取消自身预约，预约成功或者审核中的预约都可以取消
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "暂无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "当前可取消的预约记录如下：" << endl;
	int index = 1;
	//存放在最大容器中的下标编号
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (this->m_Id == atoi(of.mOrder[i]["stdId"].c_str()))
		{
			if (of.mOrder[i]["status"] == "1" || of.mOrder[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				printOrderData(of, i);
			}
		}
	}
	cout << "请输入想要取消的预约记录，或者输入0返回：";
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
			//设置预约记录的状态
			of.mOrder[v[iSel - 1]]["status"] = "0";
			of.updateOrder();
			cout << "已取消预约！" << endl;
			break;
		}
		cout << "输入有误，请重新输入：";
	}
	system("pause");
	system("cls");
}

//初始化机房信息的容器
void Student::initComVector()
{
	this->vComRoom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_ROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
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