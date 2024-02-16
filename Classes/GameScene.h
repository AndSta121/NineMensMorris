#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Board.h"
#include "MySprite.h"
#include "GameOverScene.h"

USING_NS_CC;

enum CurrentState {placingPieceOrChoosingPieceToMove, removingOpponentPiece, movingChosenPiece};

class GameScene :public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);

    bool CreateTokens();

    Sprite* tokens[24];
    MySprite* black[9];
    MySprite* white[9];

    Board* board;

    CurrentState currentState;

    int player;
    int movesCount;
    int selectedPieceIndex;
    int whiteCnt;
    int blackCnt;

    EventListenerTouchOneByOne* listener;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    void SwitchToGameOverScene(float delta);
};

#endif // __GAME_SCENE_H__