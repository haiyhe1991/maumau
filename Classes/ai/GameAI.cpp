#include "ai.h"

void GameAI::Execute(list<Poker> handlst, Poker poker)
{
	if (peakPoker(handlst, poker.point))
	{
		//���Զ��ƣ�ֱ�Ӷ���
		list<Poker> same = samePoint(handlst, poker.point);
		send(ActionState::HIT, getPeakPoker(handlst, same));
		return;
	}
	//���ܶ��ƣ�ǰһ�����������ƣ���ôֱ�ӽ��ܳͷ�
	if (poker.point == PokerPoint::CHESS_7 || poker.point == PokerPoint::CHESS_8)
	{
		pass();
	}
	else
	{
		//���� ��������������
		//���ڲ߻�û��Ҫ���Ƚ���ͬ��ɫ�ĳ��ơ�   ���������ͬ��ɫ���ƣ����ȳ���ͬ��ɫ���ƣ�û�У�������ͬ�������ƣ�����ٿ���J
		if (checkSameColor(handlst, poker))
		{
			send(ActionState::HIT, getColorPoker(sameColor(handlst, poker.color)));
			return;
		}
		//AI����  û����ͬ��ɫ����  ��ô�Ϳ�ʼѰ����ͬ��������
		if (checkSamePoint(handlst, poker))
		{
			send(ActionState::HIT, getPointPoker(handlst, samePoint(handlst, poker.point)));
			return;
		}
		//AI���ˣ�ֻ�ܴ�J��ȥ�ˣ�ǰ������һ�Ų��ǳ���J
		if (poker.point != PokerPoint::CHESS_J)
		{
			if (samePointWithCount(handlst, PokerPoint::CHESS_J) > 0)
			{
				handleChangeColor(handlst);
				return;
			}
		}
		//��ȫû�п��Գ������ˣ�ֻ��������
		send();
	}
}

//���㶥��
Poker GameAI::getPeakPoker(list<Poker> handlst, list<Poker> samelst)
{
	//ֻ��һ�ţ�ֱ�Ӵ�
	if (samelst.size() == 1)
	{
		return *samelst.begin();
	}

	Poker result;
	int	count = 0;

	list<Poker>::iterator iter = samelst.begin();
	while (iter != samelst.end())
	{
		int same_count = sameColorWithCount(handlst, (*iter).color);
		if (same_count > count)
		{
			count = same_count;
			result = *iter;
		}
		iter++;
	}

	return result;
}

bool GameAI::checkSameColor(list<Poker> handlst, Poker poker)
{
	list<Poker> sameLst = sameColor(handlst, poker.color);
	if (sameLst.size() == 0)
	{
		return false;
	}
	list<Poker>::iterator iter = sameLst.begin();
	while (iter != sameLst.end())
	{
		if ((*iter).point != PokerPoint::CHESS_J)	//ֻҪ����������ƣ��Ϳ�����Ϊ�������
		{
			return true;
		}
		iter++;
	}
	return false;
}

Poker GameAI::getColorPoker(list<Poker> colorlst)
{
	//�����Ƶķ�������   ���ȳ����������
	Poker result;
	int score = 0;
	list<Poker>::iterator iter = colorlst.begin();
	while (iter != colorlst.end())
	{
		if ((*iter).score > score)
		{
			result = (*iter);
		}
		iter++;
	}
	return result;
}

bool GameAI::checkSamePoint(list<Poker> handlst, Poker poker)
{
	list<Poker> sameLst = samePoint(handlst, poker.point);
	if (sameLst.size() == 0)
	{
		return false;
	}
	list<Poker>::iterator iter = sameLst.begin();
	while (iter != sameLst.end())
	{
		if ((*iter).point != PokerPoint::CHESS_J)	//ֻҪ����������ƣ��Ϳ�����Ϊ�������
		{
			return true;
		}
		iter++;
	}
	return false;
}

Poker GameAI::getPointPoker(list<Poker> handlst, list<Poker> pointlst)
{
	Poker result;
	int count = 0;
	list<Poker>::iterator iter = pointlst.begin();
	while (iter != pointlst.end())
	{
		int color_count = sameColorWithCount(handlst, (*iter).color);
		if (color_count > count)
		{
			count = color_count;
			result = (*iter);
		}
		iter++;
	}
	return result;
}

void GameAI::handleChangeColor(list<Poker> handlst)
{
	PokerColor color = getMaxColor(handlst);
	list<Poker>::iterator iter = handlst.begin();
	while (iter != handlst.end())
	{
		if ((*iter).point == PokerPoint::CHESS_J)
		{
			send((*iter), color);
			return;
		}
		iter++;
	}
}

