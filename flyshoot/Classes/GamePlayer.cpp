#include "GamePlayer.h"
#include "cocos2d.h"
using namespace cocos2d;
GamePlayer::GamePlayer(void)
{
	
}

GamePlayer::~GamePlayer(void)
{
}
GamePlayer::GamePlayer(char * s)
{
	mysprite = CCSprite::spriteWithFile(s);
	//mystreak =  CCMotionStreak::streakWithFade(1, 10, s,50, 50, ccc4(255,0,0,255) );
	pAngle = 0;
	isFrozen = false;
	type = 1;
	life = LIFENUM ;
	v = 2;
}
void GamePlayer::tick()
{
}
void GamePlayer::setType(int _type)
{ 
	type = _type;
	switch(type)
	{
		case 0 : mysprite->initWithFile("rplayer.png");break;
		case 1 : mysprite->initWithFile("gplayer.png");break;
	}
}
void GamePlayer::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
	//mystreak->setPosition(mypoint);
}
CCMotionStreak *GamePlayer::getstreak()
{
	return mystreak;
}
bool GamePlayer::iscollision(GameSprite *testsprite)
{
	CCSize ownsize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = (testsprite->getsprite())->getPosition();
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 && abs(ownp.y - otherp.y) <= ownsize.height/2 + othersize.height/2){
		return true;
	}
	return false;
}
bool GamePlayer::collision()
{
	return false;
}
CCSize GamePlayer::getMySize()
{
	return mysprite->getContentSize();
}

void GamePlayer::freeze()
{
	mysprite->initWithFile("stop.png");
	this->getsprite()->stopAllActions();
	isFrozen = true;
}

void GamePlayer::revert()
{
	isFrozen = false;
	setType(type);
}