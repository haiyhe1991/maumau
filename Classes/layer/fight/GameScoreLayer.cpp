#include "layer/layer_header.h"
#include "GameManage/GameManage.h"
#include "resource/ResourceManager.h"

GameScoreLayer::GameScoreLayer()
{
}

GameScoreLayer::~GameScoreLayer()
{
}
bool GameScoreLayer::init()
{
	if (!ShadeLayer::init())
		return false;
	layout = (Layout*)ResourceManager::GetInstance()->Get_ui_resource("ui/fight/window_score_1.ExportJson");
	this->addChild(layout);

	for (int i = 0; i < PLAYER_NUMBER; ++i)
	{
		char str[24];
		sprintf(str,"name%dLabel",i+1);
		TextBMFont *nameLabel = (TextBMFont*)layout->getChildByName(str);
		nameLabel->setString(GameManage::GetInstance()->getPlayerName(i));

		sprintf(str, "score%dLabel", i + 1);
		TextBMFont *scoreLabel = (TextBMFont*)layout->getChildByName(str);
		scoreLabel->setString(GameManage::GetInstance()->getPlayerScore(i));
	}
	continue_game = (Button*)layout->getChildByName("game_continue");
	//Ìí¼ÓÊÂ¼þ¼àÌý
	continue_game->addClickEventListener(CC_CALLBACK_1(GameScoreLayer::onContinueHandler, this));
	return true;
}

void GameScoreLayer::onContinueHandler(Ref* sender)
{
	GameManage::GetInstance()->RevursivelyResumeAllChildren(this->getParent());
	this->removeAllChildrenWithCleanup(false);
	this->removeFromParentAndCleanup(false);
}