#ifndef __STRING_TOOLS_H__
#define __STRING_TOOLS_H__

//�ַ���������
#include <string>
#include <list>

using namespace std;

#define SPACE_KEY_CODE		32				//�ո�ķ���
#define LIST_DELIMITER_L	"|"				//list����list��Ĭ�Ϸָ���

class StringTools
{
public:
	void static			split(string& s, string delim, list<string>& lst);	//����ַ���
	void static			replace_all(string& str, const string& old_value, const string& new_value);		//ȫ���滻
	string static		interceptString(string str, int length);		//���ݳ��ȣ�����ַ���
	list<string> static warpString(string txt, int fontSize, int width);										//�Զ������ַ���
	string static		intConvertString(int value);		//intתstring
	int static			stringConvertInt(string value);		//stringתint
	float static		stringConvertFloat(string value);
	int static			getStringWidthForShow(string txt, int fontSize);										//�����txt�ַ�������ʾ�����еĳ���    ����ʹ��

																												//������csv����Ķ���
	void static			readIntList(string& str, string delim, list<int>& lst);
	void static			readStringList(string& str, string delim, list<string>& lst);
	void static			readLstList(string& str, string delim, list<list<int>>& lst);
};


#endif
