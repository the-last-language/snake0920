#include "inGame.h"
#include <cstdlib>
#include <ctime>

inGame::inGame()
{
	srand(time(NULL));
}

inGame::~inGame()
{

}

Scene* inGame::createScene()
{
	auto scene = Scene::create();
	auto layer = inGame::create();

	scene->addChild(layer);

	return scene;
}

bool inGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	do {
		ifgameover = false;
		SetSnake();
		SetFood();
		this->schedule(schedule_selector(inGame::update), 0.6);
	} while (0);

}

void inGame::SetSnake() {
	body.clear();

	Size visiblesize = Director::getInstance()->getVisibleSize();
	head = HangulSnakeHead::create();

	head->setNode(Sprite::create("SnakeHead.png"));
	head->setPosition(Point(visiblesize.width / 2 - head->getNode()->getContentSize().width / 2, visiblesize.height / 2 - head->getNode()->getContentSize().height / 2));
	this->addChild(head, 1);

	for (int i = 1; i < 4; i++) {
		Snake* bodynode = Snake::create();
		bodynode->setNode(Sprite::create("Snake.png"));
		bodynode->setPosition(Point(head->getPosition().x + i*bodynode->getNode()->getContentSize().width, head->getPosition().y));
		body.pushBack(bodynode);
		this->addChild(bodynode);
	}
}

void inGame::SetFood() {
	this->removeChild(hangul_food);
	Point foodposi = RandomPosition();
	Point headposi = head->getPosition();
	while (foodposi == headposi || ifCollideBody(foodposi)) {
		foodposi = RandomPosition();
	}
	hangul_food = Sprite::create("Food.png");
	hangul_food->setPosition(foodposi);
	this->addChild(hangul_food);
}

Point inGame::RandomPosition(){
	int x = (rand() % 24);
	int y = (rand() % 16);
	Point position = Point(x * 20 + 10, y * 20 + 10);
	return position;
}



void inGame::PauseGame() {
//	this->pause();
	SetSnakeVisible(false);
	replay->setVisible(true);
}

void inGame::StartGame() {
	if (!isGameover) {
		SetSnakeVisible(true);
		this->resume();
		replay->setVisible(false);
	}
	else {
		this->unscheduleAllSelectors();
		this->removeAllChildren();
		//body.clear();
		this->init();
	}
}

void inGame::SetSnakeVisible(bool val) {
	hangul_food->setVisible(val);
	head->getNode()->setVisible(val);
	for (int i = 0; i<body.size(); i++) {
		body.at(i)->setVisible(val);
	}
}

void inGame::SetDirection(Ref* psender, Direction direc){
	Direction headdir = head->getDirec();
	if (movedflag && direc != headdir) {
		switch (direc) {
		case up:
			if (headdir == left || headdir == right){
				head->setDirec(up);
			}
			break;
		case down:
			if (headdir == left || headdir == right){
				head->setDirec(down);
			}
			break;
		case left:
			if (headdir == up || headdir == down){
				head->setDirec(left);
			}
			break;
		case right:
			if (headdir == up || headdir == down){
				head->setDirec(right);
			}
			break;
		default:
			break;
		}
		movedflag = false;
	}
	else{

	}


}

void inGame::MoveStep(){
	movedflag = true;
	Direction temp = head->getDirec();
	Point po = head->Node::getPosition();
	switch (temp) {
	case up:
		//log("upupup");
		po.y += 35;
		break;
	case down:
		po.y -= 35;
		break;
	case left:
		po.x -= 35;
		break;
	case right:
		po.x += 35;
		break;

	default:
		break;
	}
	MoveBody();
	head->setPosition(po);

}

void inGame::MoveBody() {
	int n = body.size();
	Point HeadPosition = head->getPosition();
	Point a, temp;
	for (int i = 0; i < n; i++) {
		if (i == 0){
			a = body.at(i)->getPosition();
			body.at(i)->setPosition(HeadPosition);
		}
		else {
			temp = a;
			a = body.at(i)->getPosition();
			body.at(i)->setPosition(temp);
		}
	}

}

bool inGame::OutofRange() {
	Point po = head->getPosition();
	if (po.x < 0 || po.x > visiblesize.width || po.y < 0 || po.y > visiblesize.height) {
		return true;
	}
	return  false;
}


bool inGame::HeadCollideBody(Direction headdirec){
	float x = head->getPosition().x;
	float y = head->getPosition().y;
	bool iscollide = false;
	switch (headdirec) {
	case up:
		y += 20;
		break;
	case down:
		y -= 20;
		break;
	case left:
		x -= 20;
		break;
	case right:
		x += 20;
		break;
	default:
		break;
	}
	Point headnextpos = Point(x, y);
	iscollide = ifCollideBody(headnextpos);
	return  iscollide;
}

bool inGame::ifCollideBody(Point pos)
{
	bool value = false;
	Snake* node;
	for (int i = 0; i<body.size(); i++) {
		node = body.at(i);
		Point nodepos = node->getPosition();
		if (nodepos == pos){
			value = true;
		}
	}
	return value;
}

bool inGame::ifGetFood(){
    bool value = false;
    if(food->getPosition() == head->getPosition()){
        value = true;
    }
    return value;
}