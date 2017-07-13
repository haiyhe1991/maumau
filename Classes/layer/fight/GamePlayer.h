#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include "mau.h"
#include "tools/TickManager.h"

#define PLAYER_TICK_TIME				1000

class GameCard;

//���״̬
enum PlayerState
{
	WAITING,		//�ȴ�
	PLAYING,		//����
	ASKING,			//ѯ�ʻ�ɫ
};

//�����
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

	void					handCard(GameCard* card);			//����

	void					changeState(PlayerState state);		//�ı�״̬

private:
	PlayerState				state;								//��ǰ��ҵ�״̬

	list<GameCard*>			handLst;							//���ƴ洢

};

#endif
