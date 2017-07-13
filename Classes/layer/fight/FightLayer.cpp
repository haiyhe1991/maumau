#include "layer/layer_header.h"
#include "mau.h"
#include "resource/ResourceManager.h"
#include "GameManage/GameManage.h"
#include "GameManage/GameRecord.h"
#include "ReadCsvFile/ReadCsvFile.h"

FightLayer::FightLayer()
{
	/*m_psCardProperties = new sCardProperties[CARDS_MAX_NUMBER];
	m_iTurn = 0;
	m_iDealCardStyle = DealCardStyle::StartDealCard;
	m_iDealCardNumber = 0;
	m_iRemainPlayer = PLAYER_NUMBER;
	m_iZOrder = 0;
	m_iChoosedColor = 1;
	m_bOrder = true;
	m_bIsPunlished = false;
	m_bIsFisrtOutCard = true;
	m_bIsTouchEnabel = false;
	m_iChooseingCardIndex = 0;
	m_iPunlishCardNumber = 0;
	for (int i = 0; i < PLAYER_NUMBER; i++)
	{
		m_PlayerCards[i].clear();
		m_iLoseScore[i] = 0;	
	}
	m_PlayerCardsCanOut.clear();
	m_ShufflingCards.clear();
	m_CardsPile.clear();*/
	
}

FightLayer::~FightLayer()
{
	delete m_psCardProperties;
}
bool FightLayer::init()
{
	Layer::init();
	layout = (Layout*)ResourceManager::GetInstance()->Get_ui_resource("ui/fight/fight.ExportJson");
	this->addChild(layout);

	game_menu = (Button *)layout->getChildByName("game_menu");
	//����¼�����
	game_menu->addClickEventListener(CC_CALLBACK_1(FightLayer::onGameMenuHandler, this));

	m_DrawCards = (Button *)layout->getChildByName("DrawCards");
	m_DrawCards->addClickEventListener(CC_CALLBACK_1(FightLayer::onDrawCardsHandler, this));

	//���ݶ������ƴ�����������
	m_bgCardArmature = Armature::create("NewAnimation");
	//���ö�������λ��
	m_bgCardArmature->setPosition(m_DrawCards->getPositionX(), m_DrawCards->getPositionY());
	//��ӵ���ǰҳ��
	this->addChild(m_bgCardArmature, INT_MAX - 1);

	m_ArrowDown = (Button *)layout->getChildByName("ArrowDown");
	m_ArrowDown->addClickEventListener(CC_CALLBACK_1(FightLayer::onArrowDownHandler, this));

	m_ArrowUp = (Button *)layout->getChildByName("ArrowUp");
	m_ArrowUp->addClickEventListener(CC_CALLBACK_1(FightLayer::onArrowUpHandler, this));

	m_top_card = (Button *)layout->getChildByName("top_card");
	m_top_card->addClickEventListener(CC_CALLBACK_1(FightLayer::onTopCardHandler, this));

	m_give_up = (Button *)layout->getChildByName("give_up");
	m_give_up->addClickEventListener(CC_CALLBACK_1(FightLayer::onGiveUpHandler, this));

	Window_Colortip = (ImageView *)layout->getChildByName("Window_Colortip");

	Window_Cardchoose = (ImageView *)layout->getChildByName("Window_Cardchoose");

	uiTempCard = (ImageView *)layout->getChildByName("uiTempCard");

	m_highLight = (ImageView *)layout->getChildByName("Hightlight");

	for (int i = 0; i < 4; i++)
	{
		char str[24];
		sprintf(str, "choose_%d",i+1);
		m_choose_color[i] = (Button *)Window_Cardchoose->getChildByName(str);
		m_choose_color[i]->setTag(i+1);
		m_choose_color[i]->addClickEventListener(CC_CALLBACK_1(FightLayer::onChooseColorHandler, this));
	}

	Window_Invalid = (ImageView *)layout->getChildByName("Window_Invalid");
	//��ʼ������
	this->initName();
	//���µ÷�
	this->updataScoreView(false);
	//�ƵĲ���˳���Ǻ�A����A������A��������k
	/*for (int i = 0; i < CARDS_MAX_NUMBER; i++)
	{
		char str[24];
		sprintf(str, "Card/%d%.2d.png", CARD_COLOR(i), CARD_NUMBER(i));
		(m_psCardProperties + i)->spCard = SpriteButton::createWithFrame(ResourceManager::getInstance()->get_resource_from_plist(str));
		(m_psCardProperties + i)->spCard->setIsShock(false);
		(m_psCardProperties + i)->spCard->setVisible(false);
		(m_psCardProperties + i)->spCard->setPressedUpHandler(this, SEL_MenuHandler(&FightLayer::onSingleCardHandler));
		this->addChild((m_psCardProperties + i)->spCard);
		(m_psCardProperties + i)->spCard->setTag(i);
		m_ShufflingCards.push_back((m_psCardProperties + i));
	}
	this->shuffCards();*/
	return true;
}
void FightLayer::initName()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	const char* full_name = GameRecord::GetInstance()->GetDataPath("CSV_data/namelist.csv");
#else
	const char* full_name = "CSV_data/namelist.csv";
#endif
	ReadCsvFile *pReadCsvFile = new ReadCsvFile();
	if (pReadCsvFile->LoadCSV(full_name))
	{
		char str[24] = {};
		int iRandomExit = 1;
		int iRandom;
		for (int i = 0; i < PLAYER_NUMBER - 1; i++)
		{
			if (i == 0)
			{
				iRandom = CCRANDOM_0_1() * 45 + 47;
				iRandomExit = iRandom;
			}
			else if (i == 1)
			{
				iRandom = CCRANDOM_0_1() * 45 + 2;
			}
			else if (i == 2)
			{
				do
				{
					iRandom = CCRANDOM_0_1() * 45 + 47;
				} while (strcmp((*pReadCsvFile->GetStringValue(iRandom, 2)).c_str(), (*pReadCsvFile->GetStringValue(iRandomExit, 2)).c_str()) == 0);
			}
			sprintf(str, "Name%d", i + 2);
			TextBMFont *Name = (TextBMFont *)layout->getChildByName(str);
			Name->setString((*(pReadCsvFile->GetStringValue(iRandom, 1))).c_str());
			CCLOG("%s", (*(pReadCsvFile->GetStringValue(iRandom, 1))).c_str());
			GameManage::GetInstance()->setPlayerName((*pReadCsvFile->GetStringValue(iRandom, 1)).c_str(), i + 1);
		}

	}
	delete pReadCsvFile;
	TextBMFont* Name1 = (TextBMFont*)layout->getChildByName("Name1");
	if (GameRecord::GetInstance()->JudgeFileExist("MauMau"))
	{
		GameRecord::GetInstance()->LoadData();
	}
	else
	{
		GameRecord::GetInstance()->SaveData();
	}
	Name1->setString(GameManage::GetInstance()->getPlayerName(0));
}
void FightLayer::updataScoreView(bool isDouble)
{
	//������ʧ�ķ�
	for (int i = 0; i < PLAYER_NUMBER; i++)
	{
		if (m_iLoseScore[i] < 100)
		{
			for (int j = 0; j != m_PlayerCards[i].size();++j)
			{
				m_iLoseScore[i] = m_iLoseScore[i] + (2 - !isDouble)*(this->cardScoreRule(m_PlayerCards[i][j]->spCard->getTag()));
			}
			if (m_iLoseScore[i] > 100)
			{
				m_iRemainPlayer--;
			}
			char str[24];
			sprintf(str, "Score%d", i + 1);
			TextBMFont *Score = (TextBMFont *)layout->getChildByName(str);
			sprintf(str, "%d", m_iLoseScore[i]);
			GameManage::GetInstance()->setPlayerScore(str,i);
			Score->setString(str);
		}
	}
}
int FightLayer::cardScoreRule(int iCardTag)
{
	int iRet;
	/*switch (CARD_NUMBER(iCardTag))
	{
	case CardNumber::CARD_A:
		iRet = 11;
		break;
	case CardNumber::CARD_J:
		iRet = 20;
		break;
	case CardNumber::CARD_Q:
		iRet = 3;
		break;
	case CardNumber::CARD_K:
		iRet = 4;
		break;
	case CardNumber::CARD_2:
	case CardNumber::CARD_3:
	case CardNumber::CARD_4:
	case CardNumber::CARD_5:
	case CardNumber::CARD_6:
	case CardNumber::CARD_7:
	case CardNumber::CARD_8:
	case CardNumber::CARD_9:
	case CardNumber::CARD_10:
		iRet =  CARD_NUMBER(iCardTag);
		break;
	default:
		break;
	}*/
	return iRet;
}
void FightLayer::shuffCards()
{
	//���Ȱ��ƶ���������ɾ�
	m_CardsPile.clear();
	//��ʼ���Ƶĵ���˳�򣬣��������ȳ�ʼ��ϴ�ƶѵ��Ƶĵ���˳��0��1��2��3.����
	for (int i = m_ShufflingCards.size(); i != 0; --i)
	{
		m_ShufflingCards[i - 1]->spCard->setVisible(false);
		m_ShufflingCards[i - 1]->iCardState = i - 1;
	}
	//������ִ��ϴ�ƵĲ�����ͨ����������ı�ϴ�ƶѵ��Ƶĵ���˳��
	for (int i = m_ShufflingCards.size(); i != 0; --i)
	{
		int iRandom = CCRANDOM_0_1()*i;
		int temp = m_ShufflingCards[i - 1]->iCardState;
		m_ShufflingCards[i - 1]->iCardState = m_ShufflingCards[iRandom]->iCardState;
		m_ShufflingCards[iRandom]->iCardState = temp;
	}
	//��ϴ�ƶѵ���ȫ����ֲ�����ƶ�����
	m_CardsPile.insert(m_CardsPile.end(), m_ShufflingCards.begin(), m_ShufflingCards.end());
	//�����ƶѵ��ư����Ƶ�״ֵ̬���µ��ţ�����
	this->sortByCardState(m_CardsPile, true);
	//����ɾ�ϴ�ƶ�����
	m_ShufflingCards.clear();
	//���Ƶķ�ʽ��ʼ��Ϊ��ʼ����
	/*m_iDealCardStyle = DealCardStyle::StartDealCard;*/
	//����˳���ʼ��Ϊ˳ʱ��
	m_bOrder = true;
	//��ʼ��ϴ�ƶѵ��Ƶ���Ⱦ�㼶Ϊ0
	m_iZOrder = 0;
	//��ʼ�����Ƶ���ʼλ��
	m_iTurn = 0;
	//������ƶ������һ����ʱ�����������ˡ��������˽�����
	for (int i = m_iTurn; i < m_iTurn + PLAYER_NUMBER; i++)
	{
		if (m_iLoseScore[i%PLAYER_NUMBER] < 100)
		{
			m_iTurn = i%PLAYER_NUMBER;
			break;
		}
	}
	//��ʼ���Ѿ����˵��Ƶ�����
	m_iDealCardNumber = 0;
	//��ʼ����һ����Ϊϵͳ�����ġ�������Ҵ������
	m_bIsFisrtOutCard = true;
	//���ƵĴ������عر�
	m_bIsTouchEnabel = false;
	//������ɫ��ʾ
	Window_Colortip->setVisible(false);
	//ִ��ϴ�ƵĶ���
	//����ָ������
	m_bgCardArmature->getAnimation()->play("shuffCards");
	//���ö�����֡����
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onShuffCardsFrameEvent));
}
void FightLayer::shuffRemainCards()
{
	//���Ȱ��ƶ���������ɾ�
	m_CardsPile.clear();
	//��ʼ���Ƶĵ���˳�򣬣��������ȳ�ʼ��ϴ�ƶѵ��Ƶĵ���˳��0��1��2��3.����
	for (int i = m_ShufflingCards.size() - 1; i != 0; --i)
	{
		m_ShufflingCards[i - 1]->spCard->setVisible(false);
		m_ShufflingCards[i - 1]->iCardState = i - 1;
	}
	//������ִ��ϴ�ƵĲ�����ͨ����������ı�ϴ�ƶѵ��Ƶĵ���˳��
	for (int i = m_ShufflingCards.size() - 1; i != 0; --i)
	{
		int iRandom = CCRANDOM_0_1()*i;
		int temp = m_ShufflingCards[i - 1]->iCardState;
		m_ShufflingCards[i - 1]->iCardState = m_ShufflingCards[iRandom]->iCardState;
		m_ShufflingCards[iRandom]->iCardState = temp;
	}
	//��ϴ�ƶѵ���ȫ����ֲ�����ƶ�����
	m_CardsPile.insert(m_CardsPile.end(), m_ShufflingCards.begin(), m_ShufflingCards.end() - 1);
	//�����ƶѵ��ư����Ƶ�״ֵ̬���µ��ţ�����
	this->sortByCardState(m_CardsPile, true);
	//�Ȱ����һ���Ʒ��ŵ�һ�߶�
	sCardProperties *pTempsCardProperties = m_ShufflingCards[m_ShufflingCards.size() - 1];
	//����ɾ�ϴ�ƶ�����
	m_ShufflingCards.clear();
	//�����һ���Ʒŵ�ϴ�ƶ���ȥ
	m_ShufflingCards.push_back(pTempsCardProperties);
	//��ʼ��ϴ�ƶѵ��Ƶ���Ⱦ�㼶Ϊ0
	m_iZOrder = 0;
	//����ԭ�ȵ��Ƶ����һ�Ų���
	m_ShufflingCards[0]->spCard->setLocalZOrder(m_iZOrder);
	m_iZOrder++; 
	//���ƵĴ������عر�
	m_bIsTouchEnabel = false;
	//ִ��ϴ�ƵĶ���
	//����ָ������
	m_bgCardArmature->getAnimation()->play("shuffCards");
	//���ö�����֡����
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onShuffCardsFrameEvent));
}
void FightLayer::onGameMenuHandler(Ref *ob)
{
	//��ͣ���еĶ���
	GameManage::GetInstance()->RevursivelyPauseAllChildren(this);
	m_gameMenuLayer = GameMenuLayer::create();
	this->addChild(m_gameMenuLayer, INT_MAX);
}
void FightLayer::onDrawCardsHandler(Ref *ob)
{
	if (0 == m_iTurn)
	{
		m_highLight->setVisible(false);
		m_DrawCards->setVisible(false);//���ƵĴ������عر�
		//���ƵĻ����Ȱ���ʾ���������ջ�ԭ��
		m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() - 20);
	}
	//ִ����ӻ����ƵĶ���
	CCLOG("remainnumber = %d", m_CardsPile.size());
	if (0 != m_CardsPile.size())
	{
		this->addTempCard();
	}
	else
	{
		//ϴ��
	    /*m_iDealCardStyle = DealCardStyle::AddTempDealCard;*/
		this->shuffRemainCards();
	}
	
}
void FightLayer::onSingleCardHandler(Ref *ob)
{
	int tag = ((Node*)ob)->getTag();
	CCLOG("%d", tag);
	if (m_iTurn != 0 || !m_bIsTouchEnabel)
	{
		return;
	}
	//�Ȱ��Ѿ���ʾ���Ƶ�λ���ջص�ԭλ
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() - 20);
	for (int i = 0; i != m_PlayerCards[m_iTurn].size(); ++i)
	{
		if (m_PlayerCards[m_iTurn][i]->spCard->getTag() == tag)
		{
			
			if (m_iChooseingCardIndex == i)
			{
				//�������ͬһ���ƣ���ô���ж��ܲ��ܳ���������
				if (this->isCanCutCardRule(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getTag()))
				{
					this->cutCardRule();
					return;
				}
				else
				{
					Window_Invalid->runAction(Sequence::create(Show::create(),DelayTime::create(0.5f),Hide::create(),NULL));
				}
			}
			m_iChooseingCardIndex = i;
			break;
		}
	}
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() + 20);
}
void FightLayer::onArrowUpHandler(Ref *ob)
{
	//��������������ͷ
	m_ArrowUp->setVisible(false);
	m_ArrowDown->setVisible(false);
	//�����ƶ���������Ʒŵ�ϴ�Ƶ���������
	m_ShufflingCards.push_back(m_CardsPile[m_CardsPile.size() - 1]);
	//��ħ�ɶ������������ʾ��������ʼ���ڷ���λ�ã��Լ���Ⱦ�㼶
	m_CardsPile[m_CardsPile.size() - 1]->spCard->setVisible(true);
	m_CardsPile[m_CardsPile.size() - 1]->spCard->setPosition(Vec2(585, 256));
	m_CardsPile[m_CardsPile.size() - 1]->spCard->setLocalZOrder(m_iZOrder);
	//��Ⱦ�㼶��Ӧ��Ҫ��1��Ϊ������ŵ�����׼����ʵ�ֺ������Ʒ���ǰ��������档
	m_iZOrder++;
	//�����ƶ����һ�����Ƴ�����
	m_CardsPile.pop_back();
	//�ɵ�һ����Ҳ������൱�ڳ�����Ҫ���������ĵ�Ч�����뵱ǰ��ҳ��ƵĲ�����
	this->afterCutSpeiclCardEffect();
	
}
void FightLayer::onArrowDownHandler(Ref *ob)
{
	//��������������ͷ��ť
	m_ArrowUp->setVisible(false);
	m_ArrowDown->setVisible(false);
	//���ӵ�������ƶ���
	this->addPlayerCard();
	//�ֵ���һ����Ҳ����������Ϊû�г��ơ����Բ���Ҫ�������Ч��
	//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
	this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
}
void FightLayer::onTopCardHandler(Ref *ob)
{
	//���ƺͷ�����ť����
	m_top_card->setVisible(false);
	m_give_up->setVisible(false);
	//��ʾ������
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() + 20);
	m_bIsTouchEnabel = true;
}
void FightLayer::onGiveUpHandler(Ref *ob)
{
	m_bIsTouchEnabel = false;
	//�������ƣ�Ҳ���ǽ����˳ͷ�
	m_bIsPunlished = true;
	//���ƺͷ�����ť����
	m_top_card->setVisible(false);
	m_give_up->setVisible(false);
	/*if (CardNumber::CARD_7==CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()))
	{
		//����
		m_iDealCardStyle = DealCardStyle::PunlishCard;
		this->DealCards();
	}
	else if (CardNumber::CARD_8 == CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()))
	{
		//this->nextTurn();
		//this->beforCutSpeiclCardEffect(0);
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
	}*/
}
void FightLayer::onChooseColorHandler(Ref *ob)
{
	int tag = ((Node*)ob)->getTag();
	CCLOG("chooseColor = %d", tag);
	this->updateChooseColorView(tag);
	this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
	//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
}
void FightLayer::updateChooseColorView(int iChooseColor)
{
	//������ɫѡ�񴰿�
	Window_Cardchoose->setVisible(false);
	//��ʾ��ɫ��ʾ����
	Window_Colortip->setVisible(true);
	//ѡ�����ɫ��ֵ����Ӧ�ĳ�Ա�������Ա��������ж�
	m_iChoosedColor = iChooseColor;
	//������ɫѡ����ֵ�ͼƬΪָ������ɫ
	ImageView *ColortipSelect = (ImageView *)Window_Colortip->getChildByName("ColortipSelect");
	char str[24];
	sprintf(str, "Colortip%d.png", iChooseColor);
	ColortipSelect->loadTexture(str, ui::Widget::TextureResType::PLIST);
}
void FightLayer::onShuffCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() ϵ ֡�¼�������
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "shuffCardsOver"))//����������֡�¼���
	{
		//ϴ������ִ�з���
		switch (m_iDealCardStyle)
		{
		/*case DealCardStyle::StartDealCard:
		case DealCardStyle::PunlishCard:
			this->DealCards();
			break;
		case  DealCardStyle::AddTempDealCard:
			this->addTempCard();
			break;*/
		default:
			break;
		}
	}
}
void FightLayer::onDealCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() ϵ ֡�¼�������
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "DealCardOver"))//����������֡�¼���
	{
		switch (m_iDealCardStyle)
		{
		/*case DealCardStyle::StartDealCard:
			//����������е�������
			this->addPlayerCard();
			//�ֵ���һ�����
			this->nextTurn();
			//�Ѿ������Ƶ�������1
			m_iDealCardNumber++;
			
			if (m_iDealCardNumber != PER_START_CARDS_NUMBER*m_iRemainPlayer)
			{
				//�������û����ʣ����Ҹ���*5�ţ���ô��������
				this->DealCards();
			}
			else
			{
				//����ͷ�����һ���ƣ���Ϊ���ƣ�
				this->firstOutCard();
			}
			break;
		case DealCardStyle::PunlishCard:
			//����������е���
			this->addPlayerCard();
			//�ͷ�����������1
			m_iPunlishCardNumber--;
			if (m_iPunlishCardNumber)
			{
				CCLOG("remainnumber = %d",m_CardsPile.size());
				if (0 != m_CardsPile.size())
				{
					this->DealCards();
				}
				else
				{
					//ϴ��
					this->shuffRemainCards();
				}
			}
			else
			{
				this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
				//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
			}
			break;*/
		default:
			break;
		}

	}
}
void FightLayer::DealCards()
{

	char str[24];
	sprintf(str, "name%dDealCard", m_iTurn + 1);
	//����ָ������������һ����4����ң�������Ҫ����4�ֲ�ͬ�Ķ�����
	m_bgCardArmature->getAnimation()->play(str);
	//���ƵĶ�������
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onDealCardsFrameEvent));

}
void FightLayer::cutCard()
{

	//����ָ������
	char str[24];
	sprintf(str, "name%dCutCard", m_iTurn + 1);
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onCutCardFrameEvent));
}
void FightLayer::onCutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() ϵ ֡�¼�������
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "CutCardOver"))
	{

		this->cutCardRule();
	}
}
//������һ���ƵĶ���
void FightLayer::firstOutCard()
{
	//����ָ������
	m_bgCardArmature->getAnimation()->play("firstOutCard");
	//������һ���ƵĶ�������
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onFirstOutCardFrameEvent));
}
void FightLayer::onFirstOutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() ϵ ֡�¼�������
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "firstOutCardOver"))//������һ���ƵĶ���֡�����¼�
	{
		this->onArrowUpHandler((Ref*)m_ArrowUp);
	}
}
void FightLayer::updateLeftCardsView(int iTurn)
{
	if (iTurn == 0)
	{
		return;
	}
	char str[24];
	sprintf(str, "Leftcards%d", iTurn);
	ImageView *Leftcards = (ImageView *)layout->getChildByName(str);
	int iRemainCards = m_PlayerCards[iTurn].size();
	iRemainCards = (!(iRemainCards / 3))*iRemainCards + 3 * (!(!(iRemainCards / 3)));
	if (iRemainCards == 0)
	{
		Leftcards->setVisible(false);
	}
	else
	{
		Leftcards->setVisible(true);
		sprintf(str, "Leftcards%d.png", iRemainCards);
		Leftcards->loadTexture(str, ui::Widget::TextureResType::PLIST);
	}
}
void FightLayer::sortByCardState(std::vector<sCardProperties *>& vectorName, bool bRise)
{

	for (int i = 0; i != vectorName.size(); ++i)
	{
		for (int j = i; j != vectorName.size(); j++)
		{
			if (bRise&&(vectorName[i]->iCardState > vectorName[j]->iCardState))
			{
				sCardProperties *pCardProperties = vectorName[i];
				vectorName[i] = vectorName[j];
				vectorName[j] = pCardProperties;
			}
			else if (!bRise&&vectorName[i]->iCardState < vectorName[j]->iCardState)
			{
				sCardProperties *pCardProperties = vectorName[i];
				vectorName[i] = vectorName[j];
				vectorName[j] = pCardProperties;
			}
		}
	}

}
void FightLayer::addPlayerCard()
{
	if (m_PlayerCards[m_iTurn].size() != 0)
	{
		int i;
		for (i = 0; i != m_PlayerCards[m_iTurn].size(); i++)
		{
			if (CARD_VALUE(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()) >= CARD_VALUE(m_PlayerCards[m_iTurn][i]->spCard->getTag()))
			{
				int insertIndex = i;
				for (int j = 0; j < insertIndex; j++)
				{
					m_PlayerCards[m_iTurn][j]->spCard->setPositionX(m_PlayerCards[m_iTurn][j]->spCard->getPositionX() - m_PlayerCards[m_iTurn][j]->spCard->getContentSize().width/2);
				}
				for (int k = insertIndex; k != m_PlayerCards[m_iTurn].size(); k++)
				{
					m_PlayerCards[m_iTurn][k]->spCard->setPositionX(m_PlayerCards[m_iTurn][k]->spCard->getPositionX() + m_PlayerCards[m_iTurn][k]->spCard->getContentSize().width / 2);
				}
				m_CardsPile[m_CardsPile.size() - 1]->spCard->setPosition(Vec2(m_PlayerCards[m_iTurn][0]->spCard->getPositionX() + (insertIndex - !insertIndex)*(m_PlayerCards[m_iTurn][0]->spCard->getContentSize().width), m_PlayerCards[m_iTurn][0]->spCard->getPositionY()));
				m_PlayerCards[m_iTurn].insert(m_PlayerCards[m_iTurn].begin()+insertIndex, m_CardsPile[m_CardsPile.size() - 1]);
				
				break;
			}
		}
		//�������������С
		if (i == m_PlayerCards[m_iTurn].size())
		{
			for (int j = 0; j != m_PlayerCards[m_iTurn].size(); j++)
			{
				m_PlayerCards[m_iTurn][j]->spCard->setPositionX(m_PlayerCards[m_iTurn][j]->spCard->getPositionX() - m_PlayerCards[m_iTurn][j]->spCard->getContentSize().width / 2);
			}
			m_CardsPile[m_CardsPile.size() - 1]->spCard->setPosition(Vec2(m_PlayerCards[m_iTurn][0]->spCard->getPositionX() + (m_PlayerCards[m_iTurn].size())*(m_PlayerCards[m_iTurn][0]->spCard->getContentSize().width), m_PlayerCards[m_iTurn][0]->spCard->getPositionY()));
			m_PlayerCards[m_iTurn].push_back(m_CardsPile[m_CardsPile.size() - 1]);
		}
	}
	else
	{
		Vec2 PlayerCardsPoint[PLAYER_NUMBER] = { Vec2(480, 109), Vec2(269, 437), Vec2(485, 437), Vec2(712, 437) };     //��������Ƶ�λ��
		m_PlayerCards[m_iTurn].push_back(m_CardsPile[m_CardsPile.size() - 1]);
		m_PlayerCards[m_iTurn][m_PlayerCards[m_iTurn].size() - 1]->spCard->setPosition(PlayerCardsPoint[m_iTurn]);	
	}
	if (m_iTurn == 0)
	{
		m_CardsPile[m_CardsPile.size() - 1]->spCard->setVisible(true);
	}
	m_CardsPile.pop_back();
	this->updateLeftCardsView(m_iTurn);
}
float FightLayer::getPerCardWidth(int iPlayerRemaindCardsNumber, float fPerUICardWidth)
{
	float fRet = fPerUICardWidth;
	if (iPlayerRemaindCardsNumber > PLAYER_MAX_CARDS_WIDTH_NUMBER)
	{
		fRet = (((float)iPlayerRemaindCardsNumber) / PLAYER_MAX_CARDS_WIDTH_NUMBER)*(fPerUICardWidth);
	}
	return fRet;
}
void FightLayer::addTempCard()
{
	//���ƴ浽��������Ķ���
	char str[24];
	sprintf(str, "name%dAddTempCard", m_iTurn+1);
	//����ָ������
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onAddTempCardFrameEvent));
}
void FightLayer::onAddTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "AddTempCardOver"))//���涯������
	{
		Vec2 PlayerCardsPoint[PLAYER_NUMBER] = { Vec2(480, 182), Vec2(269, 407), Vec2(485, 407), Vec2(712, 407) };
		
		//�����Ƶ���Ӧ�Ļ���λ�ã�������������
		m_CardsPile[m_CardsPile.size() - 1]->spCard->setPosition(PlayerCardsPoint[m_iTurn]);
		CCLOG("getCard: color==%d number===%d", CARD_COLOR(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()), CARD_NUMBER(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()));
		if (0 == m_iTurn)
		{
			//��������1����ô��ʾ����
			m_CardsPile[m_CardsPile.size() - 1]->spCard->setVisible(true);
			//��ʾ���µļ�ͷ�İ�ť
			m_ArrowDown->setVisible(true);
			//�����������ܳ�����ô��ʾ���ϵļ�ͷ�İ�ť
			if (this->isCanCutCardRule(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()))
			{
				//��������ж�Ҫ��Ҫ��������
				m_ArrowUp->setVisible(true);
			}
			m_bIsTouchEnabel = false;
		}
		else
		{
			Vec2 TempCardPoint[PLAYER_NUMBER - 1] = { Vec2(267, 317), Vec2(485, 317), Vec2(712, 317) };
			//����һ��ai������������λ���ˡ�
			uiTempCard->setPosition(TempCardPoint[m_iTurn-1]);
			if (this->isCanCutCardRule(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()))
			{
				//���������ܳ����Ǿ�ֱ�ӳ���
				uiTempCard->runAction(Sequence::create(Show::create(), DelayTime::create(TEMP_CARD_SHOW_TIME), Hide::create(), CallFunc::create(CC_CALLBACK_0(FightLayer::popTempCard, this)), NULL));
			}
			else
			{
				//�������Ʋ��ܳ�
				uiTempCard->runAction(Sequence::create(Show::create(), DelayTime::create(TEMP_CARD_SHOW_TIME), Hide::create(), CallFunc::create(CC_CALLBACK_0(FightLayer::pushTempCard, this)), NULL));
			}

		}
	}
}
bool FightLayer::isCanCutCardRule(int iCardTag)
{
	bool bRet = false;
	switch (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size()-1]->spCard->getTag()))
	{
	/*case CardNumber::CARD_7:
	case CardNumber::CARD_8:
		bRet = (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()) == CARD_NUMBER(iCardTag)) || (m_bIsPunlished && ((CARD_COLOR(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()) == CARD_COLOR(iCardTag)) || CARD_NUMBER(iCardTag)==CardNumber::CARD_J));
		break;
	case CardNumber::CARD_J:
		bRet = (CardNumber::CARD_J != CARD_NUMBER(iCardTag) && m_iChoosedColor == CARD_COLOR(iCardTag));
		break;*/
	default:
		/*bRet = (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()) == CARD_NUMBER(iCardTag)) || (CARD_COLOR(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()) == CARD_COLOR(iCardTag) || (CARD_NUMBER(iCardTag) == CardNumber::CARD_J));*/
		break;
	}
	return bRet;
}
void FightLayer::isCanCutCard()
{
	m_PlayerCardsCanOut.clear();
	for (int i = 0; i != m_PlayerCards[m_iTurn].size(); i++)
	{
		if (this->isCanCutCardRule(m_PlayerCards[m_iTurn][i]->spCard->getTag()))
		{
			m_PlayerCardsCanOut.push_back(m_PlayerCards[m_iTurn][i]);
		}
	}
}
void FightLayer::beforCutSpeiclCardEffect()
{
	//�����һ������ϵͳ�ƵĿ��عر�
	if (!m_bIsFisrtOutCard)
	{
		this->nextTurn();
	}
	//����һ������ϵͳ�ƵĿ��عر�
	m_bIsFisrtOutCard = false;
	//���ܳ����Ʒŵ�m_playerCardsCanout�����������
	this->isCanCutCard();
	//����ֵ����1����ô�����һ������ǰ20��������Ϊ���1������ʾ��
	if (0 == m_iTurn)
	{
		m_iChooseingCardIndex = CCRANDOM_0_1()*m_PlayerCards[m_iTurn].size();
		CCLOG("m_iChooseingCardIndex === %d", m_iChooseingCardIndex);
		m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() + 20);
	}

	switch (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()))
	{
	/*case CardNumber::CARD_7:
	case CardNumber::CARD_8:
		if (m_bIsPunlished)
		{
			//�Ѿ��ͷ����ˣ�����ͨ��һ����
			if (0 == m_iTurn)
			{
				//���1�Լ��ж���ô����
				if (m_PlayerCardsCanOut.size() == 0)
				{
					//û�����ƣ����ƶ���ʾ����
					m_highLight->setVisible(true);
				}
				m_DrawCards->setVisible(true);//�������ƵĴ�������
				//���ƵĴ������ؿ���
				m_bIsTouchEnabel = true;
			}
			else
			{
				//�����ж���ô����
				if (m_PlayerCardsCanOut.size() != 0)
				{
					//���Գ��Ƶ�ai�㷨
					this->AIchoosedCutIndex();
				}
				else
				{
					//���Ʋ���
					this->onDrawCardsHandler((Ref*)m_DrawCards);
				}
			}
		}
		else
		{
			//��û�ͷ������÷�Ϊ�����������һ�ܳ��ơ�������ܳ���
			m_DrawCards->setVisible(false);//���ƵĴ������عر�
			if (0 == m_iTurn)
			{
				//�Ȱ���ʾ�������ƻص�ԭ��
				m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() - 20);
				if (m_PlayerCardsCanOut.size() != 0)
				{
					//���ܳ�����
					//�������ѡ��Ҫ��Ҫ����
					m_top_card->setVisible(true);
					m_give_up->setVisible(true);
				}
				else
				{
					//û���ܳ����ƣ���������
					this->onGiveUpHandler((Ref *)m_give_up);
				}
			}
			else
			{
				if (m_PlayerCardsCanOut.size() != 0)
				{
					//�ܳ���
					//����ֱ�ӾͶ�����
					//ִ�ж��Ƶ�����
					//���Գ��Ƶ�ai�㷨
					this->AIchoosedCutIndex();
				}
				else
				{
					//û���ܳ����ƣ���������
					this->onGiveUpHandler((Ref *)m_give_up);
				}
			}
		}
		break;*/
	default:
		if (0 == m_iTurn)
		{
			//���1�Լ��ж���ô����
			if (m_PlayerCardsCanOut.size() == 0)
			{
				//û�����ƣ����ƶ���ʾ����
				m_highLight->setVisible(true);
			}
			m_DrawCards->setVisible(true);//�������ƵĴ�������
			//���ƵĴ������ؿ���
			m_bIsTouchEnabel = true;
		}
		else
		{
			//�����ж���ô����
			if (m_PlayerCardsCanOut.size() != 0)
			{
				//���Գ��Ƶ�ai�㷨
				this->AIchoosedCutIndex();
			}
			else
			{
				//���Ʋ���
				this->onDrawCardsHandler((Ref*)m_DrawCards);
			}
		}
		break;
	}
}
void FightLayer::cutCardRule()
{
	//ԭ�е��Ƶ�λ����Ҫ����
	for (int j = 0; j < m_iChooseingCardIndex; j++)
	{
		m_PlayerCards[m_iTurn][j]->spCard->setPositionX(m_PlayerCards[m_iTurn][j]->spCard->getPositionX() + m_PlayerCards[m_iTurn][j]->spCard->getContentSize().width / 2);
	}
	for (int k = m_iChooseingCardIndex; k != m_PlayerCards[m_iTurn].size(); k++)
	{
		m_PlayerCards[m_iTurn][k]->spCard->setPositionX(m_PlayerCards[m_iTurn][k]->spCard->getPositionX() - m_PlayerCards[m_iTurn][k]->spCard->getContentSize().width / 2);
	}
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setVisible(true);
	//�߼��㴦���ˣ�
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPosition(m_ShufflingCards[0]->spCard->getPosition());
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setLocalZOrder(m_iZOrder);
	m_iZOrder++;
	m_ShufflingCards.push_back(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]);
	std::vector<sCardProperties* >::iterator it;
	for (it = m_PlayerCards[m_iTurn].begin(); it != m_PlayerCards[m_iTurn].end();)
	{
		if ((*it)->spCard->getTag() == m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getTag())
		{
			it = m_PlayerCards[m_iTurn].erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
	//���¸���ҵ�����
	this->updateLeftCardsView(m_iTurn);
	//�жϸ�����Ƿ����Ƴ�����
	if (m_PlayerCards[m_iTurn].size() == 0)
	{
		bool isDouble/* = (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size()- 1]->spCard->getTag()) == CardNumber::CARD_J)*/;
		this->updataScoreView(isDouble);
		//�����ƶѵ���ȫ����ֲ��ϴ�ƶ�����
		m_ShufflingCards.insert(m_ShufflingCards.end(), m_CardsPile.begin(), m_CardsPile.end());
		//������ƶ�����
		m_CardsPile.clear();
		//�������
		for (int i = 0; i < PLAYER_NUMBER; i++)
		{
			if (0 != m_PlayerCards[i].size())
			{
				//��������ƶѵ���ȫ����ֲ��ϴ�ƶ�����
				m_ShufflingCards.insert(m_ShufflingCards.end(), m_PlayerCards[i].begin(), m_PlayerCards[i].end());
				//��������������
				m_PlayerCards[i].clear();
				//������ҵ�����
				this->updateLeftCardsView(i);
			}
		}
		CCLOG("m_ShufflingCards.size == %d", m_ShufflingCards.size());
		if (m_iRemainPlayer == 1)
		{
			//��Ϸ����
			if (m_iLoseScore[0] < 100)
			{
				//win
				GameManage::GetInstance()->setPlayerWinOrLose(true);
			}
			else
			{
				//lose
				GameManage::GetInstance()->setPlayerWinOrLose(false);
			}
			//����µ�ͼ�㡣���Ʋ˵���ť
			//��ͣ���еĶ���
			GameManage::GetInstance()->RevursivelyPauseAllChildren(this);
			m_gameOverLayer = GameOverLayer::create();
			this->addChild(m_gameOverLayer, INT_MAX);
			return;
		}
		else
		{
			//����µ�ͼ�㡣���Ʋ˵���ť
			//��ͣ���еĶ���
			GameManage::GetInstance()->RevursivelyPauseAllChildren(this);
			m_gameScoreLayer = GameScoreLayer::create();
			this->addChild(m_gameScoreLayer, INT_MAX);

			//����ϴ��
			this->shuffCards();
		}
	}
	else
	{
		//����֮���ֵ���һ�����
		this->afterCutSpeiclCardEffect();
	}
}
void FightLayer::afterCutSpeiclCardEffect()
{
	//�������عر�
	m_bIsTouchEnabel = false;
	//ÿ�γ����ƾͰ���ɫѡ����ʾ�������ص�
	Window_Colortip->setVisible(false);
	//����ϴ�ƶ���������ƵĲ�ͬ������ͬ�Ĵ���
	switch (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()))
	{
	/*case CardNumber::CARD_A:
		//�ı���Ƶ�˳��
		m_bOrder = !m_bOrder;
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		break;
	case CardNumber::CARD_7:
		//�ͷ���������Ϊ��
		m_bIsPunlished = false;
		//�����Ƶ�������2
		m_iPunlishCardNumber = m_iPunlishCardNumber + 2;
		//this->beforCutSpeiclCardEffect(0);
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		break;
	case CardNumber::CARD_8:
		//�ͷ���������Ϊ��
		m_bIsPunlished = false;
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
		//this->beforCutSpeiclCardEffect(0);
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		break;
	case CardNumber::CARD_J:
		if (0 == m_iTurn)
		{
			m_bIsTouchEnabel = false;
			m_DrawCards->setVisible(false);
			if (m_bIsFisrtOutCard)
			{
				//ϵͳ�ķ�������Ϊj�����ѡ��һ����ɫ��ʼ
				int iChoosedColor = CCRANDOM_0_1() * 4 + 1;
				//������ɫѡ���ı��֣�����ѡ�����ɫ����������
				this->updateChooseColorView(iChoosedColor);
				this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
			}
			else
			{
				//����Լ�ѡ����ɫ
				Window_Cardchoose->setVisible(true);
			}
		}
		else
		{
			//�����жϸ�ѡ������
			//aiѡ����ɫ
			int	iChoosedColor = this->getAIchoosedColor();
			//������ɫѡ���ı��֣�����ѡ�����ɫ����������
			this->updateChooseColorView(iChoosedColor);
			this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
			//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		}
		break;*/
	default:
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		break;
	}
}
int FightLayer::getAIchoosedColor()
{
	//�滻���㷨
	int iRandom = CCRANDOM_0_1() * 4 + 1;
	return iRandom;
}
void FightLayer::AIchoosedCutIndex()
{
	for (int i = 0; i != m_PlayerCards[m_iTurn].size(); i++)
	{
		if (m_PlayerCards[m_iTurn][i]->spCard->getTag() == m_PlayerCardsCanOut[0]->spCard->getTag())
		{
			m_iChooseingCardIndex = i;
			this->cutCard();
			break;
		}
	}
}
void FightLayer::nextTurn()
{
	if (m_bOrder)
	{
		m_iTurn = m_iTurn + 1;
		for (int i = m_iTurn; i < m_iTurn + PLAYER_NUMBER;i++)
		{
			if (m_iLoseScore[i%PLAYER_NUMBER] < 100)
			{
				m_iTurn = i%PLAYER_NUMBER;
				break;
			}
		}
	}
	else
	{
		m_iTurn = m_iTurn - 1;
		for (int i = m_iTurn; i > m_iTurn - PLAYER_NUMBER; i--)
		{
			int temp = i + (i < 0) * PLAYER_NUMBER;
			if (m_iLoseScore[temp] < 100)
			{
				m_iTurn = temp;
				break;
			}
		}
	}
	CCLOG("nowturn=====%d",m_iTurn);
}
void FightLayer::onPopTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() ϵ ֡�¼�������
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "CutTempCardOver"))
	{
		this->onArrowUpHandler((Ref*)m_ArrowUp);
	}
}
void FightLayer::popTempCard()
{
	char str[24];
	sprintf(str, "name%dCutTempCard", m_iTurn + 1);
	//����ָ������������ϴ�ƶ��еĶ���
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(FightLayer::onPopTempCardFrameEvent));
}
void FightLayer::onPushTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() ϵ ֡�¼�������
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "AddTempToPlayerCardOver"))
	{
		this->onArrowDownHandler((Ref*)m_ArrowDown);
	}
}
void FightLayer::pushTempCard()
{
	char str[32];
	sprintf(str, "name%dAddTempToPlayerCard", m_iTurn + 1);
	//����ָ������,ѹ��������Ķ��еĶ���
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(FightLayer::onPushTempCardFrameEvent));
}
