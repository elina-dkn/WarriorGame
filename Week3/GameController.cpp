#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"
#include "Timing.h"
#include "Level1.h"
#include "Level2.h"


GameController::GameController(){
	m_sdlEvent = { };
}

GameController::~GameController() {}

void GameController::RundGame() {
	AssetController::Instance().Initialize(1000000000);
	Renderer* r = &Renderer::Instance();
	r->Inititlaize(1920, 1080);
	Timing* t = &Timing::Instance();
	//r->Inititlaize(1920, 1080);
	TTFont* font = new TTFont();
	font->Initialize(20);

	Level1* level = new Level1();
	level->AssignNonDefaultValues();

	Level2* level2 = new Level2();
	level2->AssignNonDefaultValues();
	
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	//SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	//SpriteSheet* sheet = level->GetWarrior();


	/*ofstream writeStream("resource.bin", ios::out | ios::binary);
	sheet->Serialize(writeStream);
	writeStream.close();


	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	AssetController::Instance().Clear();
	AssetController::Instance().Initialize(1000000000);
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();

	SpriteSheet* sheet2 = SpriteSheet::Pool->GetResource();
	ifstream readStream("resource.bin", ios::in | ios::binary);
	sheet2->Deserialize(readStream);
	readStream.close();*/
	float timer = 0.0f;
	bool saved = false;
	while (m_sdlEvent.type != SDL_QUIT) {

		t->Tick();
		timer += t->GetDeltaTime();
		SDL_PollEvent(&m_sdlEvent);
		//r->SetViewport(Rect(0, 0, ws.X, ws.Y));
		//r->SetDrawColor(Color(255, 255, 255, 255));
		//r->ClearScreen();
		////r->RenderTexture(sheet, sheet->Update(EN_AN_IDLE, t->GetDeltaTime()), Rect(0, 0, 69*3, 44*3));
		//int ra = rand() % 21 + 80;
		//for (int i = 0; i < 10; i++) {
		//	r->RenderTexture(sheet, sheet->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(0 + t->GetTime() * ra, 10 + i * 100, 69 * 3 + t->GetTime()* ra, 10 + i * 100 + 44 * 3));
		//}
		
		//font->Write(r->GetRenderer(), "Testing 123!!", SDL_Color{ 0, 255, 0 }, SDL_Point{ 150, 50 });
		/*r->SetViewport(Rect(0, 0, ws.X/2, ws.Y/2));
		r->RenderTexture(texture, Point(0, 0));
		r->SetViewport(Rect(ws.X / 2, 0, ws.X,  ws.Y / 2));
		r->RenderTexture(texture, Rect(0, 0, ws.X/2, ws.Y/2));
		r->SetViewport(Rect(0, ws.Y / 2, ws.X / 2, ws.Y));
		r->RenderTexture(texture, Rect(0, 0, ws.X / 2, ws.Y / 2));
		r->SetViewport(Rect(ws.X / 2, ws.Y / 2, ws.X , ws.Y));
		r->RenderTexture(texture, Point(0, 0));*/
		if (level->IsPlaying()) {
			level->Render();
			if (timer >= 5.0f && !saved) {
				ofstream writeStream("Level1.bin", ios::out | ios::binary);
				level->Serialize(writeStream);
				writeStream.close();
			
				ifstream readStream("Level1.bin", ios::in | ios::binary);
				level->Deserialize(readStream);
				readStream.close(); 
				saved = true;
	
			}
			
		}
		else {
			
			level2->Render();
		}
		
		
		

		
		SDL_RenderPresent(r->GetRenderer());
	}
	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	font->Shutdown();
	r->Shutdown();
}
