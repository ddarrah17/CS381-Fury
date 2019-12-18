/*
 * UnitAI.h
 *
 *  Created on: Apr 29, 2018
 *      Author: josephstine
 */

#ifndef INC_UNITAI_H_
#define INC_UNITAI_H_

#include <queue>
#include "Aspect.h"
#include "InputMgr.h"
#include "Types381.h"
#include "Command.h"

class UnitAI: public Aspect {
public:
	std::queue<Command*> commands;
	UnitAI(Entity381 *ent);
	~UnitAI();

	virtual void Tick(float dt);
	Command* GetCommand();
	virtual void AddCommand(Command *c);
	virtual void SetCommand(Command *c);
};




#endif /* INC_UNITAI_H_ */
