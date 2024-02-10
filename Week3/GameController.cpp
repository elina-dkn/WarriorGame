#include "GameController.h"
#include "Renderer.h"

GameController::GameController(){}

GameController::~GameController() {}

GameController::RundGame() {
	Renderer* r = &Renderer::Instance();
	r->Inititlaize(800, 600);

	while (m_sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&m_sdlEvent);
		r->SetDrawColor(Color(255, 0, 0, 255));
		r->ClearScreen();
		SDL_RenderPresent(r->GetRenderer());
	}
	r->Shutdown();
}
