#include "GameLogic.h"

CenterLogic::CenterLogic()
{
	wait = new WaitTime;
	last_winner = nullptr;
	game_state = GameState::PAUSEING;
	direction = true;
	registerMessage();
	SetDelayTime(LOGIC_DELAY_TIME);
	initChess();
	initPlayer();
	TickManager::GetInstance()->Reg(this);
}

CenterLogic::~CenterLogic()
{
	delete chess_logic;
	TickManager::GetInstance()->Unreg(this);
}

void CenterLogic::registerMessage()
{
	MsgManager* manager = MsgManager::GetInstance();
	manager->Reg(MSG_START_GAME, this);
	manager->Reg(MSG_ACTION_CHESS, this);
}

void CenterLogic::OnTick(int time)
{
	if (wait->OnTime(time))
	{
		switch (game_state)
		{
		case WASHING:
		{
			chess_logic->WashChess();
			wait->StartWait(3000);			//�ȴ�3���Ӻ���뷢�ƽ׶Ρ��˴�Ҳ�����޵ȴ���һֱ�ȵ�UI�Ǳ߲����궯��֮���ٽ�����һ��
			game_state = GameState::DEAL;
			break;
		}
		case DEAL:
		{
			dealChess();
			break;
		}
		case ASKING:
		{
			//ֻ�л����˲Ž���AI����������ˣ��͵ȴ��˽��в���
			if ((*action_iter)->IsRobot())
			{
				(*action_iter)->Execute(poker);
			}
			else
			{
				//������Ϣ��֪ͨ��ҿ�ʼ�ж�
			}
			wait->StartWait(INT_MAX);//�����ǵ��������޵ȴ��¼���Ӧ ֱ�������ӦΪֹ
			break;
		}
		case CALCULATE:
			break;
		case OVER:
			break;
		case PAUSEING:
			break;
		default:
			break;
		}
	}
}

void CenterLogic::OnMessage(const int head, void* data)
{
	if (head == MSG_START_GAME)
	{
		game_state = GameState::WASHING;
	}
	else if (head == MSG_ACTION_CHESS)
	{
		ActionChess action = *((ActionChess*)data);
		processAction(action);
	}
}

void CenterLogic::Reset()
{
	direction = true;
	chess_logic->WashChess();
	//�������
	for (int i = 0; i < MAU_PLAYER_NUMBER; ++i)
	{
		player_vec[i]->Reset();
	}
}

void CenterLogic::initChess()
{
	chess_logic = new ChessLogic;
}

void CenterLogic::initPlayer()
{
	//������ʱֻ�ǵ���ģʽ����������д�����յ���Ϣ֮�󣬳�ʼ����������Լ�������
	//���ʼ������0��λ��
	vector<PlayerLogic*> vec(MAU_PLAYER_NUMBER);
	//vec[0] = new PlayerLogic(false);
	//����   ֱ��4��������
	vec[0] = new PlayerLogic(true);
	for (int i = 1; i < MAU_PLAYER_NUMBER; ++i)
	{
		vec[i] = new PlayerLogic(true);
	}
	player_vec = vec;
}

void CenterLogic::dealChess()
{
	int count = FIRST_HAND_NUMBER;
	while (count > 0)
	{
		for (int i = 0; i < int(player_vec.size()); i++)
		{
			player_vec[i]->AddChess(chess_logic->GetPoker());
		}
		count--;
	}

	actionPlayer(true);

	punish_count = 0;
	//ֱ�ӷ����Ƶ�����
	HitChess(chess_logic->GetPoker());

	wait->StartWait(3000);
	//�л���ǰ��Ϸ״̬
	game_state = GameState::ASKING;
}

void CenterLogic::actionPlayer(bool start/* = false*/)
{
	if (start)
	{
		if (last_winner == nullptr)
		{
			//������֮��ȷ��˭�Ƚ����ж�
			int count = RandomHelper::random_int(0, int(player_vec.size()) - 1);
			action_iter = player_vec.begin();
			while (count > 0)
			{
				action_iter++;
				count--;
			}
		}
		else
		{
			vector<PlayerLogic*>::iterator iter = player_vec.begin();
			while (iter != player_vec.end())
			{
				if ((*iter) == last_winner)
				{
					action_iter = iter;
					return;
				}
			}
		}
	}
	else
	{
		if (direction)
		{
			action_iter++;
			if (action_iter == player_vec.end())
			{
				action_iter = player_vec.begin();
			}
		}
		else
		{
			action_iter--;
			if (action_iter == player_vec.end())
			{
				action_iter = player_vec.end()--;
			}
		}
	}
}

void CenterLogic::HitChess(Poker poker)
{
	this->poker = poker;
	//������� �����ƶ�
	chess_logic->RecyclePoker(poker);
	if (poker.point == PokerPoint::CHESS_7)
	{
		punish_count += 1;
	}
	else
	{
		if (PokerPoint::CHESS_A == poker.point)
		{
			direction = !direction;
		}
		punish_count = 0;
	}
}

void CenterLogic::processAction(ActionChess action)
{
	PlayerLogic* player = *action_iter;
	if (action.state == ActionState::PASS) //����
	{
		punish();
		actionPlayer();
	}
	else if (action.state == ActionState::HIT) //�����Ǵ�һ����
	{
		if (player->CheckHandChess(action.poker))
		{
			player->DelChess(action.poker);
			HitChess(action.poker);
			//��һ���ж������
			actionPlayer();
		}
		//�����Ǵ���Ĵ��������Ժ���˵��  ֻҪ��֤AI������һ�㲻��������
	}
	else if (action.state == ActionState::GET) //�������
	{
		player->AddChess(chess_logic->GetPoker());
	}
	else if (action.state == ActionState::HIT_CHANGE)
	{

	}
	wait->StartWait(1000);
}

void CenterLogic::punish()
{
	while (this->punish_count > 0)
	{
		(*action_iter)->AddChess(chess_logic->GetPoker());
		(*action_iter)->AddChess(chess_logic->GetPoker());
		punish_count--;
	}
}
