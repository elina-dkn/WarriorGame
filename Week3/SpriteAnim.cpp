#include "SpriteAnim.h"

ObjectPool<SpriteAnim>* SpriteAnim::Pool = nullptr;

SpriteAnim::SpriteAnim() {
	ClearMemory();
}

SpriteAnim::~SpriteAnim() {}

void SpriteAnim::Create(short _clipStart, short _clipCount, float _clipSpeed) {
	m_clipStart = _clipStart;
	m_clipCount = _clipCount;
	m_clipSpeed = _clipSpeed;
	m_clipCurrent = _clipStart;
	m_clipEnd = m_clipStart + m_clipCount;
}

void SpriteAnim::ClearMemory() {
	m_clipStart = 0;
	m_clipCount = 0;
	m_clipCurrent = 0;
}

void SpriteAnim::Update() {
	m_clipCurrent += m_clipSpeed;
	if (m_clipCurrent > m_clipEnd) {
		m_clipCurrent = m_clipStart;
	}
}

void SpriteAnim::Serialize(std::ostream& _stream) {
	_stream.write(reinterpret_cast<char*>(&m_clipStart), sizeof(m_clipStart));
	_stream.write(reinterpret_cast<char*>(&m_clipCount), sizeof(m_clipCount));
	_stream.write(reinterpret_cast<char*>(&m_clipSpeed), sizeof(m_clipSpeed));
	_stream.write(reinterpret_cast<char*>(&m_clipCurrent), sizeof(m_clipCurrent));
	Resource::Serialize(_stream);
}

void SpriteAnim::Deserialize(std::istream& _stream) {
	_stream.read(reinterpret_cast<char*>(&m_clipStart), sizeof(m_clipStart));
	_stream.read(reinterpret_cast<char*>(&m_clipCount), sizeof(m_clipCount));
	_stream.read(reinterpret_cast<char*>(&m_clipSpeed), sizeof(m_clipSpeed));
	_stream.read(reinterpret_cast<char*>(&m_clipCurrent), sizeof(m_clipCurrent));
	m_clipEnd = m_clipCount + m_clipStart;

	Resource::Deserialize(_stream);
}

void SpriteAnim::ToString() {
	cout << "SPRITE ANIMATION" << endl;
	cout << "Clip Start: " << m_clipStart;
	cout << "Clip Count: " << m_clipCount << endl;
	Resource::ToString();
}