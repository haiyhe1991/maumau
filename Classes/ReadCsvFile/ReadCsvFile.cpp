#include "ReadCsvFile.h"
#include "errno.h"
ReadCsvFile::ReadCsvFile()
{
}

ReadCsvFile::~ReadCsvFile()
{
}
bool ReadCsvFile::LoadCSV(const char *path)  
{  
    FILE *pFile = fopen(path, "r");  
    if (pFile)  
    {  
		
        fseek(pFile, 0, SEEK_END);  //һ�����ڶ�����ģʽ�򿪵��ļ��У������Ƕ�λ������ָ����λ�á�ԭ�����£�int fseek(FILE* fp, lont offset, int whence); ����offset���ƶ����ַ�����whence���ƶ��Ļ�׼
        u32 uSize = ftell(pFile);  //�õ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ���
        rewind(pFile);  //���ǰѵ�ǰ�Ķ�дλ�ûص��ļ���ʼ���൱�� fseek(fp, 0L, SEEK_SET); ԭ�ͣ� void rewind(FILE* fp);
  
        char *fileBuffer = new char[uSize];  
        fread(fileBuffer, 1, uSize, pFile);  //size_t fread(void* ptr, size_t size, size_t n, FILE* fp); �����ж�ָ���������ַ���size��ÿ����ֽ�¦��n���Ƕ�ȡ�Ŀ�����
		//CCLOG("==============%s",fileBuffer);
        map<u32, string> stringMap;  //ÿһ�е���Ϣ���ڸ�map�У�
        u32 uiIndex = 1;  
        char *pBegin = fileBuffer;  
        char *pEnd = strchr(pBegin, '\n');  //���ܣ������ַ���pBegin���״γ����ַ�'\n'��λ��,˵���������״γ���c��λ�õ�ָ�룬���صĵ�ַ�Ǳ������ַ���ָ�뿪ʼ�ĵ�һ����Val��ͬ�ַ���ָ�룬���s�в�����c�򷵻�NULL��
 
        pBegin = pEnd + 1;  //ָ����һ���ֶ�
        pEnd = strchr(pBegin, '\n');  

        while (pEnd)  
        {  
            string strTemp;  
            strTemp.insert(0, pBegin, pEnd-pBegin);  
            assert(!strTemp.empty());  
            stringMap[uiIndex++] = strTemp; 
            pBegin = pEnd + 1;  
            pEnd = strchr(pBegin, '\n');  
        }  
        delete []fileBuffer;  
        fileBuffer = NULL;  
        pBegin = NULL;  
        pEnd = NULL;  
        map<u32, string>::iterator iter = stringMap.begin();  
		//CCLOG("+++++++%d",stringMap.size());
        for (; iter != stringMap.end(); ++iter)  
        {  
            vector<string> stringVec;  
            map<u32, string> stringMapTemp;  //װÿ�е���Ϣ
           //assert(GetParamFromString(iter->second, stringVec) > 0);  //��ÿ����Ԫ��������ݴ浽vector��
             GetParamFromString(iter->second, stringVec);
            vector<string>::size_type idx = 0;  
            for (; idx != stringVec.size(); ++idx)  
            {  
                stringMapTemp[idx] = stringVec[idx];
            }  
  
            m_stringMap[iter->first] = stringMapTemp;  
        }  
        fclose(pFile);  
        m_CSVName = path;  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
bool ReadCsvFile::SaveCSV(const char *path /* = NULL */)  
{  
    if (path != NULL)  
    {  
        m_CSVName = path;  
    }  
  
    FILE *pFile = fopen(m_CSVName.c_str(), "w");  
    if (pFile)  
    {  
        map<u32, map<u32, string> >::iterator iter = m_stringMap.begin();  
        for (; iter != m_stringMap.end(); ++iter)  
        {  
            map<u32, string> &rStringMap = iter->second;  
            map<u32, string>::iterator it = rStringMap.begin();  
            for (; it != rStringMap.end(); ++it)  
            {  
                string strTemp = it->second;  
                strTemp += ',';  
                fwrite(strTemp.c_str(), 1, 1, pFile);  
            }  
  
            char delim = '\n';  
            fwrite(&delim, 1, 1, pFile);  //һ��д������
        }  
  
        fclose(pFile);  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
bool ReadCsvFile::GetIntValue(u32 uiRow, u32 uiCol, int &riValue)  
{  
    string *pStr = GetStringValue(uiRow, uiCol);  
    if (pStr)  
    {  
      //  riValue = atoi(pStr->c_str());  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
bool ReadCsvFile::GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue)  
{  
    string *pStr = GetStringValue(uiRow, uiCol);  
    if (pStr)  
    {  
       // rfValue = atof(pStr->c_str());  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
string* ReadCsvFile::GetStringValue(u32 uiRow, u32 uiCol)  
{  
    map<u32, map<u32, string> >::iterator iter = m_stringMap.find(uiRow);  
    if (iter != m_stringMap.end())  
    {  
        map<u32, string> &rStrMap = iter->second;  
        map<u32, string>::iterator it = rStrMap.find(uiCol);  
        if (it != rStrMap.end())  
        {  
            return &(it->second);  
        }   
        else  
        {  
            return NULL;  
        }  
    }   
    else  
    {  
        return NULL;  
    }  
}  
  
//���ڷָ��ַ�������CSV����е�һ�а��չ��������һ���ַ������洢��һ��vector��  
//����CSV��������洢�����ݵĲ�ͬ�����ظ�����  
int ReadCsvFile::GetParamFromString(string str, vector<string> &stringVec, char* delim)  
{  
	//CCLOG("qweqweqeqeq%s",str.c_str());
    char *token = strtok(const_cast<char *>(str.c_str()), delim);  //strtok()�������ַ����ָ��һ����Ƭ�Ρ�����sָ�����ָ���ַ���������delim��Ϊ�ָ��ַ�������strtok()�ڲ���s���ַ����з��ֵ�����delim�ķָ��ַ�ʱ   ���� ��Ὣ���ַ���Ϊ\0 �ַ����ڵ�һ�ε���ʱ��strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��ÿ�ε��óɹ��򷵻ر��ָ��Ƭ�ε�ָ�롣
 
	while (token)  
    {  
        string strTemp = token;
		//  CCLOG("qqqqqqqqqqqqqqqq%s",token);
        stringVec.push_back(strTemp);  
        token = strtok(NULL, delim);  
    }  
	//CCLOG("asdaasa%d",stringVec.size());
    return stringVec.size();  
}  
  
//void ReadCsvFile::GetSkillRecordMapTable(map<int, SkillRecord> &sSkillMapTable)  
//{  
//    map<u32, map<u32, string>>::iterator iter = m_stringMap.begin();  
//    for (; iter != m_stringMap.end(); ++iter)  
//    {  
//        map<u32, string> strmap = iter->second;  
//        SkillRecord skillTemp;  
//        skillTemp.SetID(atoi(strmap[1].c_str()));  
//        skillTemp.SetPath(strmap[2]);  
//        skillTemp.SetName(strmap[3]);  
//        skillTemp.SetHurt(atoi(strmap[4].c_str()));  
//        skillTemp.SetPlayTime(atoi(strmap[5].c_str()));  
//  
//        sSkillMapTable[skillTemp.GetID()] = skillTemp;  
//    }  
//}  