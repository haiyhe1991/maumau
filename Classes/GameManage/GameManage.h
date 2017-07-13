#ifndef __GAME_MANAGE_H__
#define __GAME_MANAGE_H__
#include "mau.h"
//��Ϸ��սʱ�����ݹ���
class GameManage
{
public:
	
	~GameManage();
	static GameManage* GetInstance();                       //ȡ�����ݹ����Ψһʵ��
	static void RecoverInstance();                          //���ٵ�ǰʵ��

	
	//���ܺ��� ������ǰ�ڵ� �Լ������ӽڵ㼰�����������ڵ�
	void RevursivelyResumeAllChildren(Node *node);
	// ���ܺ��� ��ͣ��ǰ�ڵ� �Լ������ӽڵ㼰�����������ڵ�
	void RevursivelyPauseAllChildren(Node * node );
	//��¼�������
	void setPlayerName(string playerName,int index);
	string getPlayerName(int index);
	//��¼��ҵ÷�
	void setPlayerScore(string playerScore, int index);
	string getPlayerScore(int index);
	//��������˻���Ӯ��
	void  setPlayerWinOrLose(bool bWinOrLose);
	bool  getPlayerWinOrLose();
private:
	GameManage();
	static GameManage* m_pSingleInstance;
	string m_PlayerName[4];
	string m_PlayerScore[4];
	bool m_bWinOrLose;
};
#endif
