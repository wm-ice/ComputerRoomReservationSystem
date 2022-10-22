#include"orderFile.h"

OrderFile::OrderFile()
{	
	this->m_Size = 0;
	this->mOrder.clear();
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	string stdId;
	string stdName;
	string date;
	string interval;
	string room;
	string status;
	while (ifs >> stdId && ifs >> stdName && ifs >> date &&
		ifs >> interval && ifs >> room && ifs >> status)
	{
		string key;
		string value;
		map<string, string>m;
		int pos = -1;
		//stdId---->   stdId:1   (pos=5,   字符串.substr(起始0,字符个数5)   字符串.size()=7)
		//学生ID
		pos = stdId.find(":");
		if (pos != -1)
		{
			key = stdId.substr(0, pos);
			value = stdId.substr(pos + 1, stdId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//学生姓名
		pos = stdName.find(":");
		if (pos != -1)
		{
			key = stdName.substr(0, pos);
			value = stdName.substr(pos + 1, stdName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//日期
		pos = date.find(":");
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//时间段
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//机房号
		pos = room.find(":");
		if (pos != -1)
		{
			key = room.substr(0, pos);
			value = room.substr(pos + 1, room.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//审核状态
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		this->mOrder.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
}

OrderFile::~OrderFile()
{
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "stdId:" << this->mOrder[i]["stdId"] << " ";
		ofs << "stdName:" << this->mOrder[i]["stdName"] << " ";
		ofs << "date:" << this->mOrder[i]["date"] << " ";
		ofs << "interval:" << this->mOrder[i]["interval"] << " ";
		ofs << "room:" << this->mOrder[i]["room"] << " ";
		ofs << "status:" << this->mOrder[i]["status"] << endl;
	}
	ofs.close();
}