#include "Level_2.h"
#include "Renderer.h"


Level_2::Level_2() {

	m_gameTime = 0;
	m_status = true;
	m_timer = 0.0f;
	m_saved = false;


	font = new TTFont();
	font->Initialize(20);


	r = &Renderer::Instance();
	t = &Timing::Instance();

	m_rock = SpriteSheet::Pool->GetResource();
	m_warrior = SpriteSheet::Pool->GetResource();
}

Level_2::~Level_2() {

	delete font;

	m_warriors.clear();
	m_speeds.clear();
	m_rockSpeeds.clear();
	m_dead.clear();
	m_rocks.clear();
}

void Level_2::AssignNonDefaultValues() {
	int r = 0;
	float x = 0.0f;
	for (int i = 0; i < 10; i++) {
		r = rand() % 21 + 80;
		x = (r - 80) * 0.06f + 4.8f;
		m_speeds.push_back(r);


		m_warrior = SpriteSheet::Pool->GetResource();
		m_warrior->Load("../Assets/Textures/Warrior.tga");
		m_warrior->SetSize(17, 6, 69, 44);
		m_warrior->AddAnimation(EN_AN_DEATH, 26, 10, 5.0f, r);
		m_warrior->AddAnimation(EN_AN_RUN, 6, 8, x, r);
		m_warriors.push_back(m_warrior);


		r = rand() % 21 + 80;
		x = (r - 80) * 0.06f + 4.8f;
		m_rockSpeeds.push_back(r);

		m_rock = SpriteSheet::Pool->GetResource();
		m_rock->Load("../Assets/Textures/Rock.tga");
		m_rock->SetSize(1, 4, 20, 20);
		m_rock->AddAnimation(EN_AN_ROCK, 0, 4, x, r);
		m_rocks.push_back(m_rock);

		m_dead.push_back(false);
	}




	BaseLevel::AssignNonDefaultValues();
}

void Level_2::Update() {


	if (m_status) {
		m_gameTime += t->GetDeltaTime();
		m_timer += t->GetDeltaTime();
		if (m_timer >= 5.0f && !m_saved) {
			ofstream writeStream("Level2.bin", ios::out | ios::binary);
			Serialize(writeStream);
			writeStream.close();

			ifstream readStream("Level2.bin", ios::in | ios::binary);
			Deserialize(readStream);
			readStream.close();
			m_saved = true;

		}
		r->SetDrawColor(Color(0, 128, 0, 255));
		r->ClearScreen();
		RenderWarriors();
		RenderLabels();



	}


}

void Level_2::RenderLabels() {
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


void Level_2::RenderWarriors() {

	for (int i = 0; i < 10; i++) {
		if (0 + m_gameTime * m_speeds[i] > 1920 ) {
			m_status = false;
			return;
		}
		if ( (0 + m_speeds[i] * m_gameTime > 50 + i * 100) &&( 0 + m_speeds[i] * m_gameTime < 50 + i * 100 + 20 * 1.0) && (10 + i * 100 > 0 + m_rockSpeeds[i] * m_gameTime) &&(10 + i * 100 < 20 * 1.0 + m_rockSpeeds[i] * m_gameTime) ){
		
			m_dead[i] = true;
			r->RenderTexture(m_warriors[i], m_warriors[i]->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(0 + m_speeds[i] * m_gameTime, 10 + i * 100, 69 * 1.8 + m_speeds[i] * m_gameTime, 10 + i * 100 + 44 * 1.8));
		}
		else {
			if (!m_dead[i]) {
				r->RenderTexture(m_rocks[i], m_rocks[i]->Update(EN_AN_ROCK, t->GetDeltaTime()), Rect(50 + i * 100, 0 + m_rockSpeeds[i] * m_gameTime, 50 + i * 100 + 20 * 1.0, 20 * 1.0 + m_rockSpeeds[i] * m_gameTime));
				r->RenderTexture(m_warriors[i], m_warriors[i]->Update(EN_AN_RUN, t->GetDeltaTime()), Rect(0 + m_speeds[i] * m_gameTime, 10 + i * 100, 69 * 1.8 + m_speeds[i] * m_gameTime, 10 + i * 100 + 44 * 1.8));

			}
			else {
				r->RenderTexture(m_warriors[i], m_warriors[i]->Update(EN_AN_DEATH, t->GetDeltaTime()), Rect(0 + m_speeds[i] * m_gameTime, 10 + i * 100, 69 * 1.8 + m_speeds[i] * m_gameTime, 10 + i * 100 + 44 * 1.8));
			}
			
		}
		
	}
}

void Level_2::Serialize(std::ostream& _stream) {

	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	_stream.write(reinterpret_cast<char*>(&m_status), sizeof(m_status));
	_stream.write(reinterpret_cast<char*>(&m_saved), sizeof(m_saved));
	_stream.write(reinterpret_cast<char*>(&m_timer), sizeof(m_timer));


	int count = m_warriors.size();
	_stream.write(reinterpret_cast<char*>(&count), sizeof(count));
	for (int i = 0; i < count; i++) {
		m_warriors[i]->Serialize(_stream);
		m_rocks[i]->Serialize(_stream);
		_stream.write(reinterpret_cast<char*>(&m_speeds[i]), sizeof(m_speeds[i]));
		_stream.write(reinterpret_cast<char*>(&m_rockSpeeds[i]), sizeof(m_rockSpeeds[i]));
		char byte = m_dead[i] ? 1 : 0;
		
		_stream.write(&byte, sizeof(byte));
	}

	BaseLevel::Serialize(_stream);
}

void Level_2::Deserialize(std::istream& _stream) {

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

		m_rock = SpriteSheet::Pool->GetResource();
		m_rock->Deserialize(_stream);
		m_rocks.push_back(m_rock);

		int sp;
		_stream.read(reinterpret_cast<char*>(&sp), sizeof(sp));
		m_speeds.push_back(sp);
		_stream.read(reinterpret_cast<char*>(&sp), sizeof(sp));
		m_rockSpeeds.push_back(sp);
		bool d;
		_stream.read(reinterpret_cast<char*>(&d), sizeof(d));

	}
	BaseLevel::Deserialize(_stream);
}


void Level_2::ToString() {
	cout << "LEVEL" << endl;

	BaseLevel::ToString();
}
