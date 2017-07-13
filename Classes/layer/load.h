#ifndef __LOAD_H__
#define __LOAD_H__

#include "mau.h"

enum LoadType
{
	PLIST,					//ͼƬ��Դ
	UI,						//UI��Դ
	ARMATURE,				//������Դ
};


struct LoadItem
{

	LoadItem::LoadItem(LoadType type, const char* path)
	{
		this->type = type;
		this->path = path;
	};

	LoadItem::LoadItem(const char* path, const char* img, const char* plist)
	{
		this->type = LoadType::ARMATURE;
		this->path = path;
		this->img = img;
		this->plist = plist;
	};

	LoadType			type;			//��������
	const char*			path;			//·��
	
	//���ض�����Դ
	const char*			img;
	const char*			plist;			
};

#endif

