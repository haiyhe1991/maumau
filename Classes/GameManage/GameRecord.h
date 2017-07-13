#ifndef __GAME_RECORD_H__
#define __GAME_RECORD_H__
#include "mau.h"
enum MOOD_FILE_WRITE_OR_READ
{
	fileReadbasical,
	fileWritebasical
};

//���ݴ洢�����ں����ݹ������Ӧ�Ľӿ�
class GameRecord
{
public:
	
	static GameRecord* GetInstance();                       //ȡ�ô洢�����Ψһʵ��
	static void RecoverInstance();                          //���ٵ�ǰʵ��
	~GameRecord();
	/* ���ܣ���ȡ���ж��ļ��Ƿ���ڣ�
	�������ļ���
	����ֵ���ļ����ڹر��ļ����ҷ����棬�ļ������ڷ��ؼ١�
	**/
	bool JudgeFileExist(const char* name);
	 /*****�������ܣ�����������ļ������ڣ��򴴽�һ���������ļ���������ھ�ֱ�ӷ��ظ��ļ�ָ��
	 �������ļ�������дģʽ��
	 ����ֵ����Ӧ�ļ������ļ�ָ��
	 *****/
	FILE* FileWriteOrRead(const char* name, MOOD_FILE_WRITE_OR_READ op);
	//��������
	void LoadData();
	//��������
	void SaveData();
	//����string��������
	std::string LoadDataOfString(FILE *pfile);
	//����string���͵�����
	void SaveDataOfString(FILE* pfile, const std::string& str);
	//����int���͵�����
	int LoadDataOfInt(FILE *pfile);
	//����int���͵�����
	void SaveDataOfInt(FILE* pfile, const int& num);
	//����float���͵�����
	float LoadDataOfFloat(FILE *pfile);
	//����float���͵�����
     void SaveDataOfFloat(FILE* pfile, const float& num);
	//����bool���͵�����
	bool LoadDataOfBool(FILE *pfile);
	//����bool���͵�����
	void SaveDataOfBool(FILE* pfile, const bool& num);
	//��resouce�µ��ļ��������ܶ�д��������
	const char* GetDataPath(const char* path);
private:
	static GameRecord* m_pSingleInstance;
	GameRecord();

};
#endif