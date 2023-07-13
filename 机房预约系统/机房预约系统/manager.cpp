#include"manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string password)
{
	this->m_Name = name;
	this->m_Password = password;
	this->initVector();
	this->initComputer();
}

//�˵�����
void Manager::operMenu()
{
	cout << "��ӭ����Ա�� "<< this->m_Name<<"��½��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           1.����˺�           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           2.�鿴�˺�           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           3.�鿴����           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           4.���ԤԼ           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           0.ע����½           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "����������ѡ��" << endl;
}

//����˺�
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.��ӽ�ʦ" << endl;
	string fileName;
	string tip;//��ʾid��
	string errortip;
	ofstream ofs;
	int select=0;
	cin >> select;
	if (select == 1)
	{
		tip =  "������ѧ��:" ;
		errortip = "ѧ���ظ������������룺";
		fileName = STUDENT_FILE;
	}
	else if (select == 2)
	{
		tip = "������ְ����:" ;
		errortip = "ְ�����ظ������������룺";
		fileName = TEACHER_FILE;
	}
	else
	{
		cout << "������󣬷�����һ��" << endl;
		return;
	}
	ofs.open(fileName, ios::out | ios::app);//��׷�ӷ�ʽд�ļ�
	int id;
	string name;
	string password;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		//�ж�id���Ƿ��ظ�
		bool ret = this->checkRepeat(id, select);
		if (ret)//�ظ�
		{
			cout << errortip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> password;
	//���ļ���д��
	ofs << id << " " << name << " " << password << endl;
	cout << "��ӳɹ�" << endl;
	//ÿ�������Ҫ��������
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
	cout << "ѧ�ţ�" << s.m_Id << " ������" << s.m_Name << " ���룺" << s.m_Password << endl;
}

void printTeacher(Teacher& t)
{
	cout << "ְ���ţ�" << t.m_EmpId << " ������" << t.m_Name << " ���룺" << t.m_Password << endl;
}
//�鿴�˺�
void Manager::showPerson()
{
	int select = 0;
	cout << "��������Ҫ�鿴����Ϣ" << endl;
	while (true)
	{
		cout << "1.ѧ��" << endl;
		cout << "2.��ʦ" << endl;
		cout << "0.ȡ���鿴" << endl;
		cin >> select;
		if (select == 1)
		{
			cout << "ѧ���˺���Ϣ����:" << endl;
			for_each(this->vStu.begin(), this->vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "��ʦ�˺���Ϣ����:" << endl;
			for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
			break;
		}
		else if(select ==0)
		{
			break;
		}
		else
		{
			cout << "������������������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void printComputerRoom(ComputerRoom &c)
{
	cout << "�������Ϊ��" << c.m_ComiId << " �����������Ϊ��" << c.m_MaxNum << endl;
}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	cout << "��������Ϊ��" << this->vCom.size() << endl;
	for_each(this->vCom.begin(), this->vCom.end(), printComputerRoom);
	system("pause");
	system("cls");
}

//�������ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "���ԤԼ�ɹ�" << endl;
	system("pause");
	system("cls");
}

//��ʼ������
void Manager::initVector()
{
	this->vStu.clear();
	this->vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Password)
	{
		this->vStu.push_back(s);
	}
	ifs.close();
	//cout << "��ǰѧ�������ǣ�" << this->vStu.size() << endl;

	Teacher t;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Password)
	{
		this->vTea.push_back(t);
	}
	ifs.close();
	//cout << "��ǰ��ʦ�����ǣ�" << this->vTea.size() << endl;
}

//ȥ�ط�װ����
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
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComiId && ifs >> com.m_MaxNum)
	{
		this->vCom.push_back(com);
	}
	ifs.close();
}