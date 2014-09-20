#include "KeyboardLayer.h"
/* �������� ������ �ʿ��� �ڵ�. 
	�ѱ� �Է��� ���� �۾��� ���ݵȴ�. */

void CKeypadLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//�̷� ������ Ű ���� ���� ó���� �ϸ� �ȴ�
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