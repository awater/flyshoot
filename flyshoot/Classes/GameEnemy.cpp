#include "GameEnemy.h"
#include <math.h>

GameEnemy::GameEnemy(void)
{
}

GameEnemy::~GameEnemy(void)
{
}
GameEnemy::GameEnemy(char * s)
{
	mysprite = CCSprite::spriteWithFile(s);
	mysprite->setPosition(ccp(rand()%860,450));
    bezier1.controlPoint_1 = CCPointMake(-50,300);
    bezier1.controlPoint_2 = CCPointMake(694,150);
    bezier1.endPosition = CCPointMake(302,-20);
	bezier2.controlPoint_1 = CCPointMake(694,300);
    bezier2.controlPoint_2 = CCPointMake(-50,150);
    bezier2.endPosition = CCPointMake(422,-20);
    chooseflytype();
	state = 0;
	bullettick = 0;
	isFrozen = false;
}
void GameEnemy::setDead()
{
    mysprite->stopAllActions();
	mysprite->setIsVisible(false);
	state = -1;
	bullettick = 0;
}
void GameEnemy::chooseflytype()
{
    type = CCRANDOM_0_1() * 5;
	switch(type){
	case 0:
	   mysprite->initWithFile("gplayer.png");
	   bezierTo1 = CCBezierTo::actionWithDuration(5, bezier1);
	   mysprite->runAction(bezierTo1);
	   break;
    case 1:
	   mysprite->initWithFile("gplayer.png");
	   bezierTo1 = CCBezierTo::actionWithDuration(5, bezier2);
	   mysprite->runAction(bezierTo1);
	   break;
	case 2:
	   mysprite->initWithFile("gplayer.png");
	   actionTo1 = CCMoveTo::actionWithDuration(2, CCPointMake(30,300));
	   actionTo2 = CCMoveTo::actionWithDuration(2, CCPointMake(800,150));
	   actionTo3 = CCMoveTo::actionWithDuration(1, CCPointMake(400,-20));
	   mysprite->runAction(CCSequence::actions(actionTo1,actionTo2,actionTo3,NULL));
	   break;
	case 3:
	   mysprite->initWithFile("gplayer.png");
	   actionTo1 = CCMoveTo::actionWithDuration(2, CCPointMake(800,300));
	   actionTo2 = CCMoveTo::actionWithDuration(2, CCPointMake(30,150));
	   actionTo3 = CCMoveTo::actionWithDuration(1, CCPointMake(400,-20));
	   mysprite->runAction(CCSequence::actions(actionTo1,actionTo2,actionTo3,NULL));
	   break;
	case 4:
	   mysprite->initWithFile("gplayer.png");
	   actionTo1 = CCMoveTo::actionWithDuration(5, CCPointMake(122,-20));
	   mysprite->runAction(actionTo1);
	   break;
	}
	mysprite->setRotation(90);
}
void GameEnemy::restart()
{
    mysprite->setPosition(ccp(rand()%300,450));
	mysprite->setIsVisible(true);
	chooseflytype();
	state = 0;
	bullettick = 0;
}
void GameEnemy::tick()
{
	switch(state){
	case -1:
	   break;
	case 0:
	   CCPoint mypoint = mysprite->getPosition();
	   if(mypoint.y <= -20){
		  mysprite->stopAllActions();
	      restart();
	   }else{
	     if(bullettick >= 60){
	        bullettick = 0;
	     }else{
	        bullettick ++;
	     }
	   }
	   break;
	}
}
void GameEnemy::setPosition(CCPoint mypoint)
{
	mysprite->setPosition(mypoint);
}
CCMotionStreak *GameEnemy::getstreak()
{
	return mystreak;
}
int GameEnemy::getBulletTick()
{
	return bullettick;
}
bool GameEnemy::iscollision(GameSprite *testsprite)
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
bool GameEnemy::collision(GamePlayer *testsprite)
{
	CCSize ownsize = mysprite->getContentSize();
	CCSize othersize = testsprite->getMySize();
	CCPoint ownp = mysprite->getPosition();
	CCPoint otherp = (testsprite->getsprite())->getPosition();
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 && abs(ownp.y - otherp.y) <= ownsize.height/2 + othersize.height/2){
		if(ownp.y + ownsize.height/2 >= otherp.y - othersize.height/2 && ownp.y - ownsize.height/2 <= otherp.y - othersize.height/2){
			otherp.y = ownp.y + ownsize.height/2 + othersize.height/2;
			testsprite->setPosition(ccp(otherp.x,otherp.y));
			return true;
	    }
		if(ownp.y + ownsize.height/2 >= otherp.y + othersize.height/2 && ownp.y - ownsize.height/2 <= otherp.y + othersize.height/2){
	       otherp.y = ownp.y - ownsize.height/2 - othersize.height/2;
	       testsprite->setPosition(ccp(otherp.x,otherp.y));
	       return true;
	    }
		if(ownp.x + ownsize.width/2 >= otherp.x - othersize.width/2 && ownp.x - ownsize.width/2 <= otherp.x - othersize.width/2){
			otherp.x = ownp.x + ownsize.width/2 + othersize.width/2;
			testsprite->setPosition(ccp(otherp.x,otherp.y));
			return true;
	    }
		if(ownp.x + ownsize.width/2 >= otherp.x + othersize.width/2 && ownp.x - ownsize.width/2 <= otherp.x + othersize.width/2){
	       otherp.x = ownp.x - ownsize.width/2 - othersize.width/2;
	       testsprite->setPosition(ccp(otherp.x,otherp.y));
	       return true;
	    }
	}
	return false;
}
bool GameEnemy::collisionwithbullet(GameBullet *testsprite)
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
CCSize GameEnemy::getMySize()
{
	return mysprite->getContentSize();
}


void GameEnemy::freeze()
{
	mysprite->initWithFile("stop.png");
	this->getsprite()->stopAllActions();
	isFrozen = true;
}

void GameEnemy::revert()
{
	isFrozen = false;
	restart();
}