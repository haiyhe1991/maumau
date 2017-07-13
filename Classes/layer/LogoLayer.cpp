#include "layer_header.h"
#include "tools/TickManager.h"
#include "msg/message.h"


LogoLayer::~LogoLayer()
{
	CCLOG("logo layer delete");
}

// on "init" you need to initialize your instance
bool LogoLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	GameTick::SetDelayTime(LOGO_LAYER_SHOW_TIME);
	TickManager::GetInstance()->Reg(this);

	Layout* logo = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("ui/logo/logo.ExportJson"));
	this->addChild(logo);

    return true;
}

void LogoLayer::OnTick(int time)
{
	TickManager::GetInstance()->Unreg(this);
	MainLayer* mainLayer = MainLayer::create();
	mainLayer->retain();
	MsgManager::GetInstance()->Dispather(MessageHead::MSG_START_LOADING, mainLayer);
}



/*void LogoLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}*/
