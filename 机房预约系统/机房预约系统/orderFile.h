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

	//����ԤԼ
	void updateOrder();

	int m_size;//ԤԼ����
	struct isEmpty
	{
		int busy[6][3];
	};
	map<int, struct isEmpty> m_isEmpty;
	//��¼��Ϣ������
	map<int, map<string, string>> m_orderData;
	//key :��¼������val������ļ�¼��Ϣ
};