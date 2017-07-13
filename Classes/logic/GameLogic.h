#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "mau.h"
#include "csv/csv.h"

#define LOGIC_DELAY_TIME		1000

#define WASH_COUNT				3

enum PokerColor
{
	SPADES = 1,
	HEARTS,
	CLUBS,			//÷��
	DIAMONDS
};

enum PokerPoint
{
	CHESS_A = 1,
	CHESS_2,
	CHESS_3,
	CHESS_4,
	CHESS_5,
	CHESS_6,
	CHESS_7,
	CHESS_8,
	CHESS_9,
	CHESS_10,
	CHESS_J,
	CHESS_Q,
	CHESS_K,
};

struct Poker
{
	PokerColor		color;
	PokerPoint		point;
	int				score;			//�˿��ƶ�Ӧ�ķ���
};

enum ActionState
{
	HIT,			//��һ����
	GET,			//��һ����
	PASS,			//����  ����
	HIT_CHANGE,		//������  �ı仨ɫ
};

struct ActionChess
{
	Poker			poker;			//�������
	ActionState		state;
	PokerColor		color;			//ѡ��Ļ�ɫ
};

enum GameState
{
	WASHING,		//ϴ�ƽ׶�
	DEAL,			//���ƽ׶�
	ASKING,			//ѯ�ʽ׶�
	ACTION,			//����ж��׶�
	CALCULATE,		//����׶�
	OVER,			//��Ϸ����
	PAUSEING,		//��ͣ�׶Σ��ȴ����ѡ���Ƿ������Ϸ
};

class WaitTime
{
public:
	WaitTime();
	void			StartWait(int time);	//��ʼ�ȴ�  ʱ�����   ���ʱ��Ϊ0����ô����һ��������ʱ�򣬽�ִ�к���Ĵ���
	bool			OnTime(int time);		//��¼ʱ��			true ʱ���ѵ�
private:
	int				recordTime;				//��¼��ʱ��
	bool			state;					//�Ƿ�ȴ�
};

class BaseAI;

//���ƻ�   ���ƾ��е��ƶѽ��й���
class ChessLogic
{
public:
	ChessLogic();
	~ChessLogic();

	void					WashChess();						//ϴ�ƺ���
	Poker					GetPoker();							//ȡ��һ���˿���
	void					RecyclePoker(Poker poker);			//�����˿�

private:
	void					initPoker();						//��ʼ���˿���
	int						getPokerScore(PokerPoint point);	//ȡ���˿��ƶ�Ӧ�ķ���	
	void					mixPoker();							//�ƶѵ��ƴ���֮��  �����

private:
	vector<Poker*>			poker_vec;							//�˿���  ���е�
	list<Poker>				distribute_lst;						//�ɷ�list
	list<Poker>				recycle_lst;						//����list

	list<Poker>::iterator	heap_iter;							//�ƶѵ�����
};

//����߼�������
class PlayerLogic
{
public:
	PlayerLogic(bool robot);

	void					Reset();							//�������״̬
	bool					IsLose();							//�Ƿ��Ѿ�����˱���
	void					AddChess(Poker poker);
	void					DelChess(Poker poker);				//ɾ��һ������
	bool					IsRobot();

	void					Execute(Poker poker);				//�����˵�AIִ��
	bool					CheckHandChess(Poker poker);		//�������

protected:

	bool					robot;			//�Ƿ��ǻ�����
	int						score;			//����
	NameCsvItem*			nameItem;		//�������

	BaseAI*					game_ai;		//AI�㷨

	list<Poker>				chess_lst;		//����
};

//���߼�������
class CenterLogic : public GameMessage, GameTick
{
public:
	CenterLogic();
	~CenterLogic();

	virtual void							OnTick(int time);
	virtual void							OnMessage(const int head, void* data);
	

	void									Reset();								//������Ϸ
	void									HitChess(Poker poker);					//���һ����

private:
	GameState								game_state;								//��ǰ��Ϸ�Ľ���״̬
	bool									direction;								//��ǰ�ķ���˳��		true ����  false ����

	vector<PlayerLogic*>					player_vec;								//ʹ��vector �������
	vector<PlayerLogic*>::iterator			action_iter;							//��ǰ���ڶ��������

	PlayerLogic*							last_winner;							//��һ�λ��ʤ�������
	Poker									poker;									//��ǰ���������
	int										punish_count;							//�ͷ�����
	WaitTime*								wait;
	ChessLogic*								chess_logic;							//���߼�

private:
	void									registerMessage();

	void									initChess();							//��ʼ����
	void									initPlayer();							//��ʼ����Һͻ�����

	void									dealChess();							//���ƺ���
	void									actionPlayer(bool start = false);		//ȷ���ж������

	void									processAction(ActionChess action);		//�����ж�
	void									punish();								//�ͷ�����
};

#endif
