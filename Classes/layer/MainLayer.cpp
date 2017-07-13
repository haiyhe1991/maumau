#include "layer_header.h"
#include "resource/ResourceManager.h"

MainLayer::~MainLayer()
{
	releaseResource();
	CCLOG("main layer delete");
}

bool MainLayer::init()
{
	Layer::init();
	
	return true;
}

list<LoadItem> MainLayer::getResourceList()
{
	list<LoadItem> lst = BaseLayer::getResourceList();
	lst.push_back(LoadItem(LoadType::UI, "ui/main/main.ExportJson"));
	return lst;
}

void MainLayer::onEnter()
{
	BaseLayer::onEnter();
	buttonLayer = ButtonLayer::create();
	this->addChild(buttonLayer);
}

void MainLayer::releaseResource()
{
	this->removeChild(buttonLayer);
	BaseLayer::releaseResource();
}
