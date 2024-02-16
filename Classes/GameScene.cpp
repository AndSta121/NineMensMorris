#include "GameScene.h"

USING_NS_CC;
using namespace std;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

bool GameScene::init()
{
    {
        if (!Layer::init())
        {
            return false;
        }

        Size visibleSize = Director::getInstance()->getVisibleSize();
		Director::getInstance()->setClearColor(Color4F::GRAY);
		Point origin = Director::getInstance()->getVisibleOrigin();

		//Add board and position it
        auto boardSprite = Sprite::create("res/Board.png");
        boardSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(boardSprite, -1);

        float scale = (visibleSize.height) / boardSprite->getContentSize().height;
        boardSprite->setScaleX(scale);
        boardSprite->setScaleY(scale);

		//Create Player1 Sprite and position it
		auto player1Sprite = Sprite::create("res/Player1.png");
		player1Sprite->setPosition(Point(visibleSize.width / 8.3 + origin.x, visibleSize.height / 1.1 + origin.y));
		this->addChild(player1Sprite, -1);
		player1Sprite->setScale(0.3);

		//Create Player2 Sprite and position it
		auto player2Sprite = Sprite::create("res/Player2.png");
		player2Sprite->setPosition(Point(visibleSize.width / 1.13 + origin.x, visibleSize.height / 1.1 + origin.y));
		this->addChild(player2Sprite, -1);
		player2Sprite->setScale(0.3);

		//Create tokens
		if (!CreateTokens())
		{
			return false;
		}

		auto NewGameButton = cocos2d::ui::Button::create("res/NewGame.png");
		//NewGameButton->setScale(0.2);
		NewGameButton->setPosition(Point(NewGameButton->getSize().width/2, NewGameButton->getSize().height/2));

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


		//Create black pieces and position them below Player1 sign
		for (int i = 0; i < 9; i++){
			black[i] = MySprite::create("res/Black.png");
			black[i]->indexOnBoard = -1;
			black[i]->setScale(0.85);
			black[i]->setPosition(Point(player1Sprite->getPosition().x, player1Sprite->getPosition().y - 100 - i * black[i]->getContentSize().height*0.85));
			this->addChild(black[i], -1);
		}

		//Create white pieces and position them below Player2 sign
		for (int i = 0; i < 9; i++) {
			white[i] = MySprite::create("res/White.png");
			white[i]->indexOnBoard = -1;
			white[i]->setScale(0.85);
			white[i]->setPosition(Point(player2Sprite->getPosition().x, player2Sprite->getPosition().y - 100 - i * white[i]->getContentSize().height * 0.85));
			this-> addChild(white[i], -1);
		}
		
		board = new Board();
		player = 1;
		movesCount = 0;
		whiteCnt = 9;
		blackCnt = 9;
		currentState = placingPieceOrChoosingPieceToMove;

		listener = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

        return true;
    }
}

bool GameScene::CreateTokens()
{
	//Creating tokens and positionig them on board
	for (int i = 0; i < 24; i++)
	{
		tokens[i] = Sprite::create("res/Token.png");
		if (!tokens[i])
			return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//line1
	tokens[0]->setPosition(Point(visibleSize.width / 4.1 + origin.x, visibleSize.height / 20 + origin.y));
	this->addChild(tokens[0], -1);

	tokens[1]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 20 + origin.y));
	this->addChild(tokens[1], -1);

	tokens[2]->setPosition(Point(visibleSize.width / 1.325 + origin.x, visibleSize.height / 20 + origin.y));
	this->addChild(tokens[2], -1);

	//line2
	tokens[3]->setPosition(Point(visibleSize.width / 3.05 + origin.x, visibleSize.height / 5 + origin.y));
	this->addChild(tokens[3], -1);

	tokens[4]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 5 + origin.y));
	this->addChild(tokens[4], -1);

	tokens[5]->setPosition(Point(visibleSize.width / 1.49 + origin.x, visibleSize.height / 5 + origin.y));
	this->addChild(tokens[5], -1);

	//line3
	tokens[6]->setPosition(Point(visibleSize.width / 2.4 + origin.x, visibleSize.height / 2.85 + origin.y));
	this->addChild(tokens[6], -1);

	tokens[7]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2.85 + origin.y));
	this->addChild(tokens[7], -1);

	tokens[8]->setPosition(Point(visibleSize.width / 1.7 + origin.x, visibleSize.height / 2.85 + origin.y));
	this->addChild(tokens[8], -1);


	//line 4
	tokens[9]->setPosition(Point(visibleSize.width / 4.1 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tokens[9], -1);

	tokens[10]->setPosition(Point(visibleSize.width / 3.05 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tokens[10], -1);

	tokens[11]->setPosition(Point(visibleSize.width / 2.4 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tokens[11], -1);

	tokens[12]->setPosition(Point(visibleSize.width / 1.7 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tokens[12], -1);

	tokens[13]->setPosition(Point(visibleSize.width / 1.49 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tokens[13], -1);

	tokens[14]->setPosition(Point(visibleSize.width / 1.325 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tokens[14], -1);

	//line5
	tokens[15]->setPosition(Point(visibleSize.width / 2.4 + origin.x, visibleSize.height / 1.54 + origin.y));
	this->addChild(tokens[15], -1);

	tokens[16]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.54 + origin.y));
	this->addChild(tokens[16], -1);

	tokens[17]->setPosition(Point(visibleSize.width / 1.7 + origin.x, visibleSize.height / 1.54 + origin.y));
	this->addChild(tokens[17], -1);

	//line6
	tokens[18]->setPosition(Point(visibleSize.width / 3.05 + origin.x, visibleSize.height / 1.255 + origin.y));
	this->addChild(tokens[18], -1);

	tokens[19]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.255 + origin.y));
	this->addChild(tokens[19], -1);

	tokens[20]->setPosition(Point(visibleSize.width / 1.49 + origin.x, visibleSize.height / 1.255 + origin.y));
	this->addChild(tokens[20], -1);

	//line 7
	tokens[21]->setPosition(Point(visibleSize.width / 4.1 + origin.x, visibleSize.height / 1.05 + origin.y));
	this->addChild(tokens[21], -1);

	tokens[22]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 1.05 + origin.y));
	this->addChild(tokens[22], -1);

	tokens[23]->setPosition(Point(visibleSize.width / 1.325 + origin.x, visibleSize.height / 1.05 + origin.y));
	this->addChild(tokens[23], -1);
	
	return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Point touchPoint = touch->getLocation();
	auto director = Director::getInstance();
	
	switch (currentState) {
		case placingPieceOrChoosingPieceToMove: 
			if (movesCount < 18) {
				for (int i = 0; i < 24; i++)
				{
					if (tokens[i]->getBoundingBox().containsPoint(touchPoint) && board->state[i] == 0) {
						auto moveTo = MoveTo::create(0.5, Vec2(tokens[i]->getPosition()));
						if (player == 1)
						{
							black[(movesCount) / 2]->runAction(moveTo);
							black[(movesCount) / 2]->indexOnBoard = i;
							movesCount++;
							if (board->UpdateBoardStateAndCheckForMoulinFormation(i, player)) {
								log("Moulin\n");
								currentState = removingOpponentPiece;
								return;
							}
							player *= -1;
							if (movesCount == 18 && !board->CheckIfPlayerCanMoveAnyOfHisPieces(player))
							{
								scheduleOnce(schedule_selector(GameScene::SwitchToGameOverScene), 1);
								return;
							}
							return;
						}
						else if (player == -1)
						{
							white[(movesCount) / 2]->runAction(moveTo);
							white[(movesCount) / 2]->indexOnBoard = i;
							movesCount++;
							if (board->UpdateBoardStateAndCheckForMoulinFormation(i, player)) {
								log("Moulin\n");
								currentState = removingOpponentPiece;
								return;
							}
							player *= -1;
							if (movesCount == 18 && !board->CheckIfPlayerCanMoveAnyOfHisPieces(player))
							{
								scheduleOnce(schedule_selector(GameScene::SwitchToGameOverScene), 1);
								return;
							}
							return;
						}	
					}
				}	
			}
			else {
				for (int i = 0; i < 9; i++) {
					if (player == 1 && black[i]->getBoundingBox().containsPoint(touchPoint) && board->CheckIfPlayerCanMoveSelectedPiece(black[i]->indexOnBoard)){
						black[i]->setScale(1.05);
						currentState = movingChosenPiece;
						selectedPieceIndex = i;
						return;
					}
					else if (player == -1 && white[i]->getBoundingBox().containsPoint(touchPoint) && board->CheckIfPlayerCanMoveSelectedPiece(white[i]->indexOnBoard)) {
						white[i]->setScale(1.05);
						currentState = movingChosenPiece;
						selectedPieceIndex = i;
						return;
					}
				}
			}
			break;
		case removingOpponentPiece: 
			for (int i = 0; i < 9; i++) {
				auto moveTo = MoveTo::create(0.5, Vec2(2000, 2000));
				if (player == 1 && white[i]->getBoundingBox().containsPoint(touchPoint)) {
					if (board->CheckIfPieceIsRemoveable(white[i]->indexOnBoard, -player) && white[i]->indexOnBoard>=0) {
						white[i]->runAction(moveTo);
						board->state[white[i]->indexOnBoard] = 0;
						player *= -1;
						currentState = placingPieceOrChoosingPieceToMove;
						whiteCnt--;
					}
				}
				else if (player == -1 && black[i]->getBoundingBox().containsPoint(touchPoint)) {
					if (board->CheckIfPieceIsRemoveable(black[i]->indexOnBoard, -player) && black[i]->indexOnBoard>=0) {
						black[i]->runAction(moveTo);
						board->state[black[i]->indexOnBoard] = 0;
						player *= -1;
						currentState = placingPieceOrChoosingPieceToMove;
						blackCnt--;
					}
				}
			}
			if (whiteCnt < 3 || blackCnt < 3 || !board->CheckIfPlayerCanMoveAnyOfHisPieces(player))
			{
				scheduleOnce(schedule_selector(GameScene::SwitchToGameOverScene), 1);
				return;
			}
			break;
	
		case movingChosenPiece: 
			for (int i = 0; i < 24; i++) {
				if (player == 1) {
					if(tokens[i]->getBoundingBox().containsPoint(touchPoint) && board->CheckForValidMove(i, black[selectedPieceIndex]->indexOnBoard))
					{
						auto moveTo = MoveTo::create(0.5, tokens[i]->getPosition());
						black[selectedPieceIndex]->runAction(moveTo);
						
						board->state[black[selectedPieceIndex]->indexOnBoard] = 0;

						black[selectedPieceIndex]->setScale(0.85);
						black[selectedPieceIndex]->indexOnBoard = i;
						if (board->UpdateBoardStateAndCheckForMoulinFormation(i, player)) {
							currentState = removingOpponentPiece;
							return;
						}
						player *= -1;
						currentState = placingPieceOrChoosingPieceToMove;
						break;
					}	
				}
				else {
					if (tokens[i]->getBoundingBox().containsPoint(touchPoint) && board->CheckForValidMove(i, white[selectedPieceIndex]->indexOnBoard))
					{
						auto moveTo = MoveTo::create(0.5, tokens[i]->getPosition());
						white[selectedPieceIndex]->runAction(moveTo);
						
						board->state[white[selectedPieceIndex]->indexOnBoard] = 0;

						white[selectedPieceIndex]->setScale(0.85);
						white[selectedPieceIndex]->indexOnBoard = i;
						if (board->UpdateBoardStateAndCheckForMoulinFormation(i, player)) {
							currentState = removingOpponentPiece;
							return;
						}
						player *= -1;
						currentState = placingPieceOrChoosingPieceToMove;
						break;
					}
				}
			}
			if (!board->CheckIfPlayerCanMoveAnyOfHisPieces(player))
			{
				scheduleOnce(schedule_selector(GameScene::SwitchToGameOverScene), 1);
				return;
			}
			return;
		break;	
	}
	return;
}

void GameScene::SwitchToGameOverScene(float delta)
{
	Scene* scene = GameOverScene::createScene();
	TransitionFade* transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

