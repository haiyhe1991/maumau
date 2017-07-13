#ifndef __SPRITE_BUTTON_H__
#define __SPRITE_BUTTON_H__
#include "mau.h"
class SpriteButton:public Layer
{
public:
	SpriteButton();
	~SpriteButton();
	virtual bool init();
	//����֡����������
	static SpriteButton* createWithFrame(SpriteFrame* frameNormal,SpriteFrame* frameHighlight=NULL,SpriteFrame* frameDisable=NULL);
	//����ͼƬ��������������
	static SpriteButton* createWithSprite(Sprite* sprite);

	//���ð��½�ִ�еĻص�����
	virtual void setPressedDownHandler(Ref *object, SEL_MenuHandler handle);
	//���ð����ɿ�ִ�еĻص�����
	virtual void setPressedUpHandler(Ref* object, SEL_MenuHandler handle);
	//���ð������Ų���ʱ�����ھ��鷶Χ��ִ�еĻص�����
	virtual void setPressedMoveInsideHandler(Ref *object, SEL_MenuHandler handle);
	//���ð������Ų���ʱ�����ھ��鷶Χ��ִ�еĻص�����
	virtual void setPressedMoveOutsideHandler(Ref *object, SEL_MenuHandler handle);
	//���ð����Ƿ���
	virtual void setIsShock(bool bShock);
	//��ȡ�Ƿ���
	virtual bool getIsShock();
	//�ı侫��ͼƬ��ͨ��ʾʱ��ͼƬ֡
	virtual void setNormalFrame(SpriteFrame *frame);
	//���ð���ʧЧʱ����䰵����ɫ
	virtual void setUnableColor(Color3B color);
	//�����Ƿ���Ӧ��������
	virtual void setEnable(bool bIsEnable);
	CREATE_FUNC(SpriteButton);
protected:
	//��ʼ����ť
	virtual void initWithFrame(SpriteFrame* frameNormal,SpriteFrame* frameHighlight,SpriteFrame* frameDisable);
	//�Ƿ�����ͼƬ������������ť
	bool m_bSpriteMode;
	//��ť������ʾʱ�õ�֡
	SpriteFrame *m_pFrameNormal;
	//��ť���¾���ʾ��֡
	SpriteFrame *m_pFrameHighlight;
	//��ť��Чʱ��֡
	SpriteFrame *m_pFrameDisable;
	//��ť����
	Sprite *m_pSprite;
	//ִ�а�ť���»ص������Ķ���
	Ref *m_pPressedDownHandleObject;
	//��ť���µĻص�����
	SEL_MenuHandler m_pPressedDownHandle;
	//ִ�а�ť���º���Ļص������Ķ���
	Ref *m_pPressedUpHandleObject;
	//��ť���º���Ļص�����
	SEL_MenuHandler m_pPressedUpHandle;
	//��ť���Ų��Ų����ڰ�ť��Χ�ڵĶ���
	Ref *m_pPressedMoveInsideHandleObject;
	//��ť���Ų��Ų����ڰ�ť��Χ�ڵĻص�����
	SEL_MenuHandler m_pPressedMoveInsideHandle;
	//��ť���Ų��Ų����ڰ�ť��Χ��Ķ���
	Ref *m_pPressedMoveOutsideHandleObject;
	//��ť���Ų��Ų����ڰ�ť��Χ��Ļص�����
	SEL_MenuHandler m_pPressedOutsideHandle;
	//�Ƿ��ڰ�ť��Χ��
	bool isInsideTouch(Touch* touch, Event* event);
	//��ť����
	virtual void onPressedDown();
	//��ť���º���
	virtual void onPressedUp();
	//��ť�����ڰ�ť��Χ��
	virtual void onPressedMoveInside();
	//��ť�����ڰ�ť��Χ��
	virtual void onPressedMoveOutside();
private:
	//��Ӧ�����¼�
	void TouchEvent();
	//�ڵ��Ƿ�ɼ�
	bool isAllParentVisible();
	//�Ƿ���
	bool m_bShock;
	//�Ƿ���Ӧ��ť�ص�����
	bool m_bEnable;
	//��ťʧЧʱ����ɫ
	Color3B m_UnableColor;
};



#endif