#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <map>
#include <list>

using namespace std;

enum MessageHead
{
	MSG_START_LOGO						= 1000,
	MSG_CHANGE_SCENE					= 1001,			//切换场景信息   封装之后，不存在场景了，只有各种层
	MSG_START_LOADING					= 1002,			//开始加载界面 

	MSG_START_GAME						= 2000,			//开始游戏
	MSG_ACTION_CHESS					= 2001,			//玩家动作
};

//游戏中的通信接口
class GameMessage
{
public:

	virtual void OnMessage(const int head, void* data) = 0;			//接收到消息
};

//消息管理器
class MsgManager
{
public:
	static MsgManager*			GetInstance();
	static void					DestoryInstance();

	void						Reg(const int head, GameMessage* msg);				//注册消息

	void						Unreg(const int head, GameMessage* msg);			//注销消息

	void						Dispather(const int head, void* data);				//发送消息

	void						Clear();											//清除所有消息

private:
	static MsgManager*				_instance;

	map<int, list<GameMessage*>>	container;					//消息管理容器
};

#endif
