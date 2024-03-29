/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>


GameMgr::GameMgr(Engine *engine): Mgr(engine) {
	cameraNode = 0;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::LoadLevel(){

	  engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	  //engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0,0,100));
	  Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	  light->setPosition(20.0, 80.0, 50.0);

	  // a fixed point in the ocean so you can see relative motion

	  Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
	  Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
	  sceneNode->attachObject(ogreEntityFixed);
	  sceneNode->showBoundingBox(true);

	  /*Ogre::Entity* ogreEntityFixed2 = engine->gfxMgr->mSceneMgr->createEntity("AITank.mesh");
	  Ogre::SceneNode* sceneNode2 = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 2, 0));
	  sceneNode2->attachObject(ogreEntityFixed2);
	  sceneNode2->showBoundingBox(true);*/

	  // A node to attach the camera to so we can move the camera node instead of the camera.
	  cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	  //cameraNode->setPosition(0, 10, -110);
	  cameraNode->setInheritOrientation(true);
	  cameraNode->setFixedYawAxis(true);
	  cameraNode->attachObject(engine->gfxMgr->mCamera);

	  engine->gfxMgr->MakeGround();
	  engine->gfxMgr->MakeSky();
	  MakeEntities();
}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(0,2, 0);
	//engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	//pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(PlayerTankType, pos);
	Ogre::SceneNode* playerTank = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode((pos));
	playerTank->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y,Ogre::Degree(90));
	//engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType,Ogre::Vector3(0,20,100));
	//pos.x += 500;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	//pos.x += 500;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	//pos.x += 500;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);
	//pos.x = 0;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);

	engine->entityMgr->SelectNextEntity(); //sets selection
}

