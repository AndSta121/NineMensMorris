#pragma once

#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

class MySprite : public Sprite
{
public:
	int indexOnBoard;
	static MySprite* create(const std::string& filename);
};

#endif // __MYSPRITE_H__