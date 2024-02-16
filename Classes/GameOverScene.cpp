#include "GameOverScene.h"

USING_NS_CC;
using namespace std;

cocos2d::Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    Point origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("res/GameOver.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, -1);

    float rX = visibleSize.width / background->getContentSize().width;
    float rY = visibleSize.height / background->getContentSize().height;
    background->setScaleX(rX);
    background->setScaleY(rY);

	auto NewGameButton = cocos2d::ui::Button::create("res/NewGame.png");
	//NewGameButton->setScale(0.2);
	NewGameButton->setPosition(Point(NewGameButton->getSize().width / 2, NewGameButton->getSize().height / 2));

	this->addChild(NewGameButton);
	NewGameButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{

		case ui::Widget::TouchEventType::ENDED:
			Scene* scene = GameScene::createScene();
			TransitionFade* transition = TransitionFade::create(3, scene);
			Director::getInstance()->replaceScene(transition);
		}
		});

    return true;
}
