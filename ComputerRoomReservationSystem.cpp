#include<iostream>
#include<fstream>
#include"globalFile.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"admin.h"
using namespace std;

//可优化：如果文件存在且有数据则读文件，否则创建文件并写文件
//创建各种资源文件
void CreateFile()
{
	ofstream ofs;
	ofs.open(ADMIN_FILE, ios::out/*|ios::app*/);
	//向文件中添加管理员登陆数据
	ofs << "admin" << " " << "123" << endl;
	ofs.close();
	ofs.open(STUDENT_FILE, ios::out | ios::app);
	ofs.close();
	ofs.open(TEACHER_FILE, ios::out | ios::app);
	ofs.close();
	ofs.open(COMPUTER_ROOM_FILE, ios::out /*| ios::app*/);
	//向文件中添加初始机房数据
	ofs << 1 << " " << 20 <<  endl;
	ofs << 2 << " " << 50 << endl;
	ofs << 3 << " " << 100 << endl;
	ofs.close();
	ofs.open(ORDER_FILE, ios::out | ios::app);
	ofs.close();
}

//进入管理员子菜单界面
void AdminMenu(Identity*& person)
{
	while (true)
	{
		//调用管理员子菜单
		person->openMenu();
		//将父类指针转换为子类指针，调用子类里其他接口
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
			//销毁堆区对象
			delete admin;
			cout << "注销成功，欢迎下次使用" << endl;
			system("pause");
			system("cls");
			return;
		}
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
//进入学生子菜单界面
void StudentMenu(Identity*& person)
{
	while (true)
	{
		//调用学生子菜单
		person->openMenu();
		//将父类指针转换为子类指针，调用子类里其他接口
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
			//销毁堆区对象
			delete student;
			cout << "注销成功，欢迎下次使用" << endl;
			system("pause");
			system("cls");
			return;
		}
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
//进入教师子菜单界面
void TeacherMenu(Identity*& person)
{
	while (true)
	{
		//调用教师子菜单
		person->openMenu();
		//将父类指针转换为子类指针，调用子类里其他接口
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
			//销毁堆区对象
			delete teacher;
			cout << "注销成功，欢迎下次使用" << endl;
			system("pause");
			system("cls");
			return;
		}
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//登陆功能
//fileName：操作文件名称，type：操作身份类型
void LoginIn(string fileName, int type)
{
	//创建父类的指针指向子类对象
	Identity* person = NULL;
	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout<<"文件不存在" << endl;
		ifs.close();
		return;
	}
	//判断身份
	int id = 0;
	string name, pwd;
	if (type == 1)
	{
		cout << "请输入您的学生学号：";
		cin >> id;
	}
	else if(type == 2)
	{
		cout << "请输入您的教师职工号：";
		cin >> id;
	}
	cout << "请输入您的用户名：";
	cin >> name;
	cout << "请输入您的密码：";
	cin >> pwd;

	//可优化：验证身份的时候在管理员类的容器中去找用户，就不需要文件遍历
	//验证身份
	if (type == 1)
	{
		int fId;
		string fName, fPwd;
		while (ifs>>fId && ifs>>fName && ifs>>fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << name<<"登陆验证成功！" << endl;
				//system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生功能的子菜单
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
				cout << name<<"登陆验证成功！" << endl;
				//system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				//进入教师功能的子菜单
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
				cout << name<<"登陆验证成功！" << endl;
				//system("pause");
				system("cls");
				person = new Admin(name, pwd);
				//进入管理员功能的子菜单
				AdminMenu(person);
				return;
			}
		}
	}
	cout<<"登陆验证失败！" << endl;
	system("pause");
	system("cls");
}

int main()
{
	CreateFile();
	int iSel = 0;
	while (true)
	{
		//菜单
		cout << "欢迎进入登陆界面！请选择身份进去系统：" << endl;
		cout << "1、学生代表" << endl;
		cout << "2、教师" << endl;
		cout << "3、管理员" << endl;
		cout << "4、退出登陆" << endl;
		cout << "请输入您的身份：";
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
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 1;
}
