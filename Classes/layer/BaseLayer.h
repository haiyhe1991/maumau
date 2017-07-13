#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "mau.h"
#include "load.h"

//�޸ģ����е��������Բ����ʽ��
class BaseLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BaseLayer);

	virtual void onEnter();							//�������뵽����֮��   ����������У����ǵ�ǰ���������ĳ�ʼ������

	virtual void releaseResource();					//�ͷ���Դ

public:
	virtual list<LoadItem> getResourceList();		//������ص���Դ�б�
};


#endif
