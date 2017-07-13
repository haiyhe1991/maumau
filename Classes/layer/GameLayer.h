#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "mau.h"
#include "BaseLayer.h"
#include "ShadeLayer/ShadeLayer.h"
#include "SpriteButton/SpriteButton.h"
#include "msg/message.h"


#define PLAYER_NUMBER    4
#define PER_START_CARDS_NUMBER 5
#define PLAYER_MAX_CARDS_WIDTH_NUMBER 12
#define CARD_COLOR(cardTag) (cardTag)%4+1
#define CARD_NUMBER(cardTag) (cardTag)/8+1
#define CARD_VALUE(cardTag) ((4-CARD_COLOR(cardTag))*13+CARD_NUMBER(cardTag))
#define PER_TURN_TIME   1.0//每个玩家轮流的时间间隔
#define TEMP_CARD_SHOW_TIME  0.5//电脑抓在手上的牌然后显示时间

class GameOverLayer :public ShadeLayer
{
public:
	GameOverLayer();
	~GameOverLayer();
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
private:
	Layout*					layout;					//得分层资源
	void					onExitHandler(Ref *ob);	//点击的处理事件


};
class GameScoreLayer :public ShadeLayer
{
public:
	GameScoreLayer();
	~GameScoreLayer();
	virtual bool init();
	CREATE_FUNC(GameScoreLayer);
private:
	Layout*					layout;					//得分层资源
	Button*					continue_game;			//游戏继续按钮
	void					onContinueHandler(Ref* sender);	//点击的处理事件


};

class GameMenuLayer :public ShadeLayer
{
public:
	GameMenuLayer();
	~GameMenuLayer();
	virtual bool init();
	CREATE_FUNC(GameMenuLayer);
private:
	Layout*					layout;					//菜单层资源
	Button*					rule_game;				//游戏规则按钮
	Button*					setup_game;				//游戏设置按钮
	Button*                 acheivement_game;       //游戏成就按钮
	Button*					exit_game;				//游戏退出按钮
	Button*					continue_game;			//游戏继续按钮
	void					onRuleHandler(Ref* sender);	//点击的处理事件
	void					onAcheivementHandler(Ref* sender);	//点击的处理事件
	void					onSetupHandler(Ref* sender);	//点击的处理事件
	void					onExitHandler(Ref* sender);	//点击的处理事件
	void					onContinueHandler(Ref* sender);	//点击的处理事件
	
	
};

class ChessLayer : public Layer, GameMessage
{
public:
	virtual bool init();
	CREATE_FUNC(ChessLayer);

	virtual void OnMessage(const int head, void* data);				//接受消息
};

class FightLayer :public Layer
{
public:
	FightLayer();
	~FightLayer();
	virtual bool init();
	CREATE_FUNC(FightLayer);
private:
	struct sCardProperties
	{
		int iCardState;
		SpriteButton *spCard;
	};
	Layout*					layout;					//对战层资源
	Button*					game_menu;				//游戏菜单按钮
	Button*                 m_DrawCards;          //牌堆的摸牌按钮
	Button*                 m_ArrowDown;            //向下的箭头
	Button*                 m_ArrowUp;            //向上的箭头
	Button*                 m_top_card;            //顶牌
	Button*                 m_give_up;            //放弃
	Button*                 m_choose_color[4];        //颜色选择按钮
	Armature*               m_bgCardArmature;      //背景牌的动画资源
	ImageView*              m_highLight;           //底牌的高亮
	ImageView*              uiTempCard;           //电脑思考的牌
	ImageView*              Window_Colortip;       //颜色选择提示窗口
	ImageView*              Window_Cardchoose;       //颜色选择窗口
	ImageView*              Window_Invalid;       //出牌无效窗口
	void                    initName();          //初始化名字
	void                    updataScoreView(bool isDouble = false);       //更新得分
	int                    cardScoreRule(int iCardTag);//计算损失分
	void                    shuffCards();          //洗牌
	void                    shuffRemainCards();     //一局没打完，，洗剩余的牌
	void                    DealCards();            //发牌,现目前只考虑4个玩家的情况发的牌
	void                    firstOutCard();          //翻开第一张牌
	bool                    isCanCutCardRule(int iCardTag);             //是否满足出牌的规则
	void                    isCanCutCard();                  //将能出的牌放到对应的容器里面
	void                    cutCard();                       //出牌动画
	void                    cutCardRule();                       //出牌之后的逻辑和表现处理
	void                    beforCutSpeiclCardEffect();              //特殊牌的效果出之前(真正的进入下一个玩家操作)
	void                    afterCutSpeiclCardEffect();    //特殊牌的效果出了以后
	void                    nextTurn();                      //下一个玩家操作
	int                     getAIchoosedColor();              //获取ai选择的颜色
	void                    AIchoosedCutIndex();           //获取ai选择出牌的下标放到m_iChooseingCardIndex里面
	void                    onGameMenuHandler(Ref *ob);      //点击菜单的处理事件
	void                    onDrawCardsHandler(Ref *ob);      //点击摸牌的处理事件
	void                    onSingleCardHandler(Ref *ob);      //点击摸牌的处理事件
	void                    onArrowUpHandler(Ref *ob);      //点击向上箭头的处理事件
	void                    onArrowDownHandler(Ref *ob);      //点击向下箭头的处理事件
	void                    onTopCardHandler(Ref *ob);      //点击顶牌的处理事件
	void                    onGiveUpHandler(Ref *ob);      //点击放弃的处理事件
	void                    onChooseColorHandler(Ref *ob);      //点击颜色选择的处理事件
	void                    onShuffCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//洗牌帧动画监听
	void                    onDealCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//发牌帧动画监听
	void                    onFirstOutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//翻开第一张牌的动画监听
	void                    onAddTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//玩家摸到的牌放在暂存位置的动画监听
	void                    onPopTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//玩家摸到的牌从缓存位置出到洗牌堆的动画监听
	void                    onPushTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//玩家摸到的牌从缓存位置收回手牌里的动画监听
	void                    onCutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//出牌的动画监听
	void                    updateLeftCardsView(int iTurn);   //更新手上的牌的ui
	void                    updateChooseColorView(int iChooseColor);   //更新选择的颜色
	void                    sortByCardState(std::vector<sCardProperties *>& vectorName,bool bRise = true);//vector按照牌的状态值排序
	void                    addPlayerCard();              //对应位置增加玩家手中的牌
	void                    addTempCard();          //玩家摸到的牌放在暂存位置动画
	void                    popTempCard();          //玩家摸到的牌从缓存位置出到洗牌堆的动画
	void                    pushTempCard();         //玩家摸到的牌从缓存位置收回手牌里的动画
	float                   getPerCardWidth(int iPlayerRemaindCardsNumber,float fPerUICardWidth); //更新每张牌的宽度
	GameMenuLayer *         m_gameMenuLayer;//菜单层
	GameScoreLayer *         m_gameScoreLayer;//得分层
	GameOverLayer *          m_gameOverLayer;//游戏结束层
	
	sCardProperties *m_psCardProperties;
	std::vector<sCardProperties *>m_PlayerCards[PLAYER_NUMBER];
	std::vector<sCardProperties *>m_PlayerCardsCanOut;
	std::vector<sCardProperties *>m_ShufflingCards;
	std::vector<sCardProperties *>m_CardsPile;
	
	int m_iLoseScore[PLAYER_NUMBER];
	int m_iTurn;
	int m_iDealCardStyle;
	int m_iDealCardNumber;
	int m_iRemainPlayer;
	int m_iZOrder;
	int m_iChoosedColor;
	bool m_bOrder;
	bool m_bIsPunlished;
	bool m_bIsFisrtOutCard;
	bool m_bIsTouchEnabel;
	int m_iPunlishCardNumber;
	int m_iChooseingCardIndex;//存放要出的牌的下标
};


class GameLayer :public BaseLayer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void onEnter();							//初始化函数

	virtual list<LoadItem> getResourceList();			//取得资源加载列表

	virtual void releaseResource();					//释放资源


private:
	FightLayer*             m_FightLayer;//对战层

};
#endif
