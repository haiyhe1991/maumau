#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

//��Ϸ��Դ������   
#include "mau.h"

struct LoadItem;

class ResourceManager
{
public:
	static ResourceManager*		GetInstance();								//��Դ������  ����ģʽ
	static void					DestoryInstance();							//�ݻٵ���
	~ResourceManager();														//����

	void						Sync_load_plist(const char* path);			//ͬ������plistͼƬ
	void						Sync_unload_plist(const char* path);		//ͬ������plistͼƬ

	void						Sync_load_ui(const char* path);				//ͬ������ui��Դ
	void						Sync_unload_ui(const char* path);			//ж��ui��Դ

	void						Sync_load_animation(const char* imagePath, const char* plistPath, const char*ExportJsonPath);				//ͬ�����ض�����Դ
	void						Sync_unload_animation(const char* ExportJsonPath);			//ж�ض�����Դ

	SpriteFrame*				Get_resource_from_plist(const char* name);	//plist�ļ���ȡ����Դ
	Widget*						Get_ui_resource(const char* path);			//��ȡ�Ѿ����ص�ui��Դ		

	void						Sync_load(LoadItem item);					//����
	void						Release(list<LoadItem> lst);				//�����ڴ�

private:
	static ResourceManager*		_instance;									//����
	
	void						clear_all();								//�������UI��Դ

	map<string, Widget*>		_uiMaps;									//ui��Դ�Ĵ洢����	

};


#endif

