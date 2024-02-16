#pragma once
#ifndef __OPEN_SCENE_H__
#define __OPEN_SCENE_H__

#include "cocos2d.h"
class OpenScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(OpenScene);

private:
	void SwitchToGameScene(float delta);
};

#endif // !__OPEN_SCENE_H__



