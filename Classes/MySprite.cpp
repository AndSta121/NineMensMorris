#include "MySprite.h"

MySprite* MySprite::create(const std::string& filename)
{
    MySprite* mySprite = new(std::nothrow) MySprite();
    if (mySprite && mySprite->initWithFile(filename))
    {
        mySprite->autorelease();
        return mySprite;
    }
    CC_SAFE_DELETE(mySprite);
    return nullptr;
}
