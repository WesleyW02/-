#pragma once
#include<iostream>
using namespace std;

//创建身份基类
class Identity
{
public:
	//操作菜单，纯虚函数
	virtual void operMenu() = 0;

	//用户名
	string m_Name;
	string m_Password;//密码

};