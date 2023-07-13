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
	cout << "==================��ӭ��������ԤԼϵͳ==================" << endl;
	cout << endl << "�������������" << endl;
	cout << "\t\t --------------------------------\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           1.ѧ  ��           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           2.��  ʦ           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           3.����Ա           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t |           0.��  ��           |\n";
	cout << "\t\t |                              |\n";
	cout << "\t\t --------------------------------\n";
	cout << "����������ѡ��" << endl;
}

//����Ա�˵����溯�������ʵ��
void managerMenu(Identity * &manager)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->operMenu();
		//����ָ��תΪ���࣬�ɵ��������������нӿ�
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1://����˺�
			man->addPerson();
			break;
		case 2://�鿴�˺�
			man->showPerson();
			break;
		case 3://�鿴������Ϣ
			man->showComputer();
			break;
		case 4://���ԤԼ
			man->cleanFile();
			break;
		case 0://ע����½
			delete manager;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//ѧ���˵����溯�������ʵ��
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
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//��ʦ�˵�
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
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//��½������װ
void LoginIn(string fileName, int type)
{
	Identity* person;//����ָ�룬ָ���������

	//���ļ�
	ifstream  ifs;
	ifs.open(fileName, ios::in);
	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û���Ϣ
	int id = 0;
	string name;
	string password;
	if (type == 1)//ѧ��
	{
		cout << "���������ѧ��: " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "����������ְ����: " << endl;
		cin >> id;
	}
	cout << "����������û���: " << endl;
	cin >> name;
	cout << "�������������: " << endl;
	cin >> password;

	if (type == 1 || type == 2)
	{
		//ѧ�����߽�ʦ�����֤
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
					cout << " ѧ����֤��½�ɹ�" << endl;
					system("pause");
					system("cls");
					person = new Student(id, name, password);
					//����ѧ������Ӳ˵�
					StudentMenu(person);
					ifs.close();
					return;
				}
				else
				{
					cout << " ��ʦ��֤��½�ɹ�" << endl;
					system("pause");
					system("cls");
					person = new Teacher(id, name, password);
					//������ʦ����Ӳ˵�
					TeacherMenu(person);
					ifs.close();
					return;
				}
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��֤
		string fName;
		string fPassword;
		while (ifs >> fName && ifs >> fPassword)
		{
			if (fName == name && fPassword == password)
			{
				cout << " ����Ա��֤��½�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, password);
				//�������Ա����Ӳ˵�
				managerMenu(person);
				ifs.close();
				return;
			}
		}
	}
	cout << "��֤��½ʧ��" << endl;
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
		case 1://ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://�˳�ϵͳ
			cout << "��ӭ��һ��ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default :
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}