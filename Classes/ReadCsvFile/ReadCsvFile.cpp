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
		
        fseek(pFile, 0, SEEK_END);  //一般用于二进制模式打开的文件中，功能是定位到流中指定的位置。原型如下：int fseek(FILE* fp, lont offset, int whence); 参数offset是移动的字符数，whence是移动的基准
        u32 uSize = ftell(pFile);  //得到文件位置指针当前位置相对于文件首的偏移字节数
        rewind(pFile);  //则是把当前的读写位置回到文件开始，相当于 fseek(fp, 0L, SEEK_SET); 原型： void rewind(FILE* fp);
  
        char *fileBuffer = new char[uSize];  
        fread(fileBuffer, 1, uSize, pFile);  //size_t fread(void* ptr, size_t size, size_t n, FILE* fp); 从流中读指定个数的字符，size是每块的字节娄，n则是读取的块数。
		//CCLOG("==============%s",fileBuffer);
        map<u32, string> stringMap;  //每一行的信息存在该map中，
        u32 uiIndex = 1;  
        char *pBegin = fileBuffer;  
        char *pEnd = strchr(pBegin, '\n');  //功能：查找字符串pBegin中首次出现字符'\n'的位置,说明：返回首次出现c的位置的指针，返回的地址是被查找字符串指针开始的第一个与Val相同字符的指针，如果s中不存在c则返回NULL。
 
        pBegin = pEnd + 1;  //指向下一个字段
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
            map<u32, string> stringMapTemp;  //装每行的信息
           //assert(GetParamFromString(iter->second, stringVec) > 0);  //将每个单元格里的内容存到vector中
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
            fwrite(&delim, 1, 1, pFile);  //一行写完加这个
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
  
//用于分割字符串，将CSV表格中的一行按照规则解析成一组字符串，存储在一个vector中  
//根据CSV表格中所存储的数据的不同，重载各函数  
int ReadCsvFile::GetParamFromString(string str, vector<string> &stringVec, char* delim)  
{  
	//CCLOG("qweqweqeqeq%s",str.c_str());
    char *token = strtok(const_cast<char *>(str.c_str()), delim);  //strtok()用来将字符串分割成一个个片段。参数s指向欲分割的字符串，参数delim则为分割字符串，当strtok()在参数s的字符串中发现到参数delim的分割字符时   　　 则会将该字符改为\0 字符。在第一次调用时，strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL。每次调用成功则返回被分割出片段的指针。
 
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