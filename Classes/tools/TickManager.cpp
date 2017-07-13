#include "TickManager.h"

//����ģʽ
TickManager* TickManager::_instance = nullptr;

TickManager* TickManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TickManager();
	}
	return _instance;
}

void TickManager::DestoryInstance()
{
	if (_instance != nullptr)
	{
		_instance->Clear();
		delete _instance;
	}
	_instance = nullptr;
}

void TickManager::OnTickHandler(int delay)
{
	list<GameTick*>::iterator iter = container.begin();
	while (iter != container.end())
		(*iter++)->Execute(delay);
}

void TickManager::Reg(GameTick* tick)
{
	list<GameTick*>::iterator iter = container.begin();
	while (iter != container.end())
	{
		if ((*iter++) == tick)
			return;
	}
	container.push_back(tick);
}

void TickManager::Unreg(GameTick* tick)
{
	container.remove(tick);
}

void TickManager::Clear()
{
	container.clear();
}

/********************GameTick*******************/

void GameTick::SetDelayTime(int time)
{
	this->delayTime = time;
	this->count = 0;
}

void GameTick::Execute(int time)
{
	if (delayTime == 0)
	{
		OnTick(time);
		return;
	}
	else
	{
		count += time;
		if (count >= delayTime)
		{
			OnTick(count);
			//ʱ�䲹��   ����countʱ����ܲ�׼ȷ����Ҫ���Ծ�ȷ�Ļ����ټ�һ���������м���
			count -= delayTime;
		}
	}
}
