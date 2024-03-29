/*
 * Entity381.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <GfxMgr.h>

#include<Entity381.h>
#include<Physics2D.h>
#include <Aspect.h>
#include <UnitAI.h>

std::string IntToString(int x){
	char tmp[10000];
	sprintf(tmp, "%i", x);
	return std::string(tmp);
}

Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident){

	this->engine = engine;

	entityType = None;
	meshfilename = std::string();
	position = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = ident;
	isSelected = false;
	this->playSound = false;

	name = "Entity381";//meshfname + IntToString(identity);
/*
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);*/
	sceneNode = 0;
	ogreEntity = 0;

	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	UnitAI *a = new UnitAI(this);
	aspects.push_back((Aspect*)a);


	this->acceleration = 0;
	this->desiredHeading = this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;
}

Entity381::~Entity381(){

}

void Entity381::Init(){

	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
	if(meshfilename=="PlayerTank.mesh")
	{
		ogreEntity->setMaterialName("tank");
	}
	if(meshfilename=="AITank.mesh")
	{
		ogreEntity->setMaterialName("tank2");
	}
	if(meshfilename=="bullet.mesh")
	{
		ogreEntity->setMaterialName("bullet");
	}
	this->soundFile = "BoatSound.wav";
	this->audioId = 0;
	//sceneNode->rotate(Ogre::Vector3::NEGATIVE_UNIT_Y,Ogre::Degree(0));
}

void Entity381::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
DDG51::DDG51(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){

	meshfilename = "ddg51.mesh";
	entityType = DDG51Type;
	this->minSpeed = 0;
	this->maxSpeed = 16.0f;//meters per second...
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	std::cout << "Created: " << this->name << std::endl;
}

DDG51::~DDG51(){

}

//-------------------------------------------------------------------------------------------------------------------------------
PlayerTank::PlayerTank(Engine *engine, Ogre::Vector3 pos, int ident):
	Entity381(engine, pos, ident){
	meshfilename = "PlayerTank.mesh";
	entityType = PlayerTankType;
	this->minSpeed = 0;
	this->maxSpeed = 10.0f;//meters per second...
	this->acceleration = .50f; // slow
	this->turnRate = 60.0f; //2 degrees per second
}

PlayerTank::~PlayerTank(){

}
//-------------------------------------------------------------------------------------------------------------------------------

AiTank::AiTank(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "AITank.mesh";
	entityType = AiTankType;
	this->minSpeed = 0;
	this->maxSpeed = 5.0f;//meters per second...
	this->acceleration = .50f; // slow
	this->turnRate = 30.0f; //2 degrees per second
}

AiTank::~AiTank(){

}
//-------------------------------------------------------------------------------------------------------------------------------

Bullet::Bullet(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "bullet.mesh";
	entityType = BulletType;
	this->minSpeed = 200;
	this->maxSpeed = 200;
	this->acceleration = 5.0f;
	this->turnRate = 0;
	this->bulletHeading=0.0f;
}

Bullet::~Bullet(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Alien::Alien(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "bullet.mesh";
	entityType = BulletType;
	this->minSpeed = 200;
	this->maxSpeed = 200;
	this->acceleration = 5.0f;
	this->turnRate = 0;
	this->bulletHeading=0.0f;
}

Alien::~Alien(){

}
//-------------------------------------------------------------------------------------------------------------------------------


