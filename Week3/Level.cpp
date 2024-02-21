#include "Level.h"


Level::Level() {
	AssetController::Instance().Initialize(10000000);


}

Level::~Level() {

	AssetController::Instance().Clear();
}

void Level::AssignNonDefaultValues() {

	Resource::AssignNonDefaultValues();
}

void Level::Serialize(std::ostream& _stream) {
	
	
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	

	
	Resource::Deserialize(_stream);
}

void Level::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}

void Level::Render() {

}
