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
	void SetApperance();				// 메뉴 동작, 상하좌우 조종
	void PauseGame();					// 게임중지
	void StartGame();					// 게임 시작 및 재개

	/* 뱀을 맵상에 배치 */
	void update();						// 뱀의 행동을 시작함.
	void SetSnake();					// 뱀 배치 시작
	void SetSnakeVisible(bool value);	// 뱀 보이게 함

	/* 뱀이먹는 한글을 맵상에 배치 */
	void SetFood();						// 맵에 한글을 배치(미수정)
	Point RandomPosition();				// 한글 배치를 위한 임의추출

	/* 뱀의 움직임과 관련*/
	void SetDirection(Ref* psender, Direction direc);	
										// 뱀의 방향 선정
	void MoveStep();					// 뱀이 움직임
	void MoveBody();					// 뱀 전체의 움직임
	bool ifGetFood();					// 먹이를 먹었는가? (미수정)
	void AddBody();						// 뱀의 길이를 하나 길게함.

	/* 게임오버 조건 */
	bool OutofRange();					// 뱀이 범위를 벗어났다면?
	bool HeadCollideBody(Direction headdirec);			
										// 머리가 몸과 충돌?
	bool ifCollideBody(Point pos);		// 먹이 배치 시 기존 몸의 위치와 충돌에 대한 플래그 리턴.


private:
// user-defined attributes

/* inGame.cpp에서 쓰이는 메뉴 아이템 이미지들의 포인터 
	상하좌우, 중지, 재시작버튼에 대한 포인터이다. */
	MenuItemImage* butup;
    MenuItemImage* butdown;
    MenuItemImage* butleft;
    MenuItemImage* butright;
	MenuItemImage *pause;
	MenuItemImage *replay;

/* 배경화면, 한글자모, 한글 스프라이트들 */
	Sprite *BG;
	Sprite *hangul_jamo;
	Sprite *hangul_food;

/* visible size와 gameover폰트 관련 변수 선언. */
	Size visiblesize; // 화면에 띄워지는 이미지 전반과 연관.
	Label* gameover; // 게임오버와 연관.

/* 뱀의 몸통(벡터로 되어있다.), 뱀의 머리, 움직임, 마지막 뱀의 위치 */
	Vector<Snake*> body;
	HangulSnakeHead *head;
	Point lastbodyposi;
	bool movedflag;

	bool isGameover; // 게임오버 플래그

};

#endif __IN_GAME_H__