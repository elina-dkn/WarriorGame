#include "GameController.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "TTFont.h"


GameController::GameController(){}

GameController::~GameController() {}

void GameController::RundGame() {
	AssetController::Instance().Initialize(1000000000);
	Renderer* r = &Renderer::Instance();
	r->Inititlaize(800, 600);

	TTFont* font = new TTFont();
	font->Initialize(20);

	Point ws = r->GetWindowSize();

	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	SpriteSheet* sheet = SpriteSheet::Pool->GetResource();
	sheet->Load("../Assets/Textures/Warrior.tga");
	sheet->SetSize(17, 6, 69, 44);
	sheet->AddAnimation(EN_AN_IDLE, 0, 6, 0.01f);
	sheet->AddAnimation(EN_AN_RUN, 6, 8, 0.005f);

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


	while (m_sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&m_sdlEvent);
		//r->SetViewport(Rect(0, 0, ws.X, ws.Y));
		r->SetDrawColor(Color(255, 255, 255, 255));
		r->ClearScreen();
		r->RenderTexture(sheet, sheet->Update(EN_AN_IDLE), Rect(0, 0, 69*3, 44*3));
		r->RenderTexture(sheet, sheet->Update(EN_AN_RUN), Rect(0, 150, 69 * 3,150+ 44 * 3));
		//font->Write(r->GetRenderer(), "Testing 123!!", SDL_Color{ 0, 255, 0 }, SDL_Point{ 150, 50 });
		/*r->SetViewport(Rect(0, 0, ws.X/2, ws.Y/2));
		r->RenderTexture(texture, Point(0, 0));
		r->SetViewport(Rect(ws.X / 2, 0, ws.X,  ws.Y / 2));
		r->RenderTexture(texture, Rect(0, 0, ws.X/2, ws.Y/2));
		r->SetViewport(Rect(0, ws.Y / 2, ws.X / 2, ws.Y));
		r->RenderTexture(texture, Rect(0, 0, ws.X / 2, ws.Y / 2));
		r->SetViewport(Rect(ws.X / 2, ws.Y / 2, ws.X , ws.Y));
		r->RenderTexture(texture, Point(0, 0));*/
		string s = "Frame number: " + to_string(sheet->GetCurrentClip(EN_AN_IDLE));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0, 255, 0 }, SDL_Point{ 250, 50 });

		 s = "Frame number: " + to_string(sheet->GetCurrentClip(EN_AN_RUN));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{0, 255, 0}, SDL_Point{250, 200});
		SDL_RenderPresent(r->GetRenderer());
	}
	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;
	font->Shutdown();
	r->Shutdown();
}
