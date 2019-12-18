#ifndef __Entity381_h_
#define __Entity381_h_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
//#include <Aspect.h>
#include <Types381.h>
#include <Engine.h>

class Aspect;

class Entity381
{
public:
  Entity381(Engine *engine, Ogre::Vector3 pos, int identity);
  virtual ~Entity381();

  Engine *engine;

  //static data
  int identity;

  std::string name;
  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;
  std:: string materialname;
  float acceleration, turnRate;
  float minSpeed, maxSpeed;

  //dynamic data
  Ogre::Vector3 position;
  Ogre::Vector3 velocity;
  Ogre::Vector3 targetLocation;
  bool isSelected;
  float desiredHeading, desiredSpeed;
  float heading, bulletHeading, speed;

  //sound stuff
  std::string soundFile;
  bool playSound;
  unsigned int audioId;
  bool didSelectSoundPlay;

  EntityTypes entityType;

  std::vector <Aspect* > aspects;

  void Init();

  void Tick(float dt);

protected:


};



class PlayerTank: public Entity381 {
public:
	PlayerTank(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~PlayerTank();

};

class DDG51: public Entity381 {
public:
	DDG51(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~DDG51();

};

class AiTank: public Entity381 {
public:
	AiTank(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~AiTank();

};

class Bullet: public Entity381 {
public:
	Bullet(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Bullet();

};

class Alien: public Entity381 {
public:
	Alien(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Alien();

};


#endif // #ifndef __Entity381_h_
