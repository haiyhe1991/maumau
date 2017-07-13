#include "GameLogic.h"
#include "ai/ai.h"
#include "GameManage/GameRecord.h"

PlayerLogic::PlayerLogic(bool robot)
{
	this->robot = robot;
	Reset();
	//�������

	if (IsRobot())
	{
		nameItem = CsvData::GetInstance()->nameCsv->GetRandomName();
		game_ai = new GameAI();
	}
	else
	{
		nameItem = new NameCsvItem;
		nameItem->name = "player";
	}
	//������Ϣ����ʾ�㣬��ʾͷ�������

}

bool PlayerLogic::IsRobot()
{
	return robot;
}

void PlayerLogic::AddChess(Poker poker)
{
	chess_lst.push_back(poker);
}

void PlayerLogic::DelChess(Poker poker)
{
	list<Poker>::iterator iter = chess_lst.begin();
	while (iter != chess_lst.end())
	{
		if ((*iter).color == poker.color && (*iter).point == poker.point)
		{
			chess_lst.erase(iter);
			return;
		}
		iter++;
	}
}

bool PlayerLogic::CheckHandChess(Poker poker)
{
	list<Poker>::iterator iter = chess_lst.begin();
	while (iter != chess_lst.end())
	{
		if ((*iter).color == poker.color && (*iter).point == poker.point)
		{
			return true;
		}
		iter++;
	}
	return false;
}

bool PlayerLogic::IsLose()
{
	return this->score >= 100;
}

void PlayerLogic::Reset()
{
	this->score = 0;
}

void PlayerLogic::Execute(Poker poker)
{
	//�����Ҫ��AI���ϵȴ�ʱ�䣬�������������
	game_ai->Execute(chess_lst, poker);
}

