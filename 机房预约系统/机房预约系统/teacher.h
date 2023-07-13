#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include"orderFile.h"
#include<vector>
//教师类
class Teacher :public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int empId, string name, string password);

	//教师菜单
	virtual void operMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//职工编号
	int m_EmpId;
};