#ifndef __GAME_MANAGE_H__
#define __GAME_MANAGE_H__
#include "mau.h"
//游戏对战时的数据管理，
class GameManage
{
public:
	
	~GameManage();
	static GameManage* GetInstance();                       //取得数据管理的唯一实例
	static void RecoverInstance();                          //销毁当前实例

	
	//功能函数 重启当前节点 以及所有子节点及其所有下属节点
	void RevursivelyResumeAllChildren(Node *node);
	// 功能函数 暂停当前节点 以及所有子节点及其所有下属节点
	void RevursivelyPauseAllChildren(Node * node );
	//记录玩家名字
	void setPlayerName(string playerName,int index);
	string getPlayerName(int index);
	//记录玩家得分
	void setPlayerScore(string playerScore, int index);
	string getPlayerScore(int index);
	//玩家是输了还是赢了
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
