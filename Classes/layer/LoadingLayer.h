#ifndef __LOADING_BAR_H__
#define __LOADING_BAR_H__

//��Դ����

#include "mau.h"
#include "tools/TickManager.h"

#define LOADING_TICK_TIME			300		//���ص�ʱ����

class BaseLayer;
struct LoadItem;

//���س���
class LoadingLayer : public Layer, GameTick
{
public:
	virtual bool init();
	CREATE_FUNC(LoadingLayer);
	
	~LoadingLayer();										//��������
	void				StartLoading(BaseLayer* layer);
	void				ChangeProgress();
	virtual void		OnTick(int time);
private:
	BaseLayer*			base_layer;							//���ݴ洢
	list<LoadItem>		loading_lst;						//��Ҫ���ص���Դ�б�       
protected:

	void				loadingMethod();

	Layout*				resource;							//�ܵ���Դ
	LoadingBar*			progress;

	int					max_num;
	int					cur_num;

};


#endif
