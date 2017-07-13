#include "GamePlayer.h"
#include "GameCard.h"


void GamePlayer::OnTick(int time)
{

}

void GamePlayer::handCard(GameCard* card)
{
	handLst.push_back(card);
}

void GamePlayer::changeState(PlayerState state)
{
	this->state = state;
}
