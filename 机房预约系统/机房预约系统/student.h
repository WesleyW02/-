#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"globalFile.h"
#include"computerRoom.h"
#include<fstream>
#include"orderFile.h"

//学生类
class Student :public Identity
{
public:
	Student();//默认构造

	//有参构造 学号、姓名、密码
	Student(int id,string name,string password);
	//菜单界面
	virtual void operMenu();

	//申请预约
	void applyOrder();
	// 查看自身预约
	void showMyOrder();
	// 查看所有预约
	void showAllOrder();
	// 取消预约
	void cancelOrder();
	//初始化机房信息
	void initComputerRoom();
	 
	//学生学号
	int m_Id;

	//机房信息
	vector<ComputerRoom> vCom;
};