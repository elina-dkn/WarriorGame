#include "Level.h"


Level::Level() {
	AssetController::Instance().Initialize(10000000);
	Unit::Pool = new ObjectPool<Unit>();
	SoundEffect::Pool = new ObjectPool<SoundEffect>();

	m_mapSizeX = 0;
	m_mapSizeY = 0;
	m_gameTime = 0.0f;
	m_unit = nullptr;

}

Level::~Level() {
	delete SoundEffect::Pool;
	delete Unit::Pool;
	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {
	m_mapSizeX = 128;
	m_mapSizeY = 256;
	m_gameTime = 101.5f;
	m_unit = Unit::Pool->GetResource();
	m_unit->AssignNonDefaultValues();
	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {




	SerializePointer(_stream, m_unit);
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	DeserializePointer(_stream, m_unit);
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "UNIT" << endl;
	m_soundEffect->ToString();
	Resource::ToString();
}
