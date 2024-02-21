#include "Level.h"


Level::Level() {
	AssetController::Instance().Initialize(10000000);
	r = &Renderer::Instance();
	
	t = &Timing::Instance();
	font = new TTFont();
	font->Initialize(20);



	m_status = true;
	m_gameTime = 0;
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_warrior = SpriteSheet::Pool->GetResource();

}

Level::~Level() {

	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {
	int r = 0;
	float x = 0.0f;
	for (int i = 0; i < 10; i++) {
		r = rand() % 21 + 80;
		x = (r - 80) * 0.06f + 4.8f;
		m_speeds.push_back(r);
		m_warrior = SpriteSheet::Pool->GetResource();
		m_warrior->Load("../Assets/Textures/Warrior.tga");
		m_warrior->SetSize(17, 6, 69, 44);
		m_warrior->AddAnimation(EN_AN_IDLE, 0, 6, 0.0f, r);
		m_warrior->AddAnimation(EN_AN_RUN, 6, 8, x, r);
		m_warriors.push_back(m_warrior);

	}

	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {


	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.write(reinterpret_cast<char*>(&m_status), sizeof(m_status));
	

	int count = m_warriors.size();
	_stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++) {
		m_warriors[i]->Serialize(_stream);
		_stream.write(reinterpret_cast<char*>(&m_speeds[i]), sizeof(m_speeds[i]));
	}

	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	
	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.read(reinterpret_cast<char*>(&m_status), sizeof(m_status));


	int count;
	_stream.read(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++) {
		m_warrior = SpriteSheet::Pool->GetResource();
		m_warrior->Deserialize(_stream);
		m_warriors.push_back(m_warrior);
		int sp;
		_stream.read(reinterpret_cast<char*>(&sp), sizeof(sp));
		m_speeds.push_back(sp);
	}
	
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}

void Level::Render() {
	m_status = true;
	r->ClearScreen();
	//string fps = "Frames Per Second: " + to_string(t->GetFPS());
	//font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });
	//string s = "Game Time: " + to_string(floor(m_gameTime));
	//font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0,  0, 255 }, SDL_Point{ 250, 0 });
	
}

void Level::RenderWarriors() {
	for (int i = 0; i < 10; i++) {
		if (0 + m_gameTime * m_speeds[i] > 1920) {
			m_status = false;
			//m_gameTime = SDL_GetTicks();
			return;
		}
		cout << m_gameTime << endl;
		string s = "Game Time: " + to_string(floor(m_gameTime));
		font->Write(r->GetRenderer(), s.c_str(), SDL_Color{ 0,  0, 255 }, SDL_Point{ 250, 0 });
		r->RenderTexture(m_warriors[i], m_warriors[i]->Update(EN_AN_RUN, t->GetDeltaTime()), Rect( 0 +  m_speeds[i] *m_gameTime, 10 + i * 100, 69 * 1.8 +  m_speeds[i]* m_gameTime, 10 + i * 100 + 44 * 1.8));

	}
}

