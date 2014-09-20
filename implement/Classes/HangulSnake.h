#ifndef __HANGUL_SNAKE__
#define __HANGUL_SNAKE__

/*
	한글 스네이크에 대해 선언하는 코드.
	다음 요소들이 선언되어 있다.
	-한글 스네이크의 getter, setter
	-그 외 cocos2d-x에 대한 init
*/

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Snake : public Node {
// 왜 node를 상속받나?
    
private:
    Sprite* snakenode;
public:
    void setNode(Sprite* node);
    Sprite* getNode ();
    CREATE_FUNC(Snake);
    virtual bool init();

};


#endif /* defined(__Snake__Snake__) */
