#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "mau.h"
#include "BaseLayer.h"

//�����水ť��
class ButtonLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ButtonLayer);

private:
	Layout*					layout;					//��ť����Դ
	Button*					start_game;				//��ʼ��Ϸ��ť

	void					onStartHandler(Ref* sender);	//����Ĵ����¼�
};

class MainLayer : public BaseLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainLayer);
	~MainLayer();

	virtual void onEnter();							//��ʼ������

	virtual list<LoadItem> getResourceList();			//ȡ����Դ�����б�

	virtual void releaseResource();					//�ͷ���Դ

private:
	ButtonLayer*				buttonLayer;		//�����ı�������					

};

#endif
