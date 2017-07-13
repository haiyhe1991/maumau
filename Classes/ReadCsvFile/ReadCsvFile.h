#ifndef __READ_CSV_FILE_H__
#define __READ_CSV_FILE_H__
#include "mau.h" 
#include<assert.h>//抛出异常用的
//cankao::http://blog.csdn.net/zlhy_/article/details/8764250
//using namespace std;  
//注意：读表时，左上角即（1，A）位置的数据的下标为（0，0）
typedef unsigned long   u32;  
class ReadCsvFile
{
public:
	ReadCsvFile();
	~ReadCsvFile();
	//读取csv表，参数：表的路径
	 bool LoadCSV(const char *path);
	 //修改表后保存cvs表
    bool SaveCSV(const char *path = NULL);
	//是否读取到int型数据
	 bool GetIntValue(u32 uiRow, u32 uiCol, int &riValue); 
	 //是否读取到float型数据
    bool GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue); 
	//获取到表的内容，strng类型
    string* GetStringValue(u32 uiRow, u32 uiCol);

	 //void GetAI_NmaeMapTable(map<int, SkillRecord> &sSkillMapTable); 
private:
	map<u32, map<u32, string> >& GetCSVMap();
	map<u32, map<u32, string> > m_stringMap;  
	//用于分割字符串，将CSV表格中的一行按照规则解析成一组字符串，存储在一个vector中  
	//根据CSV表格中所存储的数据的不同，重载各函数  
	int GetParamFromString(string str, vector<string> &stringVec, char *delim = ",");
    string m_CSVName;  
};


#endif