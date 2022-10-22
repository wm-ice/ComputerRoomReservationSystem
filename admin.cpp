#include"admin.h"

Admin::Admin()
{

}

//有参构造函数
Admin::Admin(string name, string pwd)
{
	this->m_Name = name;
	this->m_Password = pwd;

	this->initVector();
	this->initComVector();
}

// 菜单界面
void Admin::openMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登陆！" << endl;
	cout << "以下是管理员菜单：" << endl; 
	cout << "1、添加账号" << endl;
	cout << "2、查看账号" << endl;
	cout << "3、查看机房" << endl;
	cout << "4、清空预约" << endl;
	cout << "5、注销登陆" << endl;
	cout << "请输入序号选择您要进行的操作：";
}

//可优化：删除账号
//添加账号：添加学生或教师的账号，需检测学生编号和职工号是否重复
void Admin::addAccount()
{
	cout << "可添加账号类型如下：" << endl;
	cout << "1、添加学生账号" << endl;
	cout << "2、添加教师账号" << endl;
	cout << "请输入序号选择您要进行的操作：";
	int iSel = 0;
	while (true)
	{
		cin >> iSel;
		if (iSel >= 1 && iSel <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入：";
	}
	ofstream ofs;
	//要查询的文件名和输入提示
	string fileName, tip;
	//错误的重复提示
	string errorTip;
	int type = 1;
	if (iSel == 2)
	{
		//添加教师
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		type = 2;
		errorTip = "该职工号已存在，请重新输入！";
	}
	else
	{
		//添加学生
		fileName = STUDENT_FILE;
		tip = "请输入学生学号：";
		type = 1;
		errorTip = "该学生学号已存在，请重新输入！";
	}
	//利用追加的方式写文件
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
	cout << "请输入姓名：";
	cin >> name;
	cout << "请输入密码：";
	cin >> pwd;
	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加新成员成功" << endl;
	this->initVector();
	system("pause");
	system("cls");
	ofs.close();
}

void printStudent(Student &s)
{
	cout << "学号：" << s.m_Id << "\t学生姓名：" << s.m_Name << "\t密码：" << s.m_Password << endl;
}
void printTeacher(Teacher &t)
{
	cout << "职工号：" << t.m_Id << "\t教师姓名：" << t.m_Name << "\t密码：" << t.m_Password << endl;
}
void printComputerRoom(ComputerRoom& com)
{
	cout << "机房号：" << com.m_ComId << "\t机房最大容量：" << com.m_MaxNum << endl;
}

//for_each可以换成for循环遍历vector
//查看账号：可以选择查看学生或教师的全部信息
void Admin::showAccount()
{
	cout << "查看账号类型如下：" << endl;
	cout << "1、学生账号" << endl;
	cout << "2、教师账号" << endl;
	cout << "请输入序号选择您要进行的操作(默认为1)：";
	int iSel = 0;
	cin >> iSel;
	//要查询的文件名和输入提示
	if (iSel == 2)
	{
		//显示教师信息
		cout << "所有教师信息如下：" << endl;
		for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
	}
	else
	{
		//显示学生信息
		cout << "所有学生信息如下：" << endl;
		for_each(this->vStd.begin(), this->vStd.end(), printStudent);
	}
	system("pause");
	system("cls");
}

//可优化：增加机房信息，删除机房信息
//查看机房：查看所有机房的信息
void Admin::showComputerRoom()
{
	cout << "所有机房信息如下：" << endl;
	for_each(this->vComRoom.begin(), this->vComRoom.end(), printComputerRoom);
	system("pause");
	system("cls");
}

//清空预约：清空所有预约记录
void Admin::clearOrder()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out|ios::trunc);
	ofs.clear();
	cout << "已清空所有预约信息！" << endl;
	system("pause");
	system("cls");
}

//初始化学生和教师的容器
void Admin::initVector()
{
	vStd.clear();
	vTea.clear();
	//读取信息（学生、老师账号）
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
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
		cout << "文件读取失败！" << endl;
		return;
	}
	Teacher tea;
	while (ifs >> tea.m_Id && ifs >> tea.m_Name && ifs >> tea.m_Password)
	{
		vTea.push_back(tea);
	}
	ifs.close();
}

//检测添加的新账号是否重复
bool Admin::checkRepeat(int id, int type)
{
	//检测学生
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
	//检测教师
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

//初始化机房信息的容器
void Admin::initComVector()
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

Admin::~Admin()
{

}


