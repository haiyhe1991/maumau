#include "GameManage.h"
//#include "ClientSocket/CGameSocket.h"
GameManage *GameManage::m_pSingleInstance=NULL;
GameManage* GameManage::GetInstance()
{
	if(m_pSingleInstance==NULL)
	{
	 m_pSingleInstance=new GameManage();
	}
	return m_pSingleInstance;
}

GameManage::GameManage()
{
	m_PlayerName[0] = "Player";
}

GameManage::~GameManage()
{

}

void GameManage::RecoverInstance()
{
	CC_SAFE_DELETE(m_pSingleInstance);
}

void GameManage::RevursivelyPauseAllChildren( Node * node )
{
	node->pauseSchedulerAndActions();
	for (Vector<cocos2d::Node*>::const_iterator it = (node->getChildren()).begin(); it != (node->getChildren()).end(); ++it)
	{
		RevursivelyPauseAllChildren(*it);
	}
}

void GameManage::RevursivelyResumeAllChildren( Node *node )
{
	node->resumeSchedulerAndActions();
	for (Vector<cocos2d::Node*>::const_iterator it = (node->getChildren()).begin(); it != (node->getChildren()).end(); ++it)
	{
		RevursivelyResumeAllChildren(*it);
	}
}
void GameManage::setPlayerName(string playerName, int index)
{
	m_PlayerName[index] = playerName;
}
string GameManage::getPlayerName(int index)
{
	return m_PlayerName[index];
}
void GameManage::setPlayerScore(string playerScore, int index)
{
	m_PlayerScore[index] = playerScore;
}
string GameManage::getPlayerScore(int index)
{
	return m_PlayerScore[index];
}
void GameManage::setPlayerWinOrLose(bool bWinOrLose)
{
	m_bWinOrLose = bWinOrLose;
}
bool GameManage::getPlayerWinOrLose()
{
	return m_bWinOrLose;
}

