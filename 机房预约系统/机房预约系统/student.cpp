#include"student.h"

Student::Student()//默认构造
{

}

//有参构造 学号、姓名、密码
Student::Student(int id, string name, string password)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = password;
	this->initComputerRoom();
}
//菜单界面

void Student::operMenu()
{
	cout << "欢迎学生： " << this->m_Name << "登陆！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           1.申请预约           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           2.查看自身           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           3.查看所有           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           4.取消预约           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           0.注销登陆           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请输入您的选择" << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放时间是周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入预约时间：" << endl;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "输入有误，请重新输入预约时间段：" << endl;
	}
	cout << "请选择机房：" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComiId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vCom.size())
		{
			break;
		}
		cout << "输入有误，请重新选择机房" << endl;
	}

	cout << "预约成功，审核中" << endl;
	//写入文件
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);//追加方式打开
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;
	ofs.close();
	system("pause");
	system("cls");
}

// 查看自身预约
void Student::showMyOrder()
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
	for (int i = 1; i <= order.m_size; i++)
	{
		if (atoi(order.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{//找到自身预约，C++string转为int型，用c_str()转为char*，然后用atoi转为int
			flag = 1;
			cout << "预约日期：周" << order.m_orderData[i]["date"];
			cout << "、时间段：" << (order.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
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
	}
	if (flag == 0)
	{
		cout << "未找到您的预约记录" << endl;
	}
	system("pause");
	system("cls");
	return;
}

// 查看所有预约
void Student::showAllOrder()
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

// 取消预约
void Student::cancelOrder()
{
	OrderFile order;
	if (order.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中和预约成功的记录可以取消，如下所示：" << endl;
	vector<int> v;
	int index = 1;
	int flag = 0;
	for (int i = 1; i <= order.m_size; i++)
	{
		if (atoi(order.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{//只能取消自己的预约
			if ((order.m_orderData[i]["status"] == "1") || (order.m_orderData[i]["status"] == "2"))
			{
				flag = 1;
				v.push_back(i);
				cout << index++ << ":";
				cout << "预约日期：周" << order.m_orderData[i]["date"];
				cout << "、时间段：" << (order.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
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
				cout << status << endl;
			}
		}
	}
	if (flag == 0)
	{
		cout << "无可以取消的预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入你要取消的预约：" << endl;
	cout << "输入0，取消本次操作" << endl;
	int select;
	while (true)
	{
		cin >> select;
		if (select == 0)
		{
			cout << "取消本次操作成功" << endl;
			break;
		}
		if (select > 0 && select <= index)
		{
			order.m_orderData[v[select - 1]]["status"] = "0";
			order.updateOrder();
			cout << "取消预约成功" << endl;
			break;
		}
		cout << "输入错误，请重新选择需要取消的预约" << endl;
	}
	system("pause");
	system("cls");
	return;
}

//初始化机房信息
void Student::initComputerRoom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComiId && ifs >> com.m_MaxNum)
	{
		this->vCom.push_back(com);
	}
	ifs.close();
}