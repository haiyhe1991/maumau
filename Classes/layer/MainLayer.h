#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "mau.h"
#include "BaseLayer.h"

//主界面按钮层
class ButtonLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ButtonLayer);

private:
	Layout*					layout;					//按钮层资源
	Button*					start_game;				//开始游戏按钮

	void					onStartHandler(Ref* sender);	//点击的处理事件
};

class MainLayer : public BaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainLayer);
	~MainLayer();

	virtual void onEnter();							//初始化函数

	virtual list<LoadItem> getResourceList();			//取得资源加载列表

	virtual void releaseResource();					//释放资源

private:
	ButtonLayer*				buttonLayer;		//场景的背景容器					

};

#endif
