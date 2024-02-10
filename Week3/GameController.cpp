#include "GameController.h"
#include "Renderer.h"

GameController::GameController(){}

GameController::~GameController() {}

void GameController::RundGame() {
	Renderer* r = &Renderer::Instance();
	r->Inititlaize(800, 600);

	while (m_sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&m_sdlEvent);
		r->SetDrawColor(Color(255, 0, 0, 255));
		r->ClearScreen();
		r->SetDrawColor(Color(255, 255, 0, 255));
		for (unsigned int count = 0; count < 800; count++) {
			if (count % 2 == 0) r->RenderPoint(Point(count, 300));
		}
		r->SetDrawColor(Color(0, 0, 255, 255));
		r->RenderLine(Rect(400, 0, 400, 600));
		r->SetDrawColor(Color(0, 255, 0, 255));
		r->RenderRectangle(Rect(200, 200, 300, 300));
		r->SetDrawColor(Color(255, 255, 255, 255));
		r->RenderFillRectangle(Rect(400, 400, 500, 500));

		SDL_RenderPresent(r->GetRenderer());
	}
	r->Shutdown();
}
