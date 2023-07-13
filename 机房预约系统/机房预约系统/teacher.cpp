#include"teacher.h"

//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empId, string name, string password)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Password = password;
}

//教师菜单
void Teacher::operMenu()
{
	cout << "欢迎老师： " << this->m_Name << "登陆！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           1.查看预约           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           2.审核预约           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           0.注销登陆           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请输入您的选择" << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile order;
	if (order.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 1; i <= order.m_size; i++)
	{
		cout << "第" << i << "条记录：";
		cout << "预约日期：周" << order.m_orderData[i]["date"];
		cout << "、时间段：" << (order.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "、学号：" << order.m_orderData[i]["stuId"];
		cout << "、姓名：" << order.m_orderData[i]["stuName"];
		cout << "、机房号：" << order.m_orderData[i]["roomId"];
		string  status = "、状态：";
		if (order.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (order.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (order.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else if (order.m_orderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
	return;
}

//审核预约
void Teacher::validOrder()
{

	OrderFile order;
	if (order.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	int flag = 0;
	cout << "待审核的预约记录如下：" << endl;
	int index = 1;
	vector<int> v;
	for (int i = 1; i <= order.m_size; i++)
	{
		if (order.m_orderData[i]["status"] == "1")
		{//只能审核状态为审核中的记录
			flag = 1;
			v.push_back(i);
			cout << "第" << index++ << "条记录：";
			cout << "预约日期：周" << order.m_orderData[i]["date"];
			cout << "、时间段：" << (order.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << "、学号：" << order.m_orderData[i]["stuId"];
			cout << "、姓名：" << order.m_orderData[i]["stuName"];
			cout << "、机房号：" << order.m_orderData[i]["roomId"];
			cout << "、状态：审核中" << endl;
		}
	}
	if (flag == 0)
	{
		cout << "没有待审核的预约" << endl;
		system("pause");
		system("cls");
		return;
	}
	int select;
	cout << "请输入需要审核的记录：输0返回" << endl;
	while (true)
	{
		cin >> select;
		if (select == 0)
		{
			cout << "取消审核预约成功" << endl;
			break;
		}
		else if (select > 0 && select <= index)
		{
			cout << "请输入审核结果:" << endl;
			cout << "1.通过审核" << endl;
			cout << "2.不通过审核" << endl;
			int ret = 0;
			while (true)
			{
				cin >> ret;
				if (ret == 1)
				{
					order.m_orderData[v[select - 1]]["status"] = "2";
					cout << "审核完毕" << endl;
					order.updateOrder();
					break;
				}
				else if (ret == 2)
				{
					order.m_orderData[v[select - 1]]["status"] = "-1";
					cout << "审核完毕" << endl;
					order.updateOrder();
					break;
				}
				cout << "输入有误，请重新输入" << endl;
			}
			break;
		}
		cout << "请重新输入待审核记录";
	}
	system("pause");
	system("cls");
	return;
}