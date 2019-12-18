/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();

	Ogre::Plane mPlane;

	void MakeGround();
	void MakeSky();
	void MakeEntities();

	bool levelStarted = false;
	Ogre::SceneNode *cameraNode;

};

#endif /* GAMEMGR_H_ */
