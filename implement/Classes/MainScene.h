#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include <iostream>
#include "cocos2d.h"
#include "HangulSnakeHead.h"
#include "KeyboardLayer.h"

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
    virtual bool init();     
    CREATE_FUNC(MainScene);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


private:
// user-defined attributes

	Menu* menu;
	MenuItemImage *pause;
	MenuItemImage *replay;

	Sprite *BG;
	Sprite *hangul_jamo;
	Sprite *hangul_food;

	Size visiblesize;

    Vector<Snake*> body;
	HangulSnakeHead *head;
	bool movedflag;

	bool isGameover;
	bool ifgameover;

};

#endif // __MAIN_SCENE_H__
