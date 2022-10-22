#pragma once
#include<iostream>
#include"globalFile.h"
#include<fstream>
#include<map>
using namespace std;

//预约文件类
class OrderFile
{
public:
	OrderFile();
	~OrderFile();
	//更新预约记录
	void updateOrder();
	//记录预约数目
	int m_Size;
	//记录所有预约信息的容器
	//int：预约编号(次序)，map<string, string>：预约信息(名字，信息)
	map<int, map<string, string>>mOrder;

private:

};

