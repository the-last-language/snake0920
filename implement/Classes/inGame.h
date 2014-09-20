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
	void SetApperance();				// �޴� ����, �����¿� ����
	void PauseGame();					// ��������
	void StartGame();					// ���� ���� �� �簳

	/* ���� �ʻ� ��ġ */
	void update();						// ���� �ൿ�� ������.
	void SetSnake();					// �� ��ġ ����
	void SetSnakeVisible(bool value);	// �� ���̰� ��

	/* ���̸Դ� �ѱ��� �ʻ� ��ġ */
	void SetFood();						// �ʿ� �ѱ��� ��ġ(�̼���)
	Point RandomPosition();				// �ѱ� ��ġ�� ���� ��������

	/* ���� �����Ӱ� ����*/
	void SetDirection(Ref* psender, Direction direc);	
										// ���� ���� ����
	void MoveStep();					// ���� ������
	void MoveBody();					// �� ��ü�� ������
	bool ifGetFood();					// ���̸� �Ծ��°�? (�̼���)
	void AddBody();						// ���� ���̸� �ϳ� �����.

	/* ���ӿ��� ���� */
	bool OutofRange();					// ���� ������ ����ٸ�?
	bool HeadCollideBody(Direction headdirec);			
										// �Ӹ��� ���� �浹?
	bool ifCollideBody(Point pos);		// ���� ��ġ �� ���� ���� ��ġ�� �浹�� ���� �÷��� ����.


private:
// user-defined attributes

/* inGame.cpp���� ���̴� �޴� ������ �̹������� ������ 
	�����¿�, ����, ����۹�ư�� ���� �������̴�. */
	MenuItemImage* butup;
    MenuItemImage* butdown;
    MenuItemImage* butleft;
    MenuItemImage* butright;
	MenuItemImage *pause;
	MenuItemImage *replay;

/* ���ȭ��, �ѱ��ڸ�, �ѱ� ��������Ʈ�� */
	Sprite *BG;
	Sprite *hangul_jamo;
	Sprite *hangul_food;

/* visible size�� gameover��Ʈ ���� ���� ����. */
	Size visiblesize; // ȭ�鿡 ������� �̹��� ���ݰ� ����.
	Label* gameover; // ���ӿ����� ����.

/* ���� ����(���ͷ� �Ǿ��ִ�.), ���� �Ӹ�, ������, ������ ���� ��ġ */
	Vector<Snake*> body;
	HangulSnakeHead *head;
	Point lastbodyposi;
	bool movedflag;

	bool isGameover; // ���ӿ��� �÷���

};

#endif __IN_GAME_H__