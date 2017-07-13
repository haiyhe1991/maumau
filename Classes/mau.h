#ifndef __MAU_H__
#define __MAU_H__

//一般性的头文件，用于引用一些常规引用的头文件

using namespace std;

//cocos2d
#include "cocos2d.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"

USING_NS_CC;

//cocosstudio
#include "editor-support/cocostudio/CCSGUIReader.h"
//ui
#include "ui/UILoadingBar.h"
#include "ui/UIButton.h"
#include "ui/UITextBMFont.h"
#include "ui/UIImageView.h"
#include "ui/UIWidget.h"

using namespace cocos2d::ui;
using namespace cocostudio;

#include <string>
#include <vector>
#include <list>
#include <map>

//custom
#include "tools/TickManager.h"
#include "tools/TimeTools.h"
#include "tools/StringTools.h"

#include "msg/message.h"

#define MAU_PLAYER_NUMBER			4
#define POKER_COLOR_NUMBER			4
#define POKER_POINT_COLOR			13
#define TOTAL_POKER_NUMBER			104	
#define FIRST_HAND_NUMBER			5

#endif

