/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */


//#include <GameMgr.h>
#include <UnitAI.h>
#include<Command.h>

#include <Utils.h>
#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <GameMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>
#include <iostream>
#include <string>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);
	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::LoadLevel(){
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Start Level 1!");
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton2", "Start Level 2!");
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton3", "Start Death");


	mTrayMgr->showBackdrop("ECSLENT/UI");
	std::string enemiesRemaining = "Enemies remaining: " + std::to_string(engine->entityMgr->entities.size()-1) + "/" + std::to_string(engine->entityMgr->entities.size()-1);
	mLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT,"MyLabel",enemiesRemaining,250);
	//OgreBites::ProgressBar * pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT,"HealthBar", "Health", 200, 100);
	pbar->setProgress(health);
	mTrayMgr->hideAll();
	mTrayMgr->showBackdrop();

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();
    int enemies = engine->entityMgr->entities.size()-1;
	//if(tanksSpawned==true&&engine->entityMgr->entities[engine->entityMgr->entities.size()-1]->meshfilename=="AITank.mesh")
	//{
		mTrayMgr->destroyWidget("MyLabel");
		if(level2==true)
		{
			std::string enemiesRemaining = "Enemies remaining: " + std::to_string(engine->entityMgr->updatedAmountOfTanks2) + "/" + std::to_string(engine->entityMgr->amountOfTanks2);
			mLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT,"MyLabel",enemiesRemaining,250);
		}
		else if(level3==true)
		{
			std::string enemiesRemaining = "Enemies remaining: " + std::to_string(engine->entityMgr->updatedAmountOfTanks2) + "/" + std::to_string(engine->entityMgr->amountOfTanks2);
			mLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT,"MyLabel",enemiesRemaining,250);
		}
		else if(level1==true)
		{
			std::string enemiesRemaining = "Enemies remaining: " + std::to_string(engine->entityMgr->updatedAmountOfTanks1) + "/" + std::to_string(engine->entityMgr->amountOfTanks1);
			mLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT,"MyLabel",enemiesRemaining,250);
		}
		else
		{
			std::string enemiesRemaining = "Enemies remaining: 0/0";
			mLabel = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT,"MyLabel",enemiesRemaining,250);
		}



		if(engine->inputMgr->enterCount==1)
		{
			//engine->uiMgr->mTrayMgr->hideBackdrop();
		}

		if(engine->inputMgr->enterCount==2)
		{
			mTrayMgr->hideAll();
			mTrayMgr->showBackdrop("ECSLENT/UI4");
		}
		if(engine->inputMgr->enterCount==3)
		{

			mTrayMgr->showAll();
			mTrayMgr->hideBackdrop();
		}

		if(engine->entityMgr->updatedAmountOfTanks1==0 || engine->entityMgr->updatedAmountOfTanks2==0)
		{
			mTrayMgr->hideAll();
			mTrayMgr->showBackdrop("ECSLENT/UI2");
			if(enterWasHit2==true)
			{
				mTrayMgr->showBackdrop("ECSLENT/UI3");
			}
		}
		//OgreBites::ProgressBar * pbar;
		//pbar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMRIGHT,"HealthBar", "Health", 200, 130);
		pbar->setProgress(health);
		if(health<=0.0)
		{
			mTrayMgr->hideAll();
			mTrayMgr->showBackdrop("ECSLENT/UI5");
		}
}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){
    if(b->getName()=="MyButton")
    {
    	level1=true;
        std::cout <<"Level Started!" << std::endl;
        engine->gameMgr->levelStarted=true;
        Ogre::Vector3 pos;
        pos.x = -40;
        pos.y = 2;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 20;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 20;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -40;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);

        Intercept* move1 = new Intercept(engine-> entityMgr -> entities[1], engine->entityMgr->entities[0]);
        Intercept* move2 = new Intercept(engine-> entityMgr -> entities[2], engine->entityMgr->entities[0]);
        Intercept* move3 = new Intercept(engine-> entityMgr -> entities[3], engine->entityMgr->entities[0]);
        Intercept* move4 = new Intercept(engine-> entityMgr -> entities[4], engine->entityMgr->entities[0]);

    	bool playerTankDestroyed=false;
    if(playerTankDestroyed==false)
    	{


    		engine -> entityMgr ->entities[1]-> aspects[2] -> AddCommand(move1);

    		engine -> entityMgr ->entities[2]-> aspects[2] -> AddCommand(move2);

    		engine -> entityMgr ->entities[3]-> aspects[2] -> AddCommand(move3);

    		engine -> entityMgr ->entities[4]-> aspects[2] -> AddCommand(move4);

    		std::cout<<"Am I adding commands"<<std::endl;
    		tanksSpawned=true;
    	}
    	tanksSpawned=true;
    }



    if(b->getName()=="MyButton2")
    {
    	level2=true;
        std::cout <<"Level Started!" << std::endl;
        engine->gameMgr->levelStarted=true;
        Ogre::Vector3 pos;
        pos.x = -40;
        pos.y = 2;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 20;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 20;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -40;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -80;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -100;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 200;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 300;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 40;
        pos.z = 500;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 340;
        pos.z = 200;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 340;
        pos.z = 220;
        Intercept* move1 = new Intercept(engine-> entityMgr -> entities[1], engine->entityMgr->entities[0]);
        Intercept* move2 = new Intercept(engine-> entityMgr -> entities[2], engine->entityMgr->entities[0]);
        Intercept* move3 = new Intercept(engine-> entityMgr -> entities[3], engine->entityMgr->entities[0]);
        Intercept* move4 = new Intercept(engine-> entityMgr -> entities[4], engine->entityMgr->entities[0]);
        Intercept* move5 = new Intercept(engine-> entityMgr -> entities[5], engine->entityMgr->entities[0]);
        Intercept* move6 = new Intercept(engine-> entityMgr -> entities[6], engine->entityMgr->entities[0]);
        Intercept* move7 = new Intercept(engine-> entityMgr -> entities[7], engine->entityMgr->entities[0]);
        Intercept* move8 = new Intercept(engine-> entityMgr -> entities[8], engine->entityMgr->entities[0]);
        Intercept* move9 = new Intercept(engine-> entityMgr -> entities[9], engine->entityMgr->entities[0]);
        Intercept* move10 = new Intercept(engine-> entityMgr -> entities[10], engine->entityMgr->entities[0]);


    /*	MoveTo* move1 = new MoveTo(engine -> entityMgr -> entities[1], engine->entityMgr->entities[0]->position);
    	MoveTo* move2 = new MoveTo(engine -> entityMgr -> entities[2], engine->entityMgr->entities[0]->position);
    	MoveTo* move3 = new MoveTo(engine -> entityMgr -> entities[3], engine->entityMgr->entities[0]->position);
    	MoveTo* move4 = new MoveTo(engine -> entityMgr -> entities[4], engine->entityMgr->entities[0]->position); */
    	bool playerTankDestroyed=false;
    if(playerTankDestroyed==false)
    	{


    		engine -> entityMgr ->entities[1]-> aspects[2] -> AddCommand(move1);

    		engine -> entityMgr ->entities[2]-> aspects[2] -> AddCommand(move2);

    		engine -> entityMgr ->entities[3]-> aspects[2] -> AddCommand(move3);

    		engine -> entityMgr ->entities[4]-> aspects[2] -> AddCommand(move4);

    		engine -> entityMgr ->entities[5]-> aspects[2] -> AddCommand(move5);

    		engine -> entityMgr ->entities[6]-> aspects[2] -> AddCommand(move6);

    		engine -> entityMgr ->entities[7]-> aspects[2] -> AddCommand(move7);

    		engine -> entityMgr ->entities[8]-> aspects[2] -> AddCommand(move8);

    		engine -> entityMgr ->entities[9]-> aspects[2] -> AddCommand(move9);

    		engine -> entityMgr ->entities[10]-> aspects[2] -> AddCommand(move10);
    		std::cout<<"Am I adding commands"<<std::endl;
    		tanksSpawned=true;
    	}
    	tanksSpawned=true;
    }

    if(b->getName()=="MyButton3")
    {
    	level3=true;
        std::cout <<"Level Started!" << std::endl;
        engine->gameMgr->levelStarted=true;
        Ogre::Vector3 pos;
        pos.x = -40;
        pos.y = 2;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 20;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 20;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -40;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -80;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = -100;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 200;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 300;
        pos.z = 100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 40;
        pos.z = 500;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 340;
        pos.z = 200;
        engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
        pos.x = 340;
        pos.z = 220;
        Intercept* move1 = new Intercept(engine-> entityMgr -> entities[1], engine->entityMgr->entities[0]);
        Intercept* move2 = new Intercept(engine-> entityMgr -> entities[2], engine->entityMgr->entities[0]);
        Intercept* move3 = new Intercept(engine-> entityMgr -> entities[3], engine->entityMgr->entities[0]);
        Intercept* move4 = new Intercept(engine-> entityMgr -> entities[4], engine->entityMgr->entities[0]);
        Intercept* move5 = new Intercept(engine-> entityMgr -> entities[5], engine->entityMgr->entities[0]);
        Intercept* move6 = new Intercept(engine-> entityMgr -> entities[6], engine->entityMgr->entities[0]);
        Intercept* move7 = new Intercept(engine-> entityMgr -> entities[7], engine->entityMgr->entities[0]);
        Intercept* move8 = new Intercept(engine-> entityMgr -> entities[8], engine->entityMgr->entities[0]);
        Intercept* move9 = new Intercept(engine-> entityMgr -> entities[9], engine->entityMgr->entities[0]);
        Intercept* move10 = new Intercept(engine-> entityMgr -> entities[10], engine->entityMgr->entities[0]);


    /*	MoveTo* move1 = new MoveTo(engine -> entityMgr -> entities[1], engine->entityMgr->entities[0]->position);
    	MoveTo* move2 = new MoveTo(engine -> entityMgr -> entities[2], engine->entityMgr->entities[0]->position);
    	MoveTo* move3 = new MoveTo(engine -> entityMgr -> entities[3], engine->entityMgr->entities[0]->position);
    	MoveTo* move4 = new MoveTo(engine -> entityMgr -> entities[4], engine->entityMgr->entities[0]->position); */
    	bool playerTankDestroyed=false;
    if(playerTankDestroyed==false)
    	{


    		engine -> entityMgr ->entities[1]-> aspects[2] -> AddCommand(move1);

    		engine -> entityMgr ->entities[2]-> aspects[2] -> AddCommand(move2);

    		engine -> entityMgr ->entities[3]-> aspects[2] -> AddCommand(move3);

    		engine -> entityMgr ->entities[4]-> aspects[2] -> AddCommand(move4);

    		engine -> entityMgr ->entities[5]-> aspects[2] -> AddCommand(move5);

    		engine -> entityMgr ->entities[6]-> aspects[2] -> AddCommand(move6);

    		engine -> entityMgr ->entities[7]-> aspects[2] -> AddCommand(move7);

    		engine -> entityMgr ->entities[8]-> aspects[2] -> AddCommand(move8);

    		engine -> entityMgr ->entities[9]-> aspects[2] -> AddCommand(move9);

    		engine -> entityMgr ->entities[10]-> aspects[2] -> AddCommand(move10);
    		std::cout<<"Am I adding commands"<<std::endl;
    		tanksSpawned=true;
    	}
    	tanksSpawned=true;
    }

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    Ogre::Vector3 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 100;
    switch(m->getSelectionIndex()){
    case 1:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(AiTankType,pos);
    	break;
    case 2:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type,pos);
    	break;
    case 3:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(PlayerTankType,pos);
    	mLabel->setCaption("Carrier has Arrived!");
    	break;
    default:
    	break;
    }

}
