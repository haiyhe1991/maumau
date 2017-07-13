#include "MusicHelper.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
MusicHelper *MusicHelper::m_pSingleInstance = NULL;
MusicHelper* MusicHelper::GetInstance()
{
	if (m_pSingleInstance == NULL)
	{
		m_pSingleInstance = new MusicHelper();
	}
	return m_pSingleInstance;
}
void MusicHelper::RecoverInstance()
{
	CC_SAFE_DELETE(m_pSingleInstance);
}
MusicHelper::MusicHelper()
{
	m_pUIEffects.push_back(DISTRBUTE_CARD_SOUND);
	m_pUIEffects.push_back(SHUFFLE_CARD_SOUND);

	m_pBackgroundMusic.push_back(FIGHT_BACKGROUND_MUSIC);
	m_pBackgroundMusic.push_back(MENU_BACKGROUND_MUSIC);
	//���ָ�ʽ,
	//android         Mp3  MID  WAV,
	//ios           Mp3  CAF
	//��Ч��ʽ
	//android     OGG����֧�֣�
	//ios             CAF
}

MusicHelper::~MusicHelper()
{
	SimpleAudioEngine::getInstance()->end();
	m_pUIEffects.clear();
	m_pBackgroundMusic.clear();
}



/************************************************************************/
/* ����                                                                     */
/************************************************************************/
void MusicHelper::loadEffect()
{
	std::vector<const char*>::iterator it;
	for(it=m_pUIEffects.begin(); it!=m_pUIEffects.end() ;it++)
	{
		SimpleAudioEngine::getInstance()->preloadEffect(*it);
	}
}

void MusicHelper::unLoadEffect()
{
	std::vector<const char*>::iterator it;
	for(it=m_pUIEffects.begin(); it!=m_pUIEffects.end() ;it++)
	{
		SimpleAudioEngine::getInstance()->unloadEffect((*it));
	}
}	
void MusicHelper::loadMusic()
{
	std::vector<const char *>::iterator it;
	for(it=m_pBackgroundMusic.begin();it!=m_pBackgroundMusic.end();it++)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(*it);
	}
}

void MusicHelper::unLoadMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

/************************************************************************/
/* ֹͣ���� �Ƿ��ͷ�                                                                     */
/************************************************************************/
void MusicHelper::stopMusic(bool bRemove)
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(bRemove);
	}
	
}	
void MusicHelper::SetSoundIsOpen(bool bEffectOpen)
{
	m_bEffectOpen=bEffectOpen;
}
bool MusicHelper::GetSoundIsOpen()
{
	return m_bEffectOpen;
}
void MusicHelper::SetMusicIsOpen(bool bMusicOpen)
{
	m_bMusicOpen=bMusicOpen;
}
bool MusicHelper::GetMusicIsOpen()
{
	return m_bMusicOpen;
}

/************************************************************************/
/* ��ͣ����                                                                     */
/************************************************************************/
void MusicHelper::pauseMusic()
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		this->SetMusicIsOpen(false);
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
}
/************************************************************************/
/* ������������                                                                     */
/************************************************************************/
void MusicHelper::resumeMusic()
{
	//if(m_bEffectOpen){
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			this->SetMusicIsOpen(true);
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	//}
}
/************************************************************************/
/* ��������                                                                     */
/************************************************************************/
void MusicHelper::playMusic( const char* pszFilePath, bool loop )
{
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	if(this->GetMusicIsOpen())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath, loop);
	}
}

/************************************************************************/
/* ������Ч                                                                     */
/************************************************************************/
int MusicHelper::playEffect( const char* pszFilePath, bool loop)
{
	if(this->GetSoundIsOpen())
	{
		return SimpleAudioEngine::getInstance()->playEffect(pszFilePath, loop);
	}
	return 0;
}
// ֹͣ������Ч��Ч
void MusicHelper::stopAppointSingleEffect(unsigned int iEffectId)
{
	SimpleAudioEngine::getInstance()->stopEffect(iEffectId);
}
// ��ͣ������Ч
void MusicHelper::pauseEffect(unsigned int iEffectId)
{
	if(this->GetSoundIsOpen())
	{
		SimpleAudioEngine::getInstance()->pauseEffect(iEffectId);
	}
}
//�ָ�������Ч
void MusicHelper::resumeEffect(unsigned int iEffectId)
{
	if(!this->GetSoundIsOpen())
	{
		SimpleAudioEngine::getInstance()->resumeEffect(iEffectId);
	}
}
//�ָ���Ч
void MusicHelper::ResumeAllEffect()
{
	if(!this->GetSoundIsOpen())
	{
		this->SetSoundIsOpen(true);
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}
// ��ͣ��Ч
void MusicHelper::PauseAllEffect()
{
	if(this->GetSoundIsOpen())
	{
	this->SetSoundIsOpen(false);
	SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
}
//�������ֿ���
void MusicHelper::openMusic(const char* pszFilePath)
{

	//m_bMusicOpen = true;
	this->playMusic(pszFilePath,true);	
}
// �ر����ֿ���
void MusicHelper::closeMusic(bool bRemove)
{
	//if(m_bMusicOpen)
	{
		//m_bMusicOpen = false;
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(bRemove);
	}	
}
// �л����� �л���������
void MusicHelper::ChangeMusic(const char* pszFilePath,bool bRemove)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(bRemove);
	this->playMusic(pszFilePath,true);	
}