/*
 * Command.cpp
 *
 *  Created on: Apr 29, 2018
 *      Author: josephstine
 */
#include <Command.h>
using namespace std;

Command::Command()
{

}

Command::Command(Entity381* ent, CommandType ct)
{
	entity=ent;
}

Command::~Command()
{

}

void Command::init(){

}

void Command::tick(float dt)
{
 std::cout<<"command tick";
}

bool Command::done()
{

}

MoveTo::MoveTo(Entity381 *ent, Ogre::Vector3 location): Command(ent,commandType)
{
	targetLocation = location;
	isFinished = false;
}

MoveTo::~MoveTo()
{

}

void MoveTo::init()
{

}

void MoveTo::tick(float dt)
{
	std::cout<<"move totick"<<std::endl;
	Ogre:: Real distance = targetLocation.distance(entity->position);

	if(distance<distanceLength)
	{
		entity->desiredSpeed =0;
		entity->velocity=Ogre::Vector3::ZERO;
		isFinished=false;
		return;
	}

	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian angle = Ogre::Math::ATan2(difference.x,difference.z);
	float heading = angle.valueRadians();
	//std::cout<<Ogre::Math::TWO_PI;
	if(heading<0)
	{
		heading+= Ogre::Math::TWO_PI;
	}
	else if(heading >= 0)
	{
		heading-= Ogre::Math::TWO_PI;
	}
	entity->desiredHeading =heading;
	entity->desiredSpeed=entity->maxSpeed;
}

bool MoveTo::done(){
	return isFinished;
}

Intercept::Intercept(Entity381*ent, Entity381*boat): Command(ent,commandType)
{
	isFinished=false;
	targetBoat=boat;
}

Intercept::~Intercept()
{

}

void Intercept::init()
{

}

void Intercept::tick(float dt)
{
	/*//std::cout<<"intercept tick"<<std::endl;
	targetLocation=targetBoat->position;

	Ogre::Real distance = targetLocation.distance(entity->position);
	if(distance<distanceLength)
	{

		entity->desiredSpeed=0;
		entity->velocity=Ogre::Vector3::ZERO;
		isFinished=true;
		return;
	}
	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian angle = Ogre::Math::ATan2(difference.x,difference.z);
	entity->desiredHeading=angle.valueRadians();
	entity->desiredSpeed= entity->maxSpeed;*/






	//std::cout<<"intercept tick";
	targetLocation=targetBoat->position;
	//std::cout<<targetBoat->position<<std::endl;

	Ogre::Real distance = targetLocation.distance(entity->position);
	std::cout<<distance<<std::endl;
	if(distance<distanceLength)
	{

		entity->desiredSpeed=0;
		entity->velocity=Ogre::Vector3::ZERO;
		isFinished=true;
		return;
	}
	Ogre::Vector3 difference = targetLocation - entity->position;
	Ogre::Radian angle = Ogre::Math::ATan2(difference.z,difference.x);
	entity->heading=angle.valueDegrees()-90;
	//std::cout<<entity->desiredHeading<<std::endl;
	entity->desiredSpeed= entity->maxSpeed;
}

bool Intercept::done(){
	return isFinished;
}



