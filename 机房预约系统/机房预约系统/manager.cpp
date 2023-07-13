#include"manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string password)
{
	this->m_Name = name;
	this->m_Password = password;
	this->initVector();
	this->initComputer();
}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员： "<< this->m_Name<<"登陆！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           1.添加账号           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           2.查看账号           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           3.查看机房           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           4.清空预约           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           0.注销登陆           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请输入您的选择" << endl;
}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加教师" << endl;
	string fileName;
	string tip;//提示id号
	string errortip;
	ofstream ofs;
	int select=0;
	cin >> select;
	if (select == 1)
	{
		tip =  "请输入学号:" ;
		errortip = "学号重复，请重新输入：";
		fileName = STUDENT_FILE;
	}
	else if (select == 2)
	{
		tip = "请输入职工号:" ;
		errortip = "职工号重复，请重新输入：";
		fileName = TEACHER_FILE;
	}
	else
	{
		cout << "输入错误，返回上一级" << endl;
		return;
	}
	ofs.open(fileName, ios::out | ios::app);//以追加方式写文件
	int id;
	string name;
	string password;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		//判断id号是否重复
		bool ret = this->checkRepeat(id, select);
		if (ret)//重复
		{
			cout << errortip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> password;
	//向文件中写入
	ofs << id << " " << name << " " << password << endl;
	cout << "添加成功" << endl;
	//每次添加需要更新容器
	if (select == 1)
	{
		Student s(id, name, password);
		this->vStu.push_back(s);
	}
	else
	{
		Teacher t(id, name, password);
		this->vTea.push_back(t);
	}
	system("pause");
	system("cls");
	ofs.close();
	return;
}

void printStudent(Student &s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Password << endl;
}

void printTeacher(Teacher& t)
{
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Password << endl;
}
//查看账号
void Manager::showPerson()
{
	int select = 0;
	cout << "请输入需要查看的信息" << endl;
	while (true)
	{
		cout << "1.学生" << endl;
		cout << "2.老师" << endl;
		cout << "0.取消查看" << endl;
		cin >> select;
		if (select == 1)
		{
			cout << "学生账号信息如下:" << endl;
			for_each(this->vStu.begin(), this->vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "老师账号信息如下:" << endl;
			for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
			break;
		}
		else if(select ==0)
		{
			break;
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}
	}
	system("pause");
	system("cls");
}

void printComputerRoom(ComputerRoom &c)
{
	cout << "机房编号为：" << c.m_ComiId << " 机房最大容量为：" << c.m_MaxNum << endl;
}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	cout << "机房数量为：" << this->vCom.size() << endl;
	for_each(this->vCom.begin(), this->vCom.end(), printComputerRoom);
	system("pause");
	system("cls");
}

//清空所有预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空预约成功" << endl;
	system("pause");
	system("cls");
}

//初始化容器
void Manager::initVector()
{
	this->vStu.clear();
	this->vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Password)
	{
		this->vStu.push_back(s);
	}
	ifs.close();
	//cout << "当前学生数量是：" << this->vStu.size() << endl;

	Teacher t;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Password)
	{
		this->vTea.push_back(t);
	}
	ifs.close();
	//cout << "当前老师数量是：" << this->vTea.size() << endl;
}

//去重封装函数
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = this->vStu.begin(); it != this->vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = this->vTea.begin(); it != this->vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

void Manager::initComputer()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComiId && ifs >> com.m_MaxNum)
	{
		this->vCom.push_back(com);
	}
	ifs.close();
}