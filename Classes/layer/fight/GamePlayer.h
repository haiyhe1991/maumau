#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include "mau.h"
#include "tools/TickManager.h"

#define PLAYER_TICK_TIME				1000

class GameCard;

//玩家状态
enum PlayerState
{
	WAITING,		//等待
	PLAYING,		//出牌
	ASKING,			//询问花色
};

//玩家类
class GamePlayer : public GameTick
{
public:
	GamePlayer()
	{
		isRobot = true;
		state = PlayerState::WAITING;
		SetDelayTime(PLAYER_TICK_TIME);
	};


	bool					isRobot;

public:

	virtual void			OnTick(int time);

	void					handCard(GameCard* card);			//发牌

	void					changeState(PlayerState state);		//改变状态

private:
	PlayerState				state;								//当前玩家的状态

	list<GameCard*>			handLst;							//手牌存储

};

#endif
