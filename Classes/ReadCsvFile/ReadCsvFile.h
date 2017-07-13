#ifndef __READ_CSV_FILE_H__
#define __READ_CSV_FILE_H__
#include "mau.h" 
#include<assert.h>//�׳��쳣�õ�
//cankao::http://blog.csdn.net/zlhy_/article/details/8764250
//using namespace std;  
//ע�⣺����ʱ�����ϽǼ���1��A��λ�õ����ݵ��±�Ϊ��0��0��
typedef unsigned long   u32;  
class ReadCsvFile
{
public:
	ReadCsvFile();
	~ReadCsvFile();
	//��ȡcsv�����������·��
	 bool LoadCSV(const char *path);
	 //�޸ı�󱣴�cvs��
    bool SaveCSV(const char *path = NULL);
	//�Ƿ��ȡ��int������
	 bool GetIntValue(u32 uiRow, u32 uiCol, int &riValue); 
	 //�Ƿ��ȡ��float������
    bool GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue); 
	//��ȡ��������ݣ�strng����
    string* GetStringValue(u32 uiRow, u32 uiCol);

	 //void GetAI_NmaeMapTable(map<int, SkillRecord> &sSkillMapTable); 
private:
	map<u32, map<u32, string> >& GetCSVMap();
	map<u32, map<u32, string> > m_stringMap;  
	//���ڷָ��ַ�������CSV����е�һ�а��չ��������һ���ַ������洢��һ��vector��  
	//����CSV��������洢�����ݵĲ�ͬ�����ظ�����  
	int GetParamFromString(string str, vector<string> &stringVec, char *delim = ",");
    string m_CSVName;  
};


#endif