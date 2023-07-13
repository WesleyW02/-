#include"student.h"

Student::Student()//Ĭ�Ϲ���
{

}

//�вι��� ѧ�š�����������
Student::Student(int id, string name, string password)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Password = password;
	this->initComputerRoom();
}
//�˵�����

void Student::operMenu()
{
	cout << "��ӭѧ���� " << this->m_Name << "��½��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           1.����ԤԼ           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           2.�鿴����           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           3.�鿴����           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           4.ȡ��ԤԼ           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           0.ע����½           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "����������ѡ��" << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ������һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
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
		cout << "������������������ԤԼʱ�䣺" << endl;
	}
	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "������������������ԤԼʱ��Σ�" << endl;
	}
	cout << "��ѡ�������" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComiId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vCom.size())
		{
			break;
		}
		cout << "��������������ѡ�����" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;
	//д���ļ�
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);//׷�ӷ�ʽ��
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

// �鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile order;
	if (order.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	int flag = 0;
	for (int i = 1; i <= order.m_size; i++)
	{
		if (atoi(order.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{//�ҵ�����ԤԼ��C++stringתΪint�ͣ���c_str()תΪchar*��Ȼ����atoiתΪint
			flag = 1;
			cout << "ԤԼ���ڣ���" << order.m_orderData[i]["date"];
			cout << "��ʱ��Σ�" << (order.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << "�������ţ�" << order.m_orderData[i]["roomId"];
			string  status = "��״̬��";
			if (order.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (order.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (order.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else if (order.m_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
	if (flag == 0)
	{
		cout << "δ�ҵ�����ԤԼ��¼" << endl;
	}
	system("pause");
	system("cls");
	return;
}

// �鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile order;
	if (order.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 1; i <= order.m_size; i++)
	{
		cout << "��" << i << "����¼��";
		cout << "ԤԼ���ڣ���" << order.m_orderData[i]["date"];
		cout << "��ʱ��Σ�" << (order.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << "��ѧ�ţ�" << order.m_orderData[i]["stuId"];
		cout << "��������" << order.m_orderData[i]["stuName"];
		cout << "�������ţ�" << order.m_orderData[i]["roomId"];
		string  status = "��״̬��";
		if (order.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (order.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (order.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else if (order.m_orderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
	return;
}

// ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile order;
	if (order.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����к�ԤԼ�ɹ��ļ�¼����ȡ����������ʾ��" << endl;
	vector<int> v;
	int index = 1;
	int flag = 0;
	for (int i = 1; i <= order.m_size; i++)
	{
		if (atoi(order.m_orderData[i]["stuId"].c_str()) == this->m_Id)
		{//ֻ��ȡ���Լ���ԤԼ
			if ((order.m_orderData[i]["status"] == "1") || (order.m_orderData[i]["status"] == "2"))
			{
				flag = 1;
				v.push_back(i);
				cout << index++ << ":";
				cout << "ԤԼ���ڣ���" << order.m_orderData[i]["date"];
				cout << "��ʱ��Σ�" << (order.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << "�������ţ�" << order.m_orderData[i]["roomId"];
				string  status = "��״̬��";
				if (order.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (order.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}
	if (flag == 0)
	{
		cout << "�޿���ȡ����ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��������Ҫȡ����ԤԼ��" << endl;
	cout << "����0��ȡ�����β���" << endl;
	int select;
	while (true)
	{
		cin >> select;
		if (select == 0)
		{
			cout << "ȡ�����β����ɹ�" << endl;
			break;
		}
		if (select > 0 && select <= index)
		{
			order.m_orderData[v[select - 1]]["status"] = "0";
			order.updateOrder();
			cout << "ȡ��ԤԼ�ɹ�" << endl;
			break;
		}
		cout << "�������������ѡ����Ҫȡ����ԤԼ" << endl;
	}
	system("pause");
	system("cls");
	return;
}

//��ʼ��������Ϣ
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