#include "inGame.h"
#include <cstdlib>
#include <ctime>


// Point RandomPosition()에 사용된다.
inGame::inGame() { srand(time(NULL)); }

inGame::~inGame() { }

Scene* inGame::createScene() {
	auto scene = Scene::create();
	auto layer = inGame::create();

	scene->addChild(layer);

	return scene;
}

bool inGame::init() {
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
	// while에 0이 들어가는 이유가 불명.
	// 이건 규명 못해서 미안하다아아아아아아!!!
}

/* 
    메뉴 동작과 관련한 요소.
    대다수 필요없는 요소들이나
    상하좌우 버튼, 중지, 재시작 버튼이 있으니 필터링 바람.
*/
void GameLayer::SetApperance() {
    visiblesize = Director::getInstance()->getVisibleSize();
    
    background = Sprite::create("BackGround.png");
    background->setPosition(Point(visiblesize.width/2,visiblesize.height/2));
    this->addChild(background,0);  //this is the background
    
    butup = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,up));
    Size bs = butup->getContentSize();
    butup->setPosition(Point(visiblesize.width-3*bs.width+bs.width/2,3*bs.height+bs.height/2));

    butdown = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,down));
    butdown ->setPosition(Point(visiblesize.width-3*bs.width+bs.width/2,bs.height+bs.height/2));
    
    butleft = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,left));
    butleft ->setPosition(Point(visiblesize.width-4*bs.width+bs.width/2,2*bs.height+bs.height/2));
    
    butright = MenuItemImage::create("Button.png","Button2.png","Button.png",CC_CALLBACK_1(GameLayer::SetDirection,this,right));
    butright ->setPosition(Point(visiblesize.width-2*bs.width+bs.width/2,2*bs.height+bs.height/2));
    
    pausebutton = MenuItemImage::create("PauseButton.png","PauseButton.png",CC_CALLBACK_0(GameLayer::PauseGame,this));
    pausebutton->setPosition(Point(visiblesize.width - pausebutton->getContentSize().width,visiblesize.height - pausebutton->getContentSize().height/2));
    
    playbutton = MenuItemImage::create("rePlayButton1.png","rePlayButton2.png",CC_CALLBACK_0(GameLayer::StartGame, this));
    playbutton->setPosition(Point(visiblesize.width/2,visiblesize.height/2));
    playbutton->setVisible(false);
    
    menu = Menu::create(butup,butdown,butleft,butright,pausebutton,playbutton,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,2);
    
    TTFConfig ttfconfig("Marker Felt.ttf",40);
    gameover = Label::createWithTTF(ttfconfig, " Game Over !",TextHAlignment::CENTER);
    gameover->setPosition(Point(visiblesize.width/2,visiblesize.height/2+gameover->getContentSize().height));
    gameover->setVisible(false);
    gameover->setColor(Color3B::BLACK);
    this->addChild(gameover,2);
}

/* 게임을 일시정지한다. 저 this가 왜 작동을 하지? 이해할 수 없다.*/
// 본인의 작업환경: VS2013, cocos2d-x 3.2ver
void inGame::PauseGame() {
//	this->pause();
	SetSnakeVisible(false);
	replay->setVisible(true);
}

/* 게임을 재개하는 함수이다. */
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

/* 
    움직임 업데이트. 
    다음의 요소를 체크한다.
    - 머리와 충돌했는지?
        no: 움직임, yes: 게임오버
    - 먹이를 먹었는지?
        yes: 몸을 길어지게 하고 먹이를 배치한다.
*/
void inGame::update(float dt) {
    if (!HeadCollideBody(head->getDirec()) && !OutofRange()) {
         MoveStep();
        if(ifGetFood()) {
            AddBody();
            SetFood();
        }
        lastbodyposi = body.at(body.size()-1)->getPosition();
    }
    else{
        GameOver();
    }
}

/* 뱀을 맵상에 배치한다. */
void inGame::SetSnake() {
	body.clear();

	Size visiblesize = Director::getInstance()->getVisibleSize();
	head = HangulSnakeHead::create();
	head->setNode(Sprite::create("SnakeHead.png"));
	head->setPosition(Point(visiblesize.width / 2 - head->getNode()->getContentSize().width / 2, visiblesize.height / 2 - head->getNode()->getContentSize().height / 2));
	// 뱀의 초기위치 설정. 추후 수정 요망.
	this->addChild(head, 1);

/* 처음 꼬리는 3개가 붙는다. 
    나머지는 게임을 거치며 늘어날 것이다. */
	for (int i = 1; i < 4; i++) {
		Snake* bodynode = Snake::create();
		bodynode->setNode(Sprite::create("Snake.png"));
		bodynode->setPosition(Point(head->getPosition().x + i*bodynode->getNode()->getContentSize().width, head->getPosition().y));
		body.pushBack(bodynode);
		this->addChild(bodynode);
	}
}

/* 뱀을 보이게 하는 함수이다. 
    inGame의 뱀의 몸통부분 선언을 참조하라. */
void inGame::SetSnakeVisible(bool val) {
	hangul_food->setVisible(val);
	head->getNode()->setVisible(val);
	for (int i = 0; i<body.size(); i++) {
		body.at(i)->setVisible(val);
	}
}

/* 뱀의 위치를 고려한 먹이 배치. update와 연관이 있다.
    예외처리에 주목하라.*/
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
/* 먹이의 랜덤배치를 위한 소스. */
Point inGame::RandomPosition(){
/*    원래 arc4random()을 사용했는데 안되서 rand로 바꿈. */
	int x = (rand() % 24);
	int y = (rand() % 16);
	Point position = Point(x * 20 + 10, y * 20 + 10);
	return position;
}



/* 뱀의 위치를 설정한다. psender가 있는 것으로 보아 값을 입력받을 것이다.*/
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

/* 뱀을 움직인다. update와 연관있다. */
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

/* 몸통의 움직임을 구현. */
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

/* 먹이를 먹었다면? update와 연관이 있다. */
bool inGame::ifGetFood(){
    bool value = false;
    if(food->getPosition() == head->getPosition()){
        value = true;
    }
    return value;
}

/* 몸을 길어지게 한다. update와 연관이 있다. */
void GameLayer::AddBody(){
    head->setPosition(food->getPosition());
    Snake* node = Snake::create();
    node->setNode(Sprite::create("Snake.png"));
    node->setPosition(lastbodyposi);
    body.pushBack(node);
    this->addChild(node);
}

/* 범위에 벗어났다면? 
    화면 사이즈에 맞게 알아서 수정하면 될 것이다. */
bool inGame::OutofRange() {
	Point po = head->getPosition();
	if (po.x < 0 || po.x > visiblesize.width || po.y < 0 || po.y > visiblesize.height) {
		return true;
	}
	return  false;
}

/* 머리가 몸통에 충돌한다면? */
bool inGame::HeadCollideBody(Direction headdirec){
	float x = head->getPosition().x;
	float y = head->getPosition().y;

/* 로직의 적절한 수정으로 게임오버 판정을 
    늦추거나 다르게 할 수 있을 것이다. */ 
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

/* 먹이 배치 시 기존 몸의 위치와 충돌에 대한 플래그 리턴. 
    SetFood와 연관이 있다.*/
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
