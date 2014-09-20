#ifndef __KEYBOARD_LAYER_H__
#define __KEYBOARD_LAYER_H__

// 수정 필요.

#include "cocos2d.h"
#include <iostream>

class CKeypadLayer {
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event *event){

public:
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

};
#endif /* end of __KEYBOARD_LAYER_H__ */