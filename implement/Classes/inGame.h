#ifndef __IN_GAME_H__
#define __IN_GAME_H__

#include <iostream>
#include "cocos2d.h"
#include "HangulSnakeHead.h"

USING_NS_CC;

class inGame : public Layer {

public:
	inGame();
	~inGame();
	static Scene* createScene();
	virtual void update(float dt);
	virtual bool init();
	CREATE_FUNC(inGame);
	
// user-defined methods

	/* 게임 시작 */    
	void SetApperance();				// 메뉴 동작
	void PauseGame();					// 게임중지
	void StartGame();					// 게임 시작

	/* 뱀을 맵상에 배치 */
	void SetSnake();					// 뱀 배치 시작
	void SetSnakeVisible(bool value);	// 뱀 보이게 함

	/* 뱀이먹는 한글을 맵상에 배치 */
	void SetFood();						// 맵에 한글을 배치(미수정)
	Point RandomPosition();				// 한글 배치를 위한 임의추출

	/* 뱀의 움직임과 관련*/
	void SetDirection(Ref* psender, Direction direc);	// 뱀의 방향 선정
	void MoveStep();					// 뱀이 움직임
	void MoveBody();					// 뱀 전체의 움직임
	bool ifGetFood();					// 먹이를 먹었는가? (미수정)

	/* 게임오버 조건 */
	bool OutofRange();					// 뱀이 범위를 벗어났다면?
	bool HeadCollideBody(Direction headdirec);			// 머리가 몸과 충돌?
	bool ifCollideBody(Point pos);		// 


private:
// user-defined attributes

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

#endif __IN_GAME_H__