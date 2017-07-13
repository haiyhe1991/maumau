#ifndef __MUSICHELPER_H__
#define __MUSICHELPER_H__

#include "mau.h"

#define FIGHT_BACKGROUND_MUSIC "Music/MusicGamedesk.OGG"		

#define MENU_BACKGROUND_MUSIC "Music/MusicLoginScreen.OGG"

//UI背景
#define DISTRBUTE_CARD_SOUND "Sound/SoundDeal.OGG"			
#define SHUFFLE_CARD_SOUND "Sound/SoundShuffle.OGG"				
class MusicHelper
{

public:
	static MusicHelper* GetInstance();
	static void RecoverInstance();
	~MusicHelper();
	//声音资源
	//音效文件
	void loadEffect();
	void unLoadEffect();
	int  playEffect(const char* cha, bool loop);
	void stopAppointSingleEffect(unsigned int iEffectId);
	void pauseEffect(unsigned int iEffectId);
	void resumeEffect(unsigned int iEffectId);
	void ResumeAllEffect();
	void PauseAllEffect();
	//音乐文件
	void loadMusic();
	void unLoadMusic();
	void playMusic(const char* pszFilePath, bool loop);
	void stopMusic(bool shifang);
	void pauseMusic();
	void resumeMusic();
	void openMusic(const char* pszFilePath);
	void closeMusic(bool bRemove);
	void ChangeMusic(const char* pszFilePath,bool bRemove);
	void SetSoundIsOpen(bool bEffectOpen);
	bool GetSoundIsOpen();
	void SetMusicIsOpen(bool bMusicOpen);
	bool GetMusicIsOpen();
private:
	MusicHelper();
	bool m_bEffectOpen;
	bool m_bMusicOpen;
	std::vector<const char*> m_pUIEffects;
	std::vector<const char*> m_pBackgroundMusic;
	static MusicHelper* m_pSingleInstance;
};

#endif
