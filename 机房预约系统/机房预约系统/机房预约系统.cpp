#include<iostream>
using namespace std;
#include"identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

void showMenu()
{
	cout << "==================欢迎来到机房预约系统==================" << endl;
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t --------------------------------\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           1.学  生           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           2.老  师           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           3.管理员           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           0.退  出           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t --------------------------------\n";
	cout << "请输入您的选择" << endl;
}

//管理员菜单界面函数定义和实现
void managerMenu(Identity * &manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();
		//父类指针转为子类，可调用子类其他特有接口
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1://添加账号
			man->addPerson();
			break;
		case 2://查看账号
			man->showPerson();
			break;
		case 3://查看机房信息
			man->showComputer();
			break;
		case 4://清空预约
			man->cleanFile();
			break;
		case 0://注销登陆
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//学生菜单界面函数定义和实现
void StudentMenu(Identity* &student)
{
	while (true)
	{
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			stu->applyOrder();
			break;
		case 2:
			stu->showMyOrder();
			break;
		case 3:
			stu->showAllOrder();
			break;
		case 4:
			stu->cancelOrder();
			break;
		case 0:
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//老师菜单
void TeacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			tea->showAllOrder();
			break;
		case 2:
			tea->validOrder();
			break;
		case 0:
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//登陆函数封装
void LoginIn(string fileName, int type)
{
	Identity* person;//父类指针，指向子类对象

	//读文件
	ifstream  ifs;
	ifs.open(fileName, ios::in);
	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接收用户信息
	int id = 0;
	string name;
	string password;
	if (type == 1)//学生
	{
		cout << "请输入你的学号: " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号: " << endl;
		cin >> id;
	}
	cout << "请输入你的用户名: " << endl;
	cin >> name;
	cout << "请输入你的密码: " << endl;
	cin >> password;

	if (type == 1 || type == 2)
	{
		//学生或者教师身份验证
		int fId;
		string fName;
		string fPassword;
		while (ifs>>fId&&ifs>>fName&&ifs>>fPassword)
		{
			//cout << fId << fName << fPassword << endl;
			if (fId == id && fName == name && fPassword == password)
			{
				if (type == 1)
				{
					cout << " 学生验证登陆成功" << endl;
					system("pause");
					system("cls");
					person = new Student(id, name, password);
					//进入学生身份子菜单
					StudentMenu(person);
					ifs.close();
					return;
				}
				else
				{
					cout << " 老师验证登陆成功" << endl;
					system("pause");
					system("cls");
					person = new Teacher(id, name, password);
					//进入老师身份子菜单
					TeacherMenu(person);
					ifs.close();
					return;
				}
			}
		}
	}
	else if (type == 3)
	{
		//管理员验证
		string fName;
		string fPassword;
		while (ifs >> fName && ifs >> fPassword)
		{
			if (fName == name && fPassword == password)
			{
				cout << " 管理员验证登陆成功" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, password);
				//进入管理员身份子菜单
				managerMenu(person);
				ifs.close();
				return;
			}
		}
	}
	cout << "验证登陆失败" << endl;
	ifs.close();
	system("pause");
	system("cls");
	return;
}

int main()
{
	int select = 0;
	while (true)
	{
		showMenu();
		cin >> select;
		switch (select)
		{
		case 1://学生
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://老师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
			cout << "欢迎下一次使用！" << endl;
			system("pause");
			return 0;
			break;
		default :
			cout << "输入有误，请重新选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}