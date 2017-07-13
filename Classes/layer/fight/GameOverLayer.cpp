#include "layer/layer_header.h"
#include "GameManage/GameManage.h"
#include "msg/message.h"
#include "resource/ResourceManager.h"

GameOverLayer::GameOverLayer()
{
}

GameOverLayer::~GameOverLayer()
{
}
bool GameOverLayer::init()
{
	if (!ShadeLayer::init())
		return false;
	layout = (Layout*)ResourceManager::GetInstance()->Get_ui_resource("ui/fight/ui_game_over_1.ExportJson");
	this->addChild(layout);

    
	if (!GameManage::GetInstance()->getPlayerWinOrLose())
	{
		ImageView* win  = (ImageView*)layout->getChildByName("win");
		win->setVisible(false);
		Button* winClickTip = (Button*)layout->getChildByName("winClickTip");
		winClickTip->setVisible(false);
		winClickTip->addClickEventListener(CC_CALLBACK_1(GameOverLayer::onExitHandler, this));
		ImageView* lose = (ImageView*)layout->getChildByName("lose");
		lose->setVisible(true);
		Button* loseClickTip = (Button*)layout->getChildByName("loseClickTip");
		loseClickTip->addClickEventListener(CC_CALLBACK_1(GameOverLayer::onExitHandler, this));
		loseClickTip->setVisible(true);

	}
	return true;
}

void GameOverLayer::onExitHandler(Ref *ob)
{
	//进入游戏加载界面，加载战斗界面资源
	MainLayer* mainLayer = MainLayer::create();
	mainLayer->retain();
	MsgManager::GetInstance()->Dispather(MessageHead::MSG_START_LOADING, mainLayer);
}