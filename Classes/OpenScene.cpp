#include "OpenScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;

Scene* OpenScene::createScene()
{
	auto scene = Scene::create();

	auto layer = OpenScene::create();

	scene->addChild(layer);

	return scene;
}

bool OpenScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    Point origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("res/Splash.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, -1);

    scheduleOnce(schedule_selector(OpenScene::SwitchToGameScene), 1);
    return true;
}

void OpenScene::SwitchToGameScene(float delta)
{
    Scene* scene = GameScene::createScene();
    TransitionFade* transition = TransitionFade::create(3, scene);
    Director::getInstance()->replaceScene(transition);
}
