#include "GameController.h"
#include "Renderer.h"

GameController::GameController(){}

GameController::~GameController() {}

void GameController::RundGame() {
	AssetController::Instance().Initialize(1000000000);
	Renderer* r = &Renderer::Instance();
	r->Inititlaize(800, 600);
	Point ws = r->GetWindowSize();

	Texture::Pool = new ObjectPool<Texture>();
	Texture* texture = Texture::Pool->GetResource();
	texture->Load("../Assets/Textures/Emoji.tga");

	while (m_sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&m_sdlEvent);
		r->SetViewport(Rect(0, 0, ws.X, ws.Y));
		r->SetDrawColor(Color(255, 0, 0, 255));
		r->ClearScreen();
		r->SetViewport(Rect(0, 0, ws.X/2, ws.Y/2));
		r->RenderTexture(texture, Point(0, 0));
		r->SetViewport(Rect(ws.X / 2, 0, ws.X,  ws.Y / 2));
		r->RenderTexture(texture, Rect(0, 0, ws.X/2, ws.Y/2));
		r->SetViewport(Rect(0, ws.Y / 2, ws.X / 2, ws.Y));
		r->RenderTexture(texture, Rect(0, 0, ws.X / 2, ws.Y / 2));
		r->SetViewport(Rect(ws.X / 2, ws.Y / 2, ws.X , ws.Y));
		r->RenderTexture(texture, Point(0, 0));

		SDL_RenderPresent(r->GetRenderer());
	}
	delete Texture::Pool;
	r->Shutdown();
}
