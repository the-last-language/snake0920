#ifndef __HANGULSNAKE_HEAD__
#define __HANGULSNAKE_HEAD__

/*
    한글 스네이크의 머리를 선언하는 코드.
    다음 요소들이 선언되어 있다.
    -Direction에 대한 enumeration
    -머리의 위치에 대한 getter, setter
    -그 외 cocos2d-x에 대한 init
*/

#include <iostream>
#include "cocos2d.h"
#include "HangulSnake.h"

USING_NS_CC;

enum Direction {
    up = 0,
    down = 1,
    left = 2,
    right = 3,
}; // 굳이 써놓을 필요는 없는데 명시해두자.

class HangulSnakeHead : public Snake {
private:
    Direction direction;
public:
    CREATE_FUNC(HangulSnakeHead);
    virtual bool init();
    HangulSnakeHead();
    ~HangulSnakeHead();
    void setDirec(Direction dir);
    Direction getDirec();
    
};

#endif /* defined(__HANGULSNAKE_HEAD__) */
