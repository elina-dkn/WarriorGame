#include "Level2.h"
#include "Renderer.h"


Level2::Level2() {
	m_gameTime = SDL_GetTicks();
	m_status = true;
	font = new TTFont();
	font->Initialize(20);


	r = &Renderer::Instance();
	t = &Timing::Instance();
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_warrior = SpriteSheet::Pool->GetResource();

}

Level2::~Level2() {
	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

}

void Level2::AssignNonDefaultValues() {
	//m_warrior->Load("../Assets/Textures/Warrior.tga");
	//m_warrior->SetSize(17, 6, 69, 44);
	//m_warrior->AddAnimation(EN_AN_IDLE, 0, 6, 0.0f);
	//m_warrior->AddAnimation(EN_AN_RUN, 6, 8, 4.8f);

	Level::AssignNonDefaultValues();
}

void Level2::Render() {
	r->SetDrawColor(Color(0, 128, 0, 255));
	r->ClearScreen();
	//bool a = Level::IsPlaying();
	//if (a) {
		m_gameTime = SDL_GetTicks() - m_gameTime;
		Level::SetGameTime(m_gameTime/1000.0f);
		Level::Render();
		Level::RenderWarriors();
		/*string s = "Game Time: " + to_string(floor(m_gameTime/1000.0f));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0,  0, 255 }, SDL_Point{ 250, 0 });*/

		string s = "Auto Saved: " + to_string(IsPlaying());
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0,  0, 255 }, SDL_Point{ 450, 0 });
	//}
	//else {
		//m_status = false;
	//}

}

void Level2::Serialize(std::ostream& _stream) {
	m_warrior->Serialize(_stream);

	Level::Serialize(_stream);
}

void Level2::Deserialize(std::istream& _stream) {
	m_warrior->Deserialize(_stream);
	Level::Deserialize(_stream);
}


void Level2::ToString() {
	cout << "LEVEL" << endl;

	Level::ToString();
}
