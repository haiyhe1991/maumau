#include "layer/layer_header.h"
#include "resource/ResourceManager.h"
#include "msg/message.h"

bool ButtonLayer::init()
{
	Layer::init();
	layout = (Layout*)ResourceManager::GetInstance()->Get_ui_resource("ui/main/main.ExportJson");
	this->addChild(layout);

	start_game = (Button*)layout->getChildByName("start_button");
	//添加事件监听
	start_game->addClickEventListener(CC_CALLBACK_1(ButtonLayer::onStartHandler, this));

	return true;
}

void ButtonLayer::onStartHandler(Ref* sender)
{
	//进入游戏加载界面，加载战斗界面资源
	GameLayer* gameLayer = GameLayer::create();
	gameLayer->retain();
	MsgManager::GetInstance()->Dispather(MessageHead::MSG_START_LOADING, gameLayer);
}

