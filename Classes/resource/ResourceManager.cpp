#include "ResourceManager.h"
#include "layer/load.h"

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ResourceManager;
	}
	return _instance;
}

void ResourceManager::DestoryInstance()
{
	if (_instance != nullptr)
	{
		delete _instance;
	}
	_instance = nullptr;
}

ResourceManager::~ResourceManager()
{
	SpriteFrameCache::getInstance()->removeSpriteFrames();
	clear_all();
}

void ResourceManager::Sync_load_plist(const char* path)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path);
}

void ResourceManager::Sync_unload_plist(const char* path)
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(path);
}

void ResourceManager::Sync_load_animation(const char* imagePath,const char* plistPath,const char*ExportJsonPath)
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo(imagePath, plistPath, ExportJsonPath);
}

void ResourceManager::Sync_unload_animation(const char* ExportJsonPath)
{
	ArmatureDataManager::getInstance()->removeArmatureFileInfo(ExportJsonPath);
}

SpriteFrame* ResourceManager::Get_resource_from_plist(const char* name)
{
	return SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
}

void ResourceManager::Sync_load_ui(const char* path)
{
	Widget* item = GUIReader::getInstance()->widgetFromJsonFile(path);
	if (item != nullptr)
	{
		item->retain();
		_uiMaps[path] = item;
	}
}

void ResourceManager::Sync_unload_ui(const char* path)
{
	map<string, Widget*>::iterator iter = _uiMaps.find(path);
	if (iter != _uiMaps.end())
	{
		Widget* item = iter->second;
		item->release();
		_uiMaps.erase(iter);
	}
}

Widget* ResourceManager::Get_ui_resource(const char* path)
{
	map<string, Widget*>::iterator iter = _uiMaps.find(path);
	if (iter != _uiMaps.end())
	{
		Widget* item = iter->second;
		return item->clone();
	}
	return nullptr;
}

void ResourceManager::clear_all()
{
	map<string, Widget*>::iterator iter = _uiMaps.begin();
	while (iter != _uiMaps.end())
	{
		Sync_unload_ui(iter->first.c_str());
		iter = _uiMaps.begin();
	}
}

void ResourceManager::Sync_load(LoadItem item)
{
	if (item.type == LoadType::UI)
	{
		this->Sync_load_ui(item.path);
	}
	else if (item.type == LoadType::PLIST)
	{
		this->Sync_load_plist(item.path);
	}
	else if (item.type == LoadType::ARMATURE)
	{
		this->Sync_load_animation(item.img, item.plist, item.path);
	}
}

void ResourceManager::Release(list<LoadItem> lst)
{
	list<LoadItem>::iterator iter = lst.begin();
	while (iter != lst.end())
	{
		LoadItem item = (*iter);
		if (item.type == LoadType::UI)
		{
			this->Sync_unload_ui(item.path);
		}
		else if (item.type == LoadType::PLIST)
		{
			this->Sync_unload_plist(item.path);
		}
		else if (item.type == LoadType::ARMATURE)
		{
			this->Sync_unload_animation(item.path);
		}
		iter++;
	}
}
