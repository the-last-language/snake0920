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

	/* ���� ���� */    
	void SetApperance();				// �޴� ����
	void PauseGame();					// ��������
	void StartGame();					// ���� ����

	/* ���� �ʻ� ��ġ */
	void SetSnake();					// �� ��ġ ����
	void SetSnakeVisible(bool value);	// �� ���̰� ��

	/* ���̸Դ� �ѱ��� �ʻ� ��ġ */
	void SetFood();						// �ʿ� �ѱ��� ��ġ(�̼���)
	Point RandomPosition();				// �ѱ� ��ġ�� ���� ��������

	/* ���� �����Ӱ� ����*/
	void SetDirection(Ref* psender, Direction direc);	// ���� ���� ����
	void MoveStep();					// ���� ������
	void MoveBody();					// �� ��ü�� ������
	bool ifGetFood();					// ���̸� �Ծ��°�? (�̼���)

	/* ���ӿ��� ���� */
	bool OutofRange();					// ���� ������ ����ٸ�?
	bool HeadCollideBody(Direction headdirec);			// �Ӹ��� ���� �浹?
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