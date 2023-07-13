#include"teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int empId, string name, string password)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Password = password;
}

//��ʦ�˵�
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ�� " << this->m_Name << "��½��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           1.�鿴ԤԼ           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           2.���ԤԼ           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t |           0.ע����½           |\n";
	cout << "\t\t |                                |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "����������ѡ��" << endl;
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
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

//���ԤԼ
void Teacher::validOrder()
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
	cout << "����˵�ԤԼ��¼���£�" << endl;
	int index = 1;
	vector<int> v;
	for (int i = 1; i <= order.m_size; i++)
	{
		if (order.m_orderData[i]["status"] == "1")
		{//ֻ�����״̬Ϊ����еļ�¼
			flag = 1;
			v.push_back(i);
			cout << "��" << index++ << "����¼��";
			cout << "ԤԼ���ڣ���" << order.m_orderData[i]["date"];
			cout << "��ʱ��Σ�" << (order.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << "��ѧ�ţ�" << order.m_orderData[i]["stuId"];
			cout << "��������" << order.m_orderData[i]["stuName"];
			cout << "�������ţ�" << order.m_orderData[i]["roomId"];
			cout << "��״̬�������" << endl;
		}
	}
	if (flag == 0)
	{
		cout << "û�д���˵�ԤԼ" << endl;
		system("pause");
		system("cls");
		return;
	}
	int select;
	cout << "��������Ҫ��˵ļ�¼����0����" << endl;
	while (true)
	{
		cin >> select;
		if (select == 0)
		{
			cout << "ȡ�����ԤԼ�ɹ�" << endl;
			break;
		}
		else if (select > 0 && select <= index)
		{
			cout << "��������˽��:" << endl;
			cout << "1.ͨ�����" << endl;
			cout << "2.��ͨ�����" << endl;
			int ret = 0;
			while (true)
			{
				cin >> ret;
				if (ret == 1)
				{
					order.m_orderData[v[select - 1]]["status"] = "2";
					cout << "������" << endl;
					order.updateOrder();
					break;
				}
				else if (ret == 2)
				{
					order.m_orderData[v[select - 1]]["status"] = "-1";
					cout << "������" << endl;
					order.updateOrder();
					break;
				}
				cout << "������������������" << endl;
			}
			break;
		}
		cout << "�������������˼�¼";
	}
	system("pause");
	system("cls");
	return;
}