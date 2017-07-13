#ifndef __GAME_CARD_H__
#define __GAME_CARD_H__

#include "mau.h"

enum CardColor
{
	SPADES = 1,
	HEARTS,
	CLUBS,
	DIAMONDS
};

enum CardState
{
	HEAP = 1,		//���ƶ���
	HAND,			//���������
};

enum CardNumber
{
	CARD_A = 1,
	CARD_2,
	CARD_3,
	CARD_4,
	CARD_5,
	CARD_6,
	CARD_7,
	CARD_8,
	CARD_9,
	CARD_10,
	CARD_J,
	CARD_Q,
	CARD_K
};

enum DealCardStyle
{
	StartDealCard,
	AddTempDealCard,
	PunlishCard,
};

//��
class GameCard
{
public:
	GameCard()
	{
		state = CardState::HEAP;
	};

	void						initCard(CardColor color, CardNumber number);
	
	CardColor					getColor();

	CardNumber					getNumber();

	CardState					getState();

	void						changeState(CardState state);

	bool						isSameColor(CardColor color);

private:

	CardColor					color;

	CardNumber					number;

	CardState					state;

};

//�ƹ�����
class CardManager
{
public:
	~CardManager();

	void						createCard();		//������

	void						washCard();			//ϴ��

	GameCard*					deliverCard();		//���ƺ���

private:
	vector<GameCard>			container;

	int							index;

};

#endif
