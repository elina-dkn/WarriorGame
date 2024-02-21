#include "BaseLevel.h"



BaseLevel::BaseLevel() {
	AssetController::Instance().Initialize(10000000);
	r = &Renderer::Instance();
	t = &Timing::Instance();
	font = new TTFont();
	font->Initialize(20);
	m_gameTime = 0;


}

BaseLevel::~BaseLevel() {
	delete font;
	AssetController::Instance().Clear();
}

void BaseLevel::AssignNonDefaultValues() {

	Resource::AssignNonDefaultValues();
}

void BaseLevel::Serialize(std::ostream& _stream) {

	_stream.write(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	
	Resource::Serialize(_stream);
}

void BaseLevel::Deserialize(std::istream& _stream) {

	_stream.read(reinterpret_cast<char*>(&m_gameTime), sizeof(m_gameTime));
	
	Resource::Deserialize(_stream);
}

void BaseLevel::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}





