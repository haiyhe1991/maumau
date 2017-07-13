#include "csv.h"

//����ģʽ
CsvData* CsvData::_instance = nullptr;

CsvData::CsvData()
{
	nameCsv = new NameCsv;
}

CsvData* CsvData::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new CsvData;
	}
	return _instance;
}

void CsvData::DestoryInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
	}
	_instance = nullptr;
}
