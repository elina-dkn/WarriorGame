#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"

#include "BaseLevel.h"
#include "Level_1.h"
#include "Level_2.h"


GameController::GameController(){
	m_sdlEvent = { };
}

GameController::~GameController() {}

void GameController::RundGame() {
	AssetController::Instance().Initialize(1000000000);
	Renderer* r = &Renderer::Instance();
	r->Inititlaize(1920, 1080);
	Timing* t = &Timing::Instance();

	Level_1* l1 = new Level_1();
	l1->AssignNonDefaultValues();

	Level_2* l2 = new Level_2();
	l2->AssignNonDefaultValues();



	while (m_sdlEvent.type != SDL_QUIT) {

		t->Tick();

		SDL_PollEvent(&m_sdlEvent);
		

		if (l1->IsPlaying()) {
			l1->Update();
		
		}
		else if (l2->IsPlaying()) {
		
		
			l2->Update();
		}
		else {
			m_sdlEvent.type = SDL_QUIT;
		}
		
		

		
		SDL_RenderPresent(r->GetRenderer());
	}
	delete l1;
	delete l2;

	r->Shutdown();
}
