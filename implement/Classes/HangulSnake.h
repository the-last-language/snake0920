#ifndef __HANGUL_SNAKE__
#define __HANGUL_SNAKE__

/*
	한글 스네이크의 몸통들을 정의하는 코드. 
	한글 스네이크의 getter, setter와
	init가 구현되어있다.
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
