#include "Level_1.h"

#include "Renderer.h"


Level_1::Level_1() {
	m_gameTime = 0;
	m_status = true;
	m_timer = 0.0f;
	m_saved = false;
	font = new TTFont();
	font->Initialize(20);


	r = &Renderer::Instance();
	t = &Timing::Instance();
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_warrior = SpriteSheet::Pool->GetResource();
}

Level_1::~Level_1() {


	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

	delete font;
	m_warriors.clear();

}

void Level_1::AssignNonDefaultValues() {
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
	
	BaseLevel::AssignNonDefaultValues();
	
}

void Level_1::Update() {
	
	
	if (m_status) {
		m_gameTime = SDL_GetTicks()/1000.0f;
		m_timer += t->GetDeltaTime();
		if (m_timer >= 5.0f && !m_saved) {
			ofstream writeStream("Level1.bin", ios::out | ios::binary);
			Serialize(writeStream);
			writeStream.close();

			ifstream readStream("Level1.bin", ios::in | ios::binary);
			Deserialize(readStream);
			readStream.close();
			m_saved = true;

		}
		r->SetDrawColor(Color(128, 128, 128, 255));
		r->ClearScreen();
		RenderWarriors();
		RenderLabels();

	}
	else {
		for (int i = 0; i < 10; i++) {
			
	
			SpriteSheet::Pool->ReleaseResource(m_warriors[i]);

		}

		
		return;
	}
	

}

void Level_1::RenderLabels() {
	string saved;
	if (m_saved) {
		saved = "Auto Saved: Yes";
	}
	else {
		saved = "Auto Saved: No";
	}
	font->Write(r->GetRenderer(), saved.c_str(), SDL_Color{ 0,  0, 255 }, SDL_Point{ 450, 0 });

	string fps = "Frames Per Second: " + to_string(t->GetFPS());
	font->Write(r->GetRenderer(), fps.c_str(), SDL_Color{ 0, 0, 255 }, SDL_Point{ 0, 0 });
	
	string gt = "Game Time: " + to_string(static_cast<int>(m_gameTime));
	font->Write(r->GetRenderer(), gt.c_str(), SDL_Color{ 0,  0, 255 }, SDL_Point{ 250, 0 });

}


void Level_1::RenderWarriors() {
	for (int i = 0; i < 10; i++) {
		if (0 + m_gameTime * m_speeds[i] > 1920) {
			t->SetLevelTime(m_gameTime);
			m_status = false;
			return;
		}
		
		r->RenderTexture(m_warriors[i], m_warriors[i]->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(0 + m_speeds[i] * m_gameTime, 10 + i * 100, 69 * 1.8 + m_speeds[i] * m_gameTime, 10 + i * 100 + 44 * 1.8));

	}
}

void Level_1::Serialize(std::ostream& _stream) {

	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.write(reinterpret_cast<char*>(&m_status), sizeof(m_status));
	_stream.write(reinterpret_cast<char*>(&m_saved), sizeof(m_saved));
	_stream.write(reinterpret_cast<char*>(&m_timer), sizeof(m_timer));


	int count = m_warriors.size();
	_stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++) {
		m_warriors[i]->Serialize(_stream);
		_stream.write(reinterpret_cast<char*>(&m_speeds[i]), sizeof(m_speeds[i]));
	}

	BaseLevel::Serialize(_stream);
}

void Level_1::Deserialize(std::istream& _stream) {

	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.read(reinterpret_cast<char*>(&m_status), sizeof(m_status));
	_stream.read(reinterpret_cast<char*>(&m_saved), sizeof(m_saved));
	_stream.read(reinterpret_cast<char*>(&m_timer), sizeof(m_timer));


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
	BaseLevel::Deserialize(_stream);
}


void Level_1::ToString() {
	cout << "LEVEL" << endl;

	BaseLevel::ToString();
}
