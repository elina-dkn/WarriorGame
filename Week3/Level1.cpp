#include "Level1.h"
#include "Renderer.h"


Level1::Level1() {
	m_gameTime = 0;
	SpriteSheet::Pool = new ObjectPool<SpriteSheet>();
	SpriteAnim::Pool = new ObjectPool<SpriteAnim>();
	m_warrior = SpriteSheet::Pool->GetResource();
	
}

Level1::~Level1() {
	delete SpriteAnim::Pool;
	delete SpriteSheet::Pool;

}

void Level1::AssignNonDefaultValues() {
	m_warrior->Load("../Assets/Textures/Warrior.tga");
	m_warrior->SetSize(17, 6, 69, 44);
	m_warrior->AddAnimation(EN_AN_IDLE, 0, 6, 0.0f);
	m_warrior->AddAnimation(EN_AN_RUN, 6, 8, 4.0f);

	Level::AssignNonDefaultValues();
}

void Level1::Render() {
	
}

void Level1::Serialize(std::ostream& _stream) {
	m_warrior->Serialize(_stream);

	Level::Serialize(_stream);
}

void Level1::Deserialize(std::istream& _stream) {
	m_warrior->Deserialize(_stream);
	Level::Deserialize(_stream);
}


void Level1::ToString() {
	cout << "LEVEL" << endl;
	
	Level::ToString();
}
