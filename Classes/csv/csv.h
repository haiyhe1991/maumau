#ifndef __CSV_H__
#define __CSV_H__

#include <list>
#include <string>
#include <map>
#include "tools/StringTools.h"

using namespace std;

class CSV
{
protected:
	//����������
	void init(const std::string fileName, const int skip);
	virtual void parserData(string value) = 0;
	void readIntList(string& str, string delim, list<int>& lst);
	void readStringList(string& str, string delim, list<string>& lst);
};

struct NameCsvItem
{
	int				id;
	string			name;
	string			portrait;			//ͷ��
};

class NameCsv : public CSV
{
public:
	NameCsv(){
		init("CSV_data/namelist.csv", 2);
	};

	NameCsvItem*	GetRandomName();

protected:
	list<int>		cacheLst;					//�����Ѿ��������ID��ֱ�ӱ����ظ�

	bool			hasCache(int id);
	virtual void	parserData(string value);

private:
	map<int, NameCsvItem*> container;

};

//csv���ݴ洢��
class CsvData
{
public:
	CsvData();

	NameCsv*				nameCsv;

public:
	static CsvData*			GetInstance();
	static void				DestoryInstance();

private:
	static CsvData*			_instance;
};

#endif
