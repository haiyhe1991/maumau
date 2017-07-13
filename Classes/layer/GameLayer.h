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
#define PER_TURN_TIME   1.0//ÿ�����������ʱ����
#define TEMP_CARD_SHOW_TIME  0.5//����ץ�����ϵ���Ȼ����ʾʱ��

class GameOverLayer :public ShadeLayer
{
public:
	GameOverLayer();
	~GameOverLayer();
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
private:
	Layout*					layout;					//�÷ֲ���Դ
	void					onExitHandler(Ref *ob);	//����Ĵ����¼�


};
class GameScoreLayer :public ShadeLayer
{
public:
	GameScoreLayer();
	~GameScoreLayer();
	virtual bool init();
	CREATE_FUNC(GameScoreLayer);
private:
	Layout*					layout;					//�÷ֲ���Դ
	Button*					continue_game;			//��Ϸ������ť
	void					onContinueHandler(Ref* sender);	//����Ĵ����¼�


};

class GameMenuLayer :public ShadeLayer
{
public:
	GameMenuLayer();
	~GameMenuLayer();
	virtual bool init();
	CREATE_FUNC(GameMenuLayer);
private:
	Layout*					layout;					//�˵�����Դ
	Button*					rule_game;				//��Ϸ����ť
	Button*					setup_game;				//��Ϸ���ð�ť
	Button*                 acheivement_game;       //��Ϸ�ɾͰ�ť
	Button*					exit_game;				//��Ϸ�˳���ť
	Button*					continue_game;			//��Ϸ������ť
	void					onRuleHandler(Ref* sender);	//����Ĵ����¼�
	void					onAcheivementHandler(Ref* sender);	//����Ĵ����¼�
	void					onSetupHandler(Ref* sender);	//����Ĵ����¼�
	void					onExitHandler(Ref* sender);	//����Ĵ����¼�
	void					onContinueHandler(Ref* sender);	//����Ĵ����¼�
	
	
};

class ChessLayer : public Layer, GameMessage
{
public:
	virtual bool init();
	CREATE_FUNC(ChessLayer);

	virtual void OnMessage(const int head, void* data);				//������Ϣ
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
	Layout*					layout;					//��ս����Դ
	Button*					game_menu;				//��Ϸ�˵���ť
	Button*                 m_DrawCards;          //�ƶѵ����ư�ť
	Button*                 m_ArrowDown;            //���µļ�ͷ
	Button*                 m_ArrowUp;            //���ϵļ�ͷ
	Button*                 m_top_card;            //����
	Button*                 m_give_up;            //����
	Button*                 m_choose_color[4];        //��ɫѡ��ť
	Armature*               m_bgCardArmature;      //�����ƵĶ�����Դ
	ImageView*              m_highLight;           //���Ƶĸ���
	ImageView*              uiTempCard;           //����˼������
	ImageView*              Window_Colortip;       //��ɫѡ����ʾ����
	ImageView*              Window_Cardchoose;       //��ɫѡ�񴰿�
	ImageView*              Window_Invalid;       //������Ч����
	void                    initName();          //��ʼ������
	void                    updataScoreView(bool isDouble = false);       //���µ÷�
	int                    cardScoreRule(int iCardTag);//������ʧ��
	void                    shuffCards();          //ϴ��
	void                    shuffRemainCards();     //һ��û���꣬��ϴʣ�����
	void                    DealCards();            //����,��Ŀǰֻ����4����ҵ����������
	void                    firstOutCard();          //������һ����
	bool                    isCanCutCardRule(int iCardTag);             //�Ƿ�������ƵĹ���
	void                    isCanCutCard();                  //���ܳ����Ʒŵ���Ӧ����������
	void                    cutCard();                       //���ƶ���
	void                    cutCardRule();                       //����֮����߼��ͱ��ִ���
	void                    beforCutSpeiclCardEffect();              //�����Ƶ�Ч����֮ǰ(�����Ľ�����һ����Ҳ���)
	void                    afterCutSpeiclCardEffect();    //�����Ƶ�Ч�������Ժ�
	void                    nextTurn();                      //��һ����Ҳ���
	int                     getAIchoosedColor();              //��ȡaiѡ�����ɫ
	void                    AIchoosedCutIndex();           //��ȡaiѡ����Ƶ��±�ŵ�m_iChooseingCardIndex����
	void                    onGameMenuHandler(Ref *ob);      //����˵��Ĵ����¼�
	void                    onDrawCardsHandler(Ref *ob);      //������ƵĴ����¼�
	void                    onSingleCardHandler(Ref *ob);      //������ƵĴ����¼�
	void                    onArrowUpHandler(Ref *ob);      //������ϼ�ͷ�Ĵ����¼�
	void                    onArrowDownHandler(Ref *ob);      //������¼�ͷ�Ĵ����¼�
	void                    onTopCardHandler(Ref *ob);      //������ƵĴ����¼�
	void                    onGiveUpHandler(Ref *ob);      //��������Ĵ����¼�
	void                    onChooseColorHandler(Ref *ob);      //�����ɫѡ��Ĵ����¼�
	void                    onShuffCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//ϴ��֡��������
	void                    onDealCardsFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//����֡��������
	void                    onFirstOutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//������һ���ƵĶ�������
	void                    onAddTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//����������Ʒ����ݴ�λ�õĶ�������
	void                    onPopTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//����������ƴӻ���λ�ó���ϴ�ƶѵĶ�������
	void                    onPushTempCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//����������ƴӻ���λ���ջ�������Ķ�������
	void                    onCutCardFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);//���ƵĶ�������
	void                    updateLeftCardsView(int iTurn);   //�������ϵ��Ƶ�ui
	void                    updateChooseColorView(int iChooseColor);   //����ѡ�����ɫ
	void                    sortByCardState(std::vector<sCardProperties *>& vectorName,bool bRise = true);//vector�����Ƶ�״ֵ̬����
	void                    addPlayerCard();              //��Ӧλ������������е���
	void                    addTempCard();          //����������Ʒ����ݴ�λ�ö���
	void                    popTempCard();          //����������ƴӻ���λ�ó���ϴ�ƶѵĶ���
	void                    pushTempCard();         //����������ƴӻ���λ���ջ�������Ķ���
	float                   getPerCardWidth(int iPlayerRemaindCardsNumber,float fPerUICardWidth); //����ÿ���ƵĿ��
	GameMenuLayer *         m_gameMenuLayer;//�˵���
	GameScoreLayer *         m_gameScoreLayer;//�÷ֲ�
	GameOverLayer *          m_gameOverLayer;//��Ϸ������
	
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
	int m_iChooseingCardIndex;//���Ҫ�����Ƶ��±�
};


class GameLayer :public BaseLayer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void onEnter();							//��ʼ������

	virtual list<LoadItem> getResourceList();			//ȡ����Դ�����б�

	virtual void releaseResource();					//�ͷ���Դ


private:
	FightLayer*             m_FightLayer;//��ս��

};
#endif
