#pragma once
#ifndef  __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

class GameOverScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOverScene);
};
#endif // ! __GAME_OVER_SCENE_H__



