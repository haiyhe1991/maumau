#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "mau.h"
#include "tools/TickManager.h"


//logo ������ʾʱ��
#define LOGO_LAYER_SHOW_TIME			3000				//�ݶ�Ϊ3��

//logo����

class LogoLayer : public Layer, GameTick
{
public:
    virtual bool init();
    
	~LogoLayer();

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
	// ��ʱ�� �ص�����
	virtual void OnTick(int time);

    // implement the "static create()" method manually
	CREATE_FUNC(LogoLayer);

private:
	int						count;
};

#endif // __HELLOWORLD_SCENE_H__
