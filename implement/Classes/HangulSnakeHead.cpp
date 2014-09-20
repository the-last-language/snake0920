#include "HangulSnakeHead.h"

/* 
	한글 스네이크의 머리를 정의하는 코드.
*/

bool HangulSnakeHead::init() {
    return true;
}

HangulSnakeHead::HangulSnakeHead() {
    this->direction = down;
}

HangulSnakeHead::~HangulSnakeHead() {
    
}

/*
	방향을 설정한다.
	Direction 타입은 HangulSnakeHead.h에 있다.
	up/down/left/right 순으로 정의되어 있다.
*/
Direction HangulSnakeHead::getDirec() {
    return this->direction;
}

void HangulSnakeHead::setDirec(Direction dir) {
    this->direction = dir;
}