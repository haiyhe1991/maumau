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
	//音乐格式,
	//android         Mp3  MID  WAV,
	//ios           Mp3  CAF
	//音效格式
	//android     OGG（仅支持）
	//ios             CAF
}

MusicHelper::~MusicHelper()
{
	SimpleAudioEngine::getInstance()->end();
	m_pUIEffects.clear();
	m_pBackgroundMusic.clear();
}



/************************************************************************/
/* 声音                                                                     */
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
/* 停止音乐 是否释放                                                                     */
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
/* 暂停音乐                                                                     */
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
/* 继续播放音乐                                                                     */
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
/* 播放音乐                                                                     */
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
/* 播放音效                                                                     */
/************************************************************************/
int MusicHelper::playEffect( const char* pszFilePath, bool loop)
{
	if(this->GetSoundIsOpen())
	{
		return SimpleAudioEngine::getInstance()->playEffect(pszFilePath, loop);
	}
	return 0;
}
// 停止单个音效音效
void MusicHelper::stopAppointSingleEffect(unsigned int iEffectId)
{
	SimpleAudioEngine::getInstance()->stopEffect(iEffectId);
}
// 暂停单个音效
void MusicHelper::pauseEffect(unsigned int iEffectId)
{
	if(this->GetSoundIsOpen())
	{
		SimpleAudioEngine::getInstance()->pauseEffect(iEffectId);
	}
}
//恢复单个音效
void MusicHelper::resumeEffect(unsigned int iEffectId)
{
	if(!this->GetSoundIsOpen())
	{
		SimpleAudioEngine::getInstance()->resumeEffect(iEffectId);
	}
}
//恢复音效
void MusicHelper::ResumeAllEffect()
{
	if(!this->GetSoundIsOpen())
	{
		this->SetSoundIsOpen(true);
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}
// 暂停音效
void MusicHelper::PauseAllEffect()
{
	if(this->GetSoundIsOpen())
	{
	this->SetSoundIsOpen(false);
	SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
}
//开启音乐开关
void MusicHelper::openMusic(const char* pszFilePath)
{

	//m_bMusicOpen = true;
	this->playMusic(pszFilePath,true);	
}
// 关闭音乐开关
void MusicHelper::closeMusic(bool bRemove)
{
	//if(m_bMusicOpen)
	{
		//m_bMusicOpen = false;
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(bRemove);
	}	
}
// 切换场景 切换背景音乐
void MusicHelper::ChangeMusic(const char* pszFilePath,bool bRemove)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(bRemove);
	this->playMusic(pszFilePath,true);	
}