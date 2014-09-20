#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();    
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// (제외됨.) 키보드 입력 모임
	
	// 배경
	BG = Sprite::create("BG.png");
	BG->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(BG);

	// 메뉴 모임
    pause = MenuItemImage::create("pauseButton.png", "pauseButton.png", 
        CC_CALLBACK_0(MainScene::PauseGame, this));
    pause->setPosition(Point(65, 75));
	
    replay = MenuItemImage::create("rePlayButton1.png","rePlayButton2.png",
        CC_CALLBACK_0(MainScene::StartGame, this));
    replay->setVisible(false);

	menu = Menu::create(pause, replay, NULL);
	menu->setPosition(Point(65, 115));
	menu->alignItemsVertically();
	this->addChild(menu);

    return true;
}
