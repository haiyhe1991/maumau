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
	//添加事件监听
	game_menu->addClickEventListener(CC_CALLBACK_1(FightLayer::onGameMenuHandler, this));

	m_DrawCards = (Button *)layout->getChildByName("DrawCards");
	m_DrawCards->addClickEventListener(CC_CALLBACK_1(FightLayer::onDrawCardsHandler, this));

	//根据动画名称创建动画精灵
	m_bgCardArmature = Armature::create("NewAnimation");
	//设置动画精灵位置
	m_bgCardArmature->setPosition(m_DrawCards->getPositionX(), m_DrawCards->getPositionY());
	//添加到当前页面
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
	//初始化名字
	this->initName();
	//更新得分
	this->updataScoreView(false);
	//牌的产生顺序是黑A，红A。。黑A。。。方k
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
	//计算损失的分
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
	//首先把牌堆容器清理干净
	m_CardsPile.clear();
	//初始化牌的叠放顺序，，这里是先初始化洗牌堆的牌的叠放顺序0，1，2，3.。。
	for (int i = m_ShufflingCards.size(); i != 0; --i)
	{
		m_ShufflingCards[i - 1]->spCard->setVisible(false);
		m_ShufflingCards[i - 1]->iCardState = i - 1;
	}
	//真正的执行洗牌的操作，通过随机数，改变洗牌堆的牌的叠放顺序
	for (int i = m_ShufflingCards.size(); i != 0; --i)
	{
		int iRandom = CCRANDOM_0_1()*i;
		int temp = m_ShufflingCards[i - 1]->iCardState;
		m_ShufflingCards[i - 1]->iCardState = m_ShufflingCards[iRandom]->iCardState;
		m_ShufflingCards[iRandom]->iCardState = temp;
	}
	//将洗牌堆的牌全部移植到摸牌堆容器
	m_CardsPile.insert(m_CardsPile.end(), m_ShufflingCards.begin(), m_ShufflingCards.end());
	//把摸牌堆的牌按照牌的状态值重新叠放，排序。
	this->sortByCardState(m_CardsPile, true);
	//清理干净洗牌堆容器
	m_ShufflingCards.clear();
	//发牌的方式初始化为开始发牌
	/*m_iDealCardStyle = DealCardStyle::StartDealCard;*/
	//发牌顺序初始化为顺时针
	m_bOrder = true;
	//初始化洗牌堆得牌的渲染层级为0
	m_iZOrder = 0;
	//初始化发牌的起始位置
	m_iTurn = 0;
	//这是设计多人玩家一起玩时。如果玩家输了。。其他人接着玩
	for (int i = m_iTurn; i < m_iTurn + PLAYER_NUMBER; i++)
	{
		if (m_iLoseScore[i%PLAYER_NUMBER] < 100)
		{
			m_iTurn = i%PLAYER_NUMBER;
			break;
		}
	}
	//初始化已经发了的牌的张数
	m_iDealCardNumber = 0;
	//初始化第一张牌为系统翻开的。不是玩家打出来的
	m_bIsFisrtOutCard = true;
	//手牌的触摸开关关闭
	m_bIsTouchEnabel = false;
	//隐藏颜色提示
	Window_Colortip->setVisible(false);
	//执行洗牌的动画
	//播放指定动作
	m_bgCardArmature->getAnimation()->play("shuffCards");
	//设置动画的帧监听
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onShuffCardsFrameEvent));
}
void FightLayer::shuffRemainCards()
{
	//首先把牌堆容器清理干净
	m_CardsPile.clear();
	//初始化牌的叠放顺序，，这里是先初始化洗牌堆的牌的叠放顺序0，1，2，3.。。
	for (int i = m_ShufflingCards.size() - 1; i != 0; --i)
	{
		m_ShufflingCards[i - 1]->spCard->setVisible(false);
		m_ShufflingCards[i - 1]->iCardState = i - 1;
	}
	//真正的执行洗牌的操作，通过随机数，改变洗牌堆的牌的叠放顺序
	for (int i = m_ShufflingCards.size() - 1; i != 0; --i)
	{
		int iRandom = CCRANDOM_0_1()*i;
		int temp = m_ShufflingCards[i - 1]->iCardState;
		m_ShufflingCards[i - 1]->iCardState = m_ShufflingCards[iRandom]->iCardState;
		m_ShufflingCards[iRandom]->iCardState = temp;
	}
	//将洗牌堆的牌全部移植到摸牌堆容器
	m_CardsPile.insert(m_CardsPile.end(), m_ShufflingCards.begin(), m_ShufflingCards.end() - 1);
	//把摸牌堆的牌按照牌的状态值重新叠放，排序。
	this->sortByCardState(m_CardsPile, true);
	//先把最后一张牌坊放到一边儿
	sCardProperties *pTempsCardProperties = m_ShufflingCards[m_ShufflingCards.size() - 1];
	//清理干净洗牌堆容器
	m_ShufflingCards.clear();
	//将最后一张牌放到洗牌堆里去
	m_ShufflingCards.push_back(pTempsCardProperties);
	//初始化洗牌堆得牌的渲染层级为0
	m_iZOrder = 0;
	//保留原先的牌的最后一张不动
	m_ShufflingCards[0]->spCard->setLocalZOrder(m_iZOrder);
	m_iZOrder++; 
	//手牌的触摸开关关闭
	m_bIsTouchEnabel = false;
	//执行洗牌的动画
	//播放指定动作
	m_bgCardArmature->getAnimation()->play("shuffCards");
	//设置动画的帧监听
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onShuffCardsFrameEvent));
}
void FightLayer::onGameMenuHandler(Ref *ob)
{
	//暂停所有的动画
	GameManage::GetInstance()->RevursivelyPauseAllChildren(this);
	m_gameMenuLayer = GameMenuLayer::create();
	this->addChild(m_gameMenuLayer, INT_MAX);
}
void FightLayer::onDrawCardsHandler(Ref *ob)
{
	if (0 == m_iTurn)
	{
		m_highLight->setVisible(false);
		m_DrawCards->setVisible(false);//摸牌的触摸开关关闭
		//摸牌的话，先把提示的那张牌收回原地
		m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() - 20);
	}
	//执行添加缓存牌的动画
	CCLOG("remainnumber = %d", m_CardsPile.size());
	if (0 != m_CardsPile.size())
	{
		this->addTempCard();
	}
	else
	{
		//洗牌
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
	//先把已经提示的牌的位置收回到原位
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() - 20);
	for (int i = 0; i != m_PlayerCards[m_iTurn].size(); ++i)
	{
		if (m_PlayerCards[m_iTurn][i]->spCard->getTag() == tag)
		{
			
			if (m_iChooseingCardIndex == i)
			{
				//点击的是同一张牌，那么就判断能不能出，这张牌
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
	//隐藏上下两个箭头
	m_ArrowUp->setVisible(false);
	m_ArrowDown->setVisible(false);
	//将摸牌堆最上面的牌放到洗牌的容器里面
	m_ShufflingCards.push_back(m_CardsPile[m_CardsPile.size() - 1]);
	//将魔派堆最上面的牌显示出来，初始化摆饭的位置，以及渲染层级
	m_CardsPile[m_CardsPile.size() - 1]->spCard->setVisible(true);
	m_CardsPile[m_CardsPile.size() - 1]->spCard->setPosition(Vec2(585, 256));
	m_CardsPile[m_CardsPile.size() - 1]->spCard->setLocalZOrder(m_iZOrder);
	//渲染层级相应的要加1，为后面叠放的牌做准备。实现后来的牌放在前面的牌上面。
	m_iZOrder++;
	//将摸牌堆最后一张牌移出容器
	m_CardsPile.pop_back();
	//由第一个玩家操作。相当于出完牌要加上特殊拍的效果进入当前玩家出牌的步骤里
	this->afterCutSpeiclCardEffect();
	
}
void FightLayer::onArrowDownHandler(Ref *ob)
{
	//隐藏上下两个箭头按钮
	m_ArrowUp->setVisible(false);
	m_ArrowDown->setVisible(false);
	//增加到玩家手牌堆中
	this->addPlayerCard();
	//轮到下一个玩家操作，这儿因为没有出牌。所以不需要加特殊的效果
	//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
	this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
}
void FightLayer::onTopCardHandler(Ref *ob)
{
	//顶牌和放弃按钮隐藏
	m_top_card->setVisible(false);
	m_give_up->setVisible(false);
	//提示牌升起
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() + 20);
	m_bIsTouchEnabel = true;
}
void FightLayer::onGiveUpHandler(Ref *ob)
{
	m_bIsTouchEnabel = false;
	//放弃出牌，也就是接受了惩罚
	m_bIsPunlished = true;
	//顶牌和放弃按钮隐藏
	m_top_card->setVisible(false);
	m_give_up->setVisible(false);
	/*if (CardNumber::CARD_7==CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()))
	{
		//罚牌
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
	//隐藏颜色选择窗口
	Window_Cardchoose->setVisible(false);
	//显示颜色提示窗口
	Window_Colortip->setVisible(true);
	//选择的颜色赋值给对应的成员变量，以便后面进行判断
	m_iChoosedColor = iChooseColor;
	//更新颜色选择表现的图片为指定的颜色
	ImageView *ColortipSelect = (ImageView *)Window_Colortip->getChildByName("ColortipSelect");
	char str[24];
	sprintf(str, "Colortip%d.png", iChooseColor);
	ColortipSelect->loadTexture(str, ui::Widget::TextureResType::PLIST);
}
void FightLayer::onShuffCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() 系 帧事件的名称
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "shuffCardsOver"))//动画结束的帧事件名
	{
		//洗牌完了执行发牌
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
	//   evt.c_str() 系 帧事件的名称
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "DealCardOver"))//动画结束的帧事件名
	{
		switch (m_iDealCardStyle)
		{
		/*case DealCardStyle::StartDealCard:
			//增加玩家手中的牌容器
			this->addPlayerCard();
			//轮到下一个玩家
			this->nextTurn();
			//已经发的牌的张数加1
			m_iDealCardNumber++;
			
			if (m_iDealCardNumber != PER_START_CARDS_NUMBER*m_iRemainPlayer)
			{
				//如果发牌没发到剩余玩家个数*5张，那么继续发牌
				this->DealCards();
			}
			else
			{
				//否则就翻开第一张牌，作为底牌，
				this->firstOutCard();
			}
			break;
		case DealCardStyle::PunlishCard:
			//增加玩家手中的牌
			this->addPlayerCard();
			//惩罚的牌张数减1
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
					//洗牌
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
	//播放指定动作（发牌一共有4个玩家，所以需要播放4种不同的动画）
	m_bgCardArmature->getAnimation()->play(str);
	//发牌的动画监听
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onDealCardsFrameEvent));

}
void FightLayer::cutCard()
{

	//播放指定动作
	char str[24];
	sprintf(str, "name%dCutCard", m_iTurn + 1);
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onCutCardFrameEvent));
}
void FightLayer::onCutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() 系 帧事件的名称
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "CutCardOver"))
	{

		this->cutCardRule();
	}
}
//翻开第一张牌的动画
void FightLayer::firstOutCard()
{
	//播放指定动作
	m_bgCardArmature->getAnimation()->play("firstOutCard");
	//翻开第一张牌的动画监听
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onFirstOutCardFrameEvent));
}
void FightLayer::onFirstOutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() 系 帧事件的名称
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "firstOutCardOver"))//翻开第一张牌的动画帧结束事件
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
		//如果新来的牌最小
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
		Vec2 PlayerCardsPoint[PLAYER_NUMBER] = { Vec2(480, 109), Vec2(269, 437), Vec2(485, 437), Vec2(712, 437) };     //玩家手中牌的位置
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
	//将牌存到缓存里面的动画
	char str[24];
	sprintf(str, "name%dAddTempCard", m_iTurn+1);
	//播放指定动作
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, SEL_FrameEventCallFunc(&FightLayer::onAddTempCardFrameEvent));
}
void FightLayer::onAddTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	CCLOG("----- %s, --- %d    ---    %d", evt.c_str(), originFrameIndex, currentFrameIndex);
	if (!strcmp(evt.c_str(), "AddTempCardOver"))//缓存动画结束
	{
		Vec2 PlayerCardsPoint[PLAYER_NUMBER] = { Vec2(480, 182), Vec2(269, 407), Vec2(485, 407), Vec2(712, 407) };
		
		//将牌移到相应的缓存位置，但是容器不变
		m_CardsPile[m_CardsPile.size() - 1]->spCard->setPosition(PlayerCardsPoint[m_iTurn]);
		CCLOG("getCard: color==%d number===%d", CARD_COLOR(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()), CARD_NUMBER(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()));
		if (0 == m_iTurn)
		{
			//如果是玩家1，那么显示该牌
			m_CardsPile[m_CardsPile.size() - 1]->spCard->setVisible(true);
			//显示向下的箭头的按钮
			m_ArrowDown->setVisible(true);
			//如果缓存的牌能出，那么显示向上的箭头的按钮
			if (this->isCanCutCardRule(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()))
			{
				//玩家自行判断要不要出这张牌
				m_ArrowUp->setVisible(true);
			}
			m_bIsTouchEnabel = false;
		}
		else
		{
			Vec2 TempCardPoint[PLAYER_NUMBER - 1] = { Vec2(267, 317), Vec2(485, 317), Vec2(712, 317) };
			//表现一下ai的牌摸到缓存位置了。
			uiTempCard->setPosition(TempCardPoint[m_iTurn-1]);
			if (this->isCanCutCardRule(m_CardsPile[m_CardsPile.size() - 1]->spCard->getTag()))
			{
				//摸到的牌能出。那就直接出了
				uiTempCard->runAction(Sequence::create(Show::create(), DelayTime::create(TEMP_CARD_SHOW_TIME), Hide::create(), CallFunc::create(CC_CALLBACK_0(FightLayer::popTempCard, this)), NULL));
			}
			else
			{
				//摸到的牌不能出
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
	//如果第一张牌是系统牌的开关关闭
	if (!m_bIsFisrtOutCard)
	{
		this->nextTurn();
	}
	//将第一张牌是系统牌的开关关闭
	m_bIsFisrtOutCard = false;
	//将能出的牌放到m_playerCardsCanout这个容器里面
	this->isCanCutCard();
	//如果轮到玩家1，那么随意抽一张牌上前20个像素作为玩家1操作提示。
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
			//已经惩罚过了，跟普通牌一样的
			if (0 == m_iTurn)
			{
				//玩家1自己判断怎么出牌
				if (m_PlayerCardsCanOut.size() == 0)
				{
					//没法出牌，摸牌堆显示高亮
					m_highLight->setVisible(true);
				}
				m_DrawCards->setVisible(true);//开启摸牌的触摸开关
				//手牌的触摸开关开启
				m_bIsTouchEnabel = true;
			}
			else
			{
				//电脑判断怎么出牌
				if (m_PlayerCardsCanOut.size() != 0)
				{
					//电脑出牌的ai算法
					this->AIchoosedCutIndex();
				}
				else
				{
					//摸牌操作
					this->onDrawCardsHandler((Ref*)m_DrawCards);
				}
			}
		}
		else
		{
			//还没惩罚过，得分为两种情况，其一能出牌。其二不能出牌
			m_DrawCards->setVisible(false);//摸牌的触摸开关关闭
			if (0 == m_iTurn)
			{
				//先把提示的那张牌回到原地
				m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setPositionY(m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->getPositionY() - 20);
				if (m_PlayerCardsCanOut.size() != 0)
				{
					//有能出的牌
					//玩家自行选择要不要顶牌
					m_top_card->setVisible(true);
					m_give_up->setVisible(true);
				}
				else
				{
					//没有能出的牌，放弃治疗
					this->onGiveUpHandler((Ref *)m_give_up);
				}
			}
			else
			{
				if (m_PlayerCardsCanOut.size() != 0)
				{
					//能出牌
					//电脑直接就顶牌了
					//执行顶牌的内容
					//电脑出牌的ai算法
					this->AIchoosedCutIndex();
				}
				else
				{
					//没有能出的牌，放弃治疗
					this->onGiveUpHandler((Ref *)m_give_up);
				}
			}
		}
		break;*/
	default:
		if (0 == m_iTurn)
		{
			//玩家1自己判断怎么出牌
			if (m_PlayerCardsCanOut.size() == 0)
			{
				//没法出牌，摸牌堆显示高亮
				m_highLight->setVisible(true);
			}
			m_DrawCards->setVisible(true);//开启摸牌的触摸开关
			//手牌的触摸开关开启
			m_bIsTouchEnabel = true;
		}
		else
		{
			//电脑判断怎么出牌
			if (m_PlayerCardsCanOut.size() != 0)
			{
				//电脑出牌的ai算法
				this->AIchoosedCutIndex();
			}
			else
			{
				//摸牌操作
				this->onDrawCardsHandler((Ref*)m_DrawCards);
			}
		}
		break;
	}
}
void FightLayer::cutCardRule()
{
	//原有的牌的位置需要处理
	for (int j = 0; j < m_iChooseingCardIndex; j++)
	{
		m_PlayerCards[m_iTurn][j]->spCard->setPositionX(m_PlayerCards[m_iTurn][j]->spCard->getPositionX() + m_PlayerCards[m_iTurn][j]->spCard->getContentSize().width / 2);
	}
	for (int k = m_iChooseingCardIndex; k != m_PlayerCards[m_iTurn].size(); k++)
	{
		m_PlayerCards[m_iTurn][k]->spCard->setPositionX(m_PlayerCards[m_iTurn][k]->spCard->getPositionX() - m_PlayerCards[m_iTurn][k]->spCard->getContentSize().width / 2);
	}
	m_PlayerCards[m_iTurn][m_iChooseingCardIndex]->spCard->setVisible(true);
	//逻辑层处理了，
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
	//更新该玩家的手牌
	this->updateLeftCardsView(m_iTurn);
	//判断该玩家是否手牌出完了
	if (m_PlayerCards[m_iTurn].size() == 0)
	{
		bool isDouble/* = (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size()- 1]->spCard->getTag()) == CardNumber::CARD_J)*/;
		this->updataScoreView(isDouble);
		//将摸牌堆的牌全部移植到洗牌堆容器
		m_ShufflingCards.insert(m_ShufflingCards.end(), m_CardsPile.begin(), m_CardsPile.end());
		//清空摸牌堆容器
		m_CardsPile.clear();
		//所有玩家
		for (int i = 0; i < PLAYER_NUMBER; i++)
		{
			if (0 != m_PlayerCards[i].size())
			{
				//将玩家手牌堆的牌全部移植到洗牌堆容器
				m_ShufflingCards.insert(m_ShufflingCards.end(), m_PlayerCards[i].begin(), m_PlayerCards[i].end());
				//清空玩家手牌容器
				m_PlayerCards[i].clear();
				//隐藏玩家的手牌
				this->updateLeftCardsView(i);
			}
		}
		CCLOG("m_ShufflingCards.size == %d", m_ShufflingCards.size());
		if (m_iRemainPlayer == 1)
		{
			//游戏结束
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
			//添加新的图层。类似菜单按钮
			//暂停所有的动画
			GameManage::GetInstance()->RevursivelyPauseAllChildren(this);
			m_gameOverLayer = GameOverLayer::create();
			this->addChild(m_gameOverLayer, INT_MAX);
			return;
		}
		else
		{
			//添加新的图层。类似菜单按钮
			//暂停所有的动画
			GameManage::GetInstance()->RevursivelyPauseAllChildren(this);
			m_gameScoreLayer = GameScoreLayer::create();
			this->addChild(m_gameScoreLayer, INT_MAX);

			//重新洗牌
			this->shuffCards();
		}
	}
	else
	{
		//出牌之后轮到下一个玩家
		this->afterCutSpeiclCardEffect();
	}
}
void FightLayer::afterCutSpeiclCardEffect()
{
	//触摸开关关闭
	m_bIsTouchEnabel = false;
	//每次出完牌就把颜色选择提示窗口隐藏掉
	Window_Colortip->setVisible(false);
	//根据洗牌堆最上面的牌的不同，做不同的处理
	switch (CARD_NUMBER(m_ShufflingCards[m_ShufflingCards.size() - 1]->spCard->getTag()))
	{
	/*case CardNumber::CARD_A:
		//改变出牌的顺序
		m_bOrder = !m_bOrder;
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		break;
	case CardNumber::CARD_7:
		//惩罚结束开关为假
		m_bIsPunlished = false;
		//罚的牌的数量加2
		m_iPunlishCardNumber = m_iPunlishCardNumber + 2;
		//this->beforCutSpeiclCardEffect(0);
		this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
		//this->scheduleOnce(schedule_selector(FightLayer::beforCutSpeiclCardEffect), PER_TURN_TIME);
		break;
	case CardNumber::CARD_8:
		//惩罚结束开关为假
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
				//系统的翻开的牌为j，随机选择一种颜色开始
				int iChoosedColor = CCRANDOM_0_1() * 4 + 1;
				//更新颜色选择后的表现，并将选择的颜色保存下来。
				this->updateChooseColorView(iChoosedColor);
				this->runAction(Sequence::create(DelayTime::create(PER_TURN_TIME), CallFunc::create(CC_CALLBACK_0(FightLayer::beforCutSpeiclCardEffect, this)), NULL));
			}
			else
			{
				//玩家自己选择颜色
				Window_Cardchoose->setVisible(true);
			}
		}
		else
		{
			//电脑判断该选那种颜
			//ai选择颜色
			int	iChoosedColor = this->getAIchoosedColor();
			//更新颜色选择后的表现，并将选择的颜色保存下来。
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
	//替换该算法
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
	//   evt.c_str() 系 帧事件的名称
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
	//播放指定动作，推入洗牌堆中的动画
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(FightLayer::onPopTempCardFrameEvent));
}
void FightLayer::onPushTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	//   evt.c_str() 系 帧事件的名称
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
	//播放指定动作,压入玩家手拍堆中的动画
	m_bgCardArmature->getAnimation()->play(str);
	m_bgCardArmature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(FightLayer::onPushTempCardFrameEvent));
}
