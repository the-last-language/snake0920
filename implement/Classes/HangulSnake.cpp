#include "HangulSnake.h"

/*
	한글 스네이크의 getter, setter와
	init가 구현되어있다.
*/

Sprite* Snake::getNode() {
    return this->snakenode;
}

void Snake::setNode(Sprite* node){
    this->snakenode = node;
    this->addChild(snakenode);
}

bool Snake::init(){
    return true;
}
