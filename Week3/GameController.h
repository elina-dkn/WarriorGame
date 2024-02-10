#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
class GameController : public Singleton<GameController>
{
public:
	GameController();
	virtual ~GameController();

	void RundGame();

private:
	SDL_Event m_sdlEvent;
};

#endif