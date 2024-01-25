// Week3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "FileController.h"

int main()
{
	FileController* fc = &FileController::Instance();
	cout << fc->GetCurDirectory() << endl;
	int fs = fc->GetFileSize("FileController.cpp");
	unsigned char* buffer = new unsigned char[fs];
	if (fc->ReadFile("FileController.cpp", buffer, fs)) {
		cout << "File read operation successful." << endl;
	}
	delete[] buffer;
}
