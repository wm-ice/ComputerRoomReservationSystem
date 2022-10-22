#pragma once
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"student.h"
#include"teacher.h"
#include<algorithm>

//管理员
class Admin :public Identity
{
public:
	//默认构造函数
	Admin();

	//有参构造函数
	Admin(string name, string pwd);

	// 菜单界面
	virtual void openMenu();
	//添加账号：添加学生或教师的账号，需检测学生编号和职工号是否重复
	void addAccount();
	//查看账号：可以选择查看学生或教师的全部信息
	void showAccount();
	//查看机房：查看所有机房的信息
	void showComputerRoom();
	//清空预约：清空所有预约记录
	void clearOrder();
	//注销登陆：退出登陆

	//初始化学生和教师的容器
	void initVector();
	//学生容器
	vector<Student>vStd;
	//教师容器
	vector<Teacher>vTea;
	//检测添加的新账号是否重复
	//id：检测的id，type：1为学生2为教师
	bool checkRepeat(int id, int type);
	//可优化：将机房信息封装
	//机房信息容器
	vector<ComputerRoom>vComRoom;
	//初始化机房信息的容器
	void initComVector();
	~Admin();

private:

};

