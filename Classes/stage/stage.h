#ifndef __STAGE_H__
#define __STAGE_H__

#include "mau.h"
#include "msg/message.h"
#include "tools/TickManager.h"

class Stage : public Scene, GameMessage
{

public:

	static Stage*			GetInstance();		//ȡ�õ���
	virtual bool			init();				//��ʼ������
	virtual void			OnMessage(const int head, void* data);
	CREATE_FUNC(Stage);

private:

	static Stage*			_instance;

	Layer*					current;						//��ǰ������ʾ��

	Layer*					asyncLayer;						//�첽ɾ�����õ�layer�洢ָ��

	void					onScheduleHandler(float dt);

	void					async_clearChild();				//�첽ɾ����̨�еĶ���

};

#endif
