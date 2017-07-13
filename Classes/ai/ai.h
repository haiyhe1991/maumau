#ifndef __AI_H__
#define __AI_H__

#include "mau.h"
#include "logic/GameLogic.h"

//AI�Ļ���
class BaseAI
{
public:
	virtual void		Execute(list<Poker> handlst, Poker poker) = 0;		//AI��ִ�к���

protected:

	list<Poker>			samePoint(list<Poker> handlst, PokerPoint point);			//�ҵ���ͬ��������
	int					samePointWithCount(list<Poker> handlst, PokerPoint point);	//�ҵ���ͬ�������� ��������
	list<Poker>			sameColor(list<Poker> handlst, PokerColor color);			//�ҵ���ͬ��ɫ����
	int					sameColorWithCount(list<Poker> handlst, PokerColor color);	//�ҵ���ͬ��ɫ���� ��������
	virtual bool		peakPoker(list<Poker> handlst, PokerPoint point);			//���㶥��
	void				pass();														//����

	void				send();														//����
	void				send(ActionState state, Poker poker);						//������Ϣ
	void				send(Poker poker, PokerColor color);						//���������

	PokerColor			getMaxColor(list<Poker> handlst);							//ȡ����������ɫ

private:
	bool				compareColorCount(list<Poker> handlst, PokerColor color, int &count);		//�Ƚ���ɫ�Ƶ�����

};

class GameAI : public BaseAI
{
public:
	virtual void		Execute(list<Poker> handlst, Poker poker);

protected:
	bool				checkSameColor(list<Poker> handlst, Poker poker);			//����ܲ�����ͬ��������
	bool				checkSamePoint(list<Poker> handlst, Poker poker);			//�����û����ͬ��������

	Poker				getPeakPoker(list<Poker> handlst, list<Poker> samelst);		//���Ƶĳ��Ƽ���

	Poker				getColorPoker(list<Poker> colorlst);						//���������ɫ���Ƶ���
	Poker				getPointPoker(list<Poker> handlst, list<Poker> pointlst);	//��������������Ƶ���

	void				handleChangeColor(list<Poker> handlst);						//����ı���ɫ����

};

#endif
