#pragma once
#include<iostream>
#include"globalFile.h"
using namespace std;
#include<fstream>
#include<map>
#include<string>

class OrderFile
{
public:
	OrderFile();

	//更新预约
	void updateOrder();

	int m_size;//预约条数
	struct isEmpty
	{
		int busy[6][3];
	};
	map<int, struct isEmpty> m_isEmpty;
	//记录信息的容器
	map<int, map<string, string>> m_orderData;
	//key :记录条数，val：具体的记录信息
};