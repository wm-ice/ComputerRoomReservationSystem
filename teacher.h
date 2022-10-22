#pragma once
#include"identity.h"
#include"orderFile.h"
#include<vector>
//教师类
class Teacher:public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);

	// 菜单界面
	virtual void openMenu();

	//查看所有预约：查看全部预约信息以及预约状态
	void showALLOrder();
	//审核预约：对学生的预约进行审核
	void validOrder();
	//注销登陆：退出登陆

	//职工号
	int m_Id;

	~Teacher();

private:

};
