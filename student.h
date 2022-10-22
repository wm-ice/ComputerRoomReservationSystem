#pragma once
#include"identity.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"

//学生类
class Student:public Identity
{
public:
	//默认构造函数
	Student();

	//有参构造函数
	Student(int id, string name, string pwd);

	// 菜单界面
	virtual void openMenu();

	//申请预约：预约机房
	void applyOrder();
	//查看自身的预约：查看自己的预约状态
	void showMyOrder();
	//查看所有预约：查看全部预约信息以及预约状态
	void showALLOrder();
	//取消预约：取消自身预约，预约成功或者审核中的预约都可以取消
	void cancelOrder();
	//注销登陆：退出登陆
	
	//学生学号
	int m_Id;

	//可优化：将机房信息封装
	//机房信息容器
	vector<ComputerRoom>vComRoom;
	//初始化机房信息的容器
	void initComVector();

	~Student();

private:

};

