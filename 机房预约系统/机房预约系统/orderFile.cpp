#include"orderFile.h"

void divideString(string str, map<string, string> &m)
{
	string key, value;
	int pos = str.find(":");
	if (pos != -1)
	{
		key = str.substr(0, pos);
		value = str.substr(pos + 1, str.length() - 1);
		m.insert(make_pair(key, value));
	}
}

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date, interval, stuId, stuName, roomId, status;
	this->m_size = 0;
	while (ifs >> date && ifs >> interval && ifs
		>> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//切分函数
		map<string, string> m;
		divideString(date, m);
		divideString(interval, m);
		divideString(stuId, m);
		divideString(stuName, m);
		divideString(roomId, m);
		divideString(status, m);
		//测试m
		/*for (map<string, string>::iterator it = m.begin(); it != m.end(); it++)
		{
			cout << "key = " << it->first << " value = " << it->second << " ";
		}
		cout << endl;*/
		this->m_orderData.insert(make_pair(++this->m_size, m));
	}
	ifs.close();
	//测试this->m_orderData
	/*for (map<int, map<string, string>>::iterator it = this->m_orderData.begin(); it != this->m_orderData.end(); it++)
	{
		cout << "条数：" << it->first << " 记录为：" << endl;
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << "key = " << mit->first << " value = " << mit->second << " ";
		}
		cout << endl;
	}*/

}

//更新预约记录文件
void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 1; i <= this->m_size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] <<endl;
	}
}