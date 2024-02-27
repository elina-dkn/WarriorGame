#include "BaseLevel.h"



BaseLevel::BaseLevel() {


}

BaseLevel::~BaseLevel() {

}

void BaseLevel::AssignNonDefaultValues() {

	Resource::AssignNonDefaultValues();
}

void BaseLevel::Serialize(std::ostream& _stream) {
	
	Resource::Serialize(_stream);
}

void BaseLevel::Deserialize(std::istream& _stream) {
	
	Resource::Deserialize(_stream);
}

void BaseLevel::ToString() {
	cout << "LEVEL" << endl;
	Resource::ToString();
}





