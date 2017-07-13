#ifndef __TICK_MANAGER_H__
#define __TICK_MANAGER_H__

#include <list>

using namespace std;

class GameTick
{
public:
	virtual void				OnTick(int time) = 0;	//ʱ�䵽��֮��Ļص�
	void						SetDelayTime(int time);	//���ü���ص�ʱ��   ���time=0 ����ÿ֡�����лص�
	void						Execute(int time);

private:

	int							delayTime;				//���ʱ��

	int							count;					//��ǰ�ļ���ʱ��

};

class TickManager
{
public:
	static TickManager*			GetInstance();
	static void					DestoryInstance();

	void						OnTickHandler(int delay);

	void						Clear();

	void						Reg(GameTick* tick);
	void						Unreg(GameTick* tick);

private:
	
	list<GameTick*>				container;

	static TickManager*			_instance;
};

#endif // __TICK_MANAGER_H__
