/*
 * UnitAI.cpp
 *
 *  Created on: Apr 29, 2018
 *      Author: josephstine
 */
#include "UnitAI.h"
#include "Engine.h"


UnitAI::UnitAI(Entity381* ent) : Aspect(ent){

}

UnitAI::~UnitAI()
{

}

void UnitAI::Tick(float dt){
	Command *temp;
	//std::cout<<"am I ticking"<<std::endl;
	if(commands.front()==NULL)
	{
		return;
	}

	for(unsigned int i=0; i<commands.size();i++)
	{
		if(!commands.front()->done())
		{
			commands.front()->tick(dt);
		}
		else
		{
			temp= GetCommand();
			commands.pop();
			delete temp;
		}
	}
}

Command *UnitAI ::GetCommand(){
	return commands.front();
}

void UnitAI::AddCommand(Command *command)
{
	commands.push(command);
}

void UnitAI::SetCommand(Command *command)
{
	Command *temp;
	for(unsigned int i=0; i<commands.size();i++)
	{
			temp= GetCommand();
			commands.pop();
			delete temp;

	}
}



