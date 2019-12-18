/*
 * Command.h
 *
 *  Created on: Apr 29, 2018
 *      Author: josephstine
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include "Entity381.h"
#include "InputMgr.h"
#include "Types381.h"

class Command {
public:
	Command();
	Command(Entity381* ent, CommandType ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Entity381* entity;
	CommandType commandType;
};

class MoveTo: public Command{
public:
	MoveTo(Entity381* ent, Ogre::Vector3 location);
	~MoveTo();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Ogre::Vector3 targetLocation;
	float distanceLength = 50;

	bool isFinished;
};

class Intercept: public Command{
public:
	Intercept(Entity381* ent, Entity381* boat);
	~Intercept();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Ogre::Vector3 targetLocation;
	Entity381* targetBoat;
	float distanceLength = 0;

	bool isFinished;
};





#endif /* INC_COMMAND_H_ */
