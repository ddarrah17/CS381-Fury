/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Entity381.h>
#include <GameMgr.h>
#include <UiMgr.h>
#include <UnitAI.h>
#include<Command.h>
#include <Utils.h>
#include <unistd.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	this->selectionDistanceSquaredThreshold = 10000;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		//pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	mMouse->capture();
//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);

}

void InputMgr::UpdateCamera(float dt){
	float move = 200.0f;
	float rotate = .00000005f;
	int d =2;
	 //Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	if(engine->uiMgr->level1==true)
	{
		if(bulletCount1>5)
		{
			Ogre::Vector3 difference1;
			Ogre::Vector3 difference2;
			Ogre::Vector3 difference3;
			Ogre::Vector3 difference4;


			difference1 = engine->entityMgr->entities[bulletCount1]->position - engine->entityMgr->entities[1]->position;
			difference2 = engine->entityMgr->entities[bulletCount1]->position - engine->entityMgr->entities[2]->position;
			difference3 = engine->entityMgr->entities[bulletCount1]->position - engine->entityMgr->entities[3]->position;
			difference4 = engine->entityMgr->entities[bulletCount1-1]->position - engine->entityMgr->entities[4]->position;



			if(((difference1.x<=d)&&(difference1.x>=-d))&&((difference1.z<=d)&&(difference1.z>=-d))&&((difference1.y<=d)&&(difference1.y>=-d)))
			{
				engine->entityMgr->entities[1]->velocity.y=1000000000;
				engine->entityMgr->updatedAmountOfTanks1--;
				engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.05;
			}
			if(((difference2.x<=d)&&(difference2.x>=-d))&&((difference2.z<=d)&&(difference2.z>=-d))&&((difference2.y<=d)&&(difference2.y>=-d)))
			{
				engine->entityMgr->entities[2]->velocity.y=1000000000;
				engine->entityMgr->updatedAmountOfTanks1--;
				engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.05;
			}
			if(((difference3.x<=d)&&(difference3.x>=-d))&&((difference3.z<=d)&&(difference3.z>=-d))&&((difference3.y<=d)&&(difference3.y>=-d)))
			{
				engine->entityMgr->entities[3]->velocity.y=1000000000;
				engine->entityMgr->updatedAmountOfTanks1--;
				engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.05;
			}
			if(((difference4.x<=d)&&(difference4.x>=-d))&&((difference4.z<=d)&&(difference4.z>=-d))&&((difference4.y<=d)&&(difference4.y>=-d)))
			{
				engine->entityMgr->entities[4]->velocity.y=1000000000;
				engine->entityMgr->updatedAmountOfTanks1--;
				engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.05;
			}

	}
	}


if(engine->uiMgr->level2==true||engine->uiMgr->level3==true)
{
	if(bulletCount2>11)
	{
		Ogre::Vector3 difference1;
		Ogre::Vector3 difference2;
		Ogre::Vector3 difference3;
		Ogre::Vector3 difference4;
		Ogre::Vector3 difference5;
		Ogre::Vector3 difference6;
		Ogre::Vector3 difference7;
		Ogre::Vector3 difference8;
		Ogre::Vector3 difference9;
		Ogre::Vector3 difference10;

		difference1 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[1]->position;
		difference2 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[2]->position;
		difference3 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[3]->position;
		difference4 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[4]->position;
		difference5 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[5]->position;
		difference6 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[6]->position;
		difference7 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[7]->position;
		difference8 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[8]->position;
		difference9 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[9]->position;
		difference10 = engine->entityMgr->entities[bulletCount2]->position - engine->entityMgr->entities[10]->position;


		if(((difference1.x<=d)&&(difference1.x>=-d))&&((difference1.z<=d)&&(difference1.z>=-d))&&((difference1.y<=d)&&(difference1.y>=-d)))
		{
			engine->entityMgr->entities[1]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference2.x<=d)&&(difference2.x>=-d))&&((difference2.z<=d)&&(difference2.z>=-d))&&((difference2.y<=d)&&(difference2.y>=-d)))
		{
			engine->entityMgr->entities[2]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference3.x<=d)&&(difference3.x>=-d))&&((difference3.z<=d)&&(difference3.z>=-d))&&((difference3.y<=d)&&(difference3.y>=-d)))
		{
			engine->entityMgr->entities[3]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference4.x<=d)&&(difference4.x>=-d))&&((difference4.z<=d)&&(difference4.z>=-d))&&((difference4.y<=d)&&(difference4.y>=-d)))
		{
			engine->entityMgr->entities[4]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference5.x<=d)&&(difference5.x>=-d))&&((difference5.z<=d)&&(difference5.z>=-d))&&((difference5.y<=d)&&(difference5.y>=-d)))
		{
			engine->entityMgr->entities[5]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference6.x<=d)&&(difference6.x>=-d))&&((difference6.z<=d)&&(difference6.z>=-d))&&((difference6.y<=d)&&(difference6.y>=-d)))
		{
			engine->entityMgr->entities[6]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference7.x<=d)&&(difference7.x>=-d))&&((difference7.z<=d)&&(difference7.z>=-d))&&((difference7.y<=d)&&(difference7.y>=-d)))
		{
			engine->entityMgr->entities[7]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference8.x<=d)&&(difference8.x>=-d))&&((difference8.z<=d)&&(difference8.z>=-d))&&((difference8.y<=d)&&(difference8.y>=-d)))
		{
			engine->entityMgr->entities[8]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference9.x<=d)&&(difference9.x>=-d))&&((difference9.z<=d)&&(difference9.z>=-d))&&((difference9.y<=d)&&(difference9.y>=-d)))
		{
			engine->entityMgr->entities[9]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
		if(((difference10.x<=d)&&(difference10.x>=-d))&&((difference10.z<=d)&&(difference10.z>=-d))&&((difference10.y<=d)&&(difference10.y>=-d)))
		{
			engine->entityMgr->entities[10]->velocity.y=1000000000;
			engine->entityMgr->updatedAmountOfTanks2--;
			engine->uiMgr->healthDecrementer1=engine->uiMgr->healthDecrementer1-.02;
		}
	}
}

}
void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_RETURN))
	{
		enterCount++;
		engine->uiMgr->enterWasHit=true;
		//engine->uiMgr->mTrayMgr->showAll();
		//engine->uiMgr->mTrayMgr->hideBackdrop();
		engine->gfxMgr->mCamera->setPosition(0,15,0);
		engine->gameMgr->cameraNode->lookAt(engine->entityMgr->selectedEntity->position,Ogre::Node::TS_WORLD);



		if(engine->entityMgr->updatedAmountOfTanks1==0||engine->entityMgr->updatedAmountOfTanks2==0)
		{
			engine->uiMgr->enterWasHit2=true;
		}
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_W)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed += deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_S)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredSpeed -= deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_A)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading -= deltaDesiredHeading;
		//engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading-=deltaDesiredHeading;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_D)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->desiredHeading += deltaDesiredHeading;
		//engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading+=deltaDesiredHeading;
	}
	engine->entityMgr->selectedEntity->desiredHeading = FixAngle(engine->entityMgr->selectedEntity->desiredHeading);
	//Set velocity to zero....
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		keyboardTimer = keyTime;
		engine->entityMgr->selectedEntity->velocity = Ogre::Vector3::ZERO;
		engine->entityMgr->selectedEntity->desiredSpeed = engine->entityMgr->selectedEntity->speed = 0;
		engine->entityMgr->selectedEntity->desiredHeading = engine->entityMgr->selectedEntity->heading;
	}

	//tab handling
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)){
		keyboardTimer = keyTime;
		engine->entityMgr->SelectNextEntity();
	}
		Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
		dirVec.x=(engine->entityMgr->selectedEntity->position.x);
		dirVec.y=(engine->entityMgr->selectedEntity->position.y)+10;
		dirVec.z=(engine->entityMgr->selectedEntity->position.z)-110;


	if((keyboardTimer < 0)&& engine->entityMgr->entities.size()==4)
	{
		std::cout<<"Spawn me"<<std::endl;
		engine->entityMgr->entities[5]->desiredSpeed += deltaDesiredSpeed;
	}

	engine->gameMgr->cameraNode->setPosition(dirVec);



	if(engine->uiMgr->level1==true)
	{
		fire++;
		if(fire==1500)
		{
			AIBullet1=engine->entityMgr->entities[1]->position;
			AIBullet2=engine->entityMgr->entities[2]->position;
			AIBullet3=engine->entityMgr->entities[3]->position;
			AIBullet4=engine->entityMgr->entities[4]->position;

			bulletCount1=bulletCount1+4;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet1);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[1]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet2);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[2]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet3);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[3]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet4);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[4]->heading;

			fire=0;
			engine->uiMgr->health=engine->uiMgr->health-engine->uiMgr->healthDecrementer1;
		}

	}

	if(engine->uiMgr->level2==true)
	{
		fire++;
		if(fire==1500)
		{
			AIBullet1=engine->entityMgr->entities[1]->position;
			AIBullet2=engine->entityMgr->entities[2]->position;
			AIBullet3=engine->entityMgr->entities[3]->position;
			AIBullet4=engine->entityMgr->entities[4]->position;
			AIBullet5=engine->entityMgr->entities[5]->position;
			AIBullet6=engine->entityMgr->entities[6]->position;
			AIBullet7=engine->entityMgr->entities[7]->position;
			AIBullet8=engine->entityMgr->entities[8]->position;
			AIBullet9=engine->entityMgr->entities[9]->position;
			AIBullet10=engine->entityMgr->entities[10]->position;

			bulletCount2=bulletCount2+10;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet1);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[1]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet2);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[2]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet3);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[3]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet4);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[4]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet5);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[5]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet6);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[6]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet7);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[7]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet8);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[8]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet9);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[9]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet10);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[10]->heading;


			fire=0;
			engine->uiMgr->health=engine->uiMgr->health-engine->uiMgr->healthDecrementer1;
		}

	}

	if(engine->uiMgr->level3==true)
	{
		fire++;
		if(fire==700)
		{
			AIBullet1=engine->entityMgr->entities[1]->position;
			AIBullet2=engine->entityMgr->entities[2]->position;
			AIBullet3=engine->entityMgr->entities[3]->position;
			AIBullet4=engine->entityMgr->entities[4]->position;
			AIBullet5=engine->entityMgr->entities[5]->position;
			AIBullet6=engine->entityMgr->entities[6]->position;
			AIBullet7=engine->entityMgr->entities[7]->position;
			AIBullet8=engine->entityMgr->entities[8]->position;
			AIBullet9=engine->entityMgr->entities[9]->position;
			AIBullet10=engine->entityMgr->entities[10]->position;

			bulletCount2=bulletCount2+10;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet1);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[1]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet2);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[2]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet3);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[3]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet4);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[4]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet5);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[5]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet6);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[6]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet7);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[7]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet8);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[8]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet9);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[9]->heading;
			engine->entityMgr->CreateEntityOfTypeAtPosition(AIBulletType,AIBullet10);
			engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->entities[10]->heading;


			fire=0;
			engine->uiMgr->health=engine->uiMgr->health-(engine->uiMgr->healthDecrementer1+.1);
		}

	}



}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
    if (engine->uiMgr->mTrayMgr->injectMouseMove(me)) return true;
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
    if (engine->uiMgr->mTrayMgr->injectMouseDown(me, mid)) return true;
	if(OIS::MB_Left == mid && engine->gameMgr->levelStarted==true){
		std::cout << "Left mouse press" << std::endl;
		//HandleMouseSelection(me);
		Ogre::Vector3 bulletPosition=engine->entityMgr->entities[0]->position;
		engine->entityMgr->CreateEntityOfTypeAtPosition(BulletType,bulletPosition);
		engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->heading=engine->entityMgr->selectedEntity->desiredHeading;


		if(engine->uiMgr->level1==true)
		{
			bulletCount1++;

		}
		if(engine->uiMgr->level2==true||engine->uiMgr->level3==true)
		{
			bulletCount2++;
		}

	}



	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
    if (engine->uiMgr->mTrayMgr->injectMouseUp(me, mid)) return true;
	return true;
}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::HandleMouseSelection(const OIS::MouseEvent &me){
	const OIS::MouseState &ms = mMouse->getMouseState();
	int index = -1;
	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
	if(result.first){
		Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);
		float minDistanceSquared = FLT_MAX;
		float distanceSquared; //because squareroot is expensive
		for(unsigned int i = 0; i < engine->entityMgr->entities.size(); i++){
			distanceSquared = posUnderMouse.squaredDistance(engine->entityMgr->entities[i]->position);
			if (distanceSquared < selectionDistanceSquaredThreshold){
				if (distanceSquared < minDistanceSquared){
					index = i;
					minDistanceSquared = distanceSquared;
				}
			}
		}
		engine->entityMgr->Select(index);
	}
}


