#include "layer_header.h"
#include "resource/ResourceManager.h"
#include "mau.h"
#include "tools/TimeTools.h"
GameLayer::GameLayer()
{
	srand((unsigned int )TimeTools::getInstance()->getCurTime().cur_mtime);
}

GameLayer::~GameLayer()
{
	this->releaseResource();
	CCLOG("game layer delete");
}

bool GameLayer::init()
{
	BaseLayer::init();

	return true;
}
list<LoadItem> GameLayer::getResourceList()
{
	list<LoadItem> lst = BaseLayer::getResourceList();
	lst.push_back(LoadItem(LoadType::PLIST, "plist/CardsPile/NewUi0.plist"));
	lst.push_back(LoadItem(LoadType::UI, "ui/fight/window_score_1.ExportJson"));
	lst.push_back(LoadItem(LoadType::UI, "ui/fight/ui_game_over_1.ExportJson"));
	lst.push_back(LoadItem(LoadType::UI, "ui/fight/fight.ExportJson"));
	lst.push_back(LoadItem(LoadType::UI, "ui/fight/gameMenu/gameMenu.ExportJson"));
	lst.push_back(LoadItem("animation/bgCard/NewAnimation.ExportJson",
		"animation/bgCard/NewAnimation0.png", "animation/bgCard/NewAnimation0.plist"));
	return lst;
}

void GameLayer::onEnter()
{
	BaseLayer::onEnter();
	m_FightLayer = FightLayer::create();
	this->addChild(m_FightLayer);
}
void GameLayer::releaseResource()
{
	this->removeChild(m_FightLayer);
	BaseLayer::releaseResource();
}
