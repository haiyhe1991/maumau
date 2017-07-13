#include "layer/layer_header.h"
#include "GameManage/GameManage.h"
#include "msg/message.h"
#include "resource/ResourceManager.h"

GameMenuLayer::GameMenuLayer()
{

}

GameMenuLayer::~GameMenuLayer()
{

}

bool GameMenuLayer::init()
{
	if (!ShadeLayer::init())
		return false;
	layout = (Layout*)ResourceManager::GetInstance()->Get_ui_resource("ui/fight/gameMenu/gameMenu.ExportJson");
	this->addChild(layout);
	rule_game = (Button*)layout->getChildByName("Button_gameRule");
	//����¼�����
	rule_game->addClickEventListener(CC_CALLBACK_1(GameMenuLayer::onRuleHandler, this));

	setup_game = (Button*)layout->getChildByName("Button_gameSetup");
	//����¼�����
	setup_game->addClickEventListener(CC_CALLBACK_1(GameMenuLayer::onSetupHandler, this));

	acheivement_game = (Button*)layout->getChildByName("Button_acheviement");
	//����¼�����
	acheivement_game->addClickEventListener(CC_CALLBACK_1(GameMenuLayer::onAcheivementHandler, this));

	exit_game = (Button*)layout->getChildByName("Button_exit");
	//����¼�����
	exit_game->addClickEventListener(CC_CALLBACK_1(GameMenuLayer::onExitHandler, this));

	continue_game = (Button*)layout->getChildByName("Button_continue");
	//����¼�����
	continue_game->addClickEventListener(CC_CALLBACK_1(GameMenuLayer::onContinueHandler, this));
	return true;
}
void GameMenuLayer::onRuleHandler(Ref* sender)
{
	CCLOG("Button_gameRule");
}
void GameMenuLayer::onAcheivementHandler(Ref* sender)
{
	CCLOG("Button_acheviement");
}
void GameMenuLayer::onSetupHandler(Ref* sender)
{
	CCLOG("Button_gameSetup");
}
void GameMenuLayer::onExitHandler(Ref* sender)
{
	MainLayer* mainLayer = MainLayer::create();
	mainLayer->retain();
	MsgManager::GetInstance()->Dispather(MessageHead::MSG_START_LOADING, mainLayer);
}
void GameMenuLayer::onContinueHandler(Ref* sender)
{
	GameManage::GetInstance()->RevursivelyResumeAllChildren(this->getParent());
	this->removeAllChildrenWithCleanup(false);
	this->removeFromParentAndCleanup(false);
}