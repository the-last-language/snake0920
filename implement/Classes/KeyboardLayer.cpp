#include "KeyboardLayer.h"
/* 전반적인 수정이 필요한 코드. 
	한글 입력을 위한 작업이 수반된다. */

void CKeypadLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//이런 식으로 키 값에 따라 처리를 하면 된다
	int nIndex = 0;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		nIndex = 0;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		nIndex = 1;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		nIndex = 2;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		nIndex = 3;
		break;
	}
}

void CKeypadLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}