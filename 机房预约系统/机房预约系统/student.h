#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"globalFile.h"
#include"computerRoom.h"
#include<fstream>
#include"orderFile.h"

//ѧ����
class Student :public Identity
{
public:
	Student();//Ĭ�Ϲ���

	//�вι��� ѧ�š�����������
	Student(int id,string name,string password);
	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();
	// �鿴����ԤԼ
	void showMyOrder();
	// �鿴����ԤԼ
	void showAllOrder();
	// ȡ��ԤԼ
	void cancelOrder();
	//��ʼ��������Ϣ
	void initComputerRoom();
	 
	//ѧ��ѧ��
	int m_Id;

	//������Ϣ
	vector<ComputerRoom> vCom;
};