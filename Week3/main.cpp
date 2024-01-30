// Week3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Asset.h"
#include "AssetController.h"


int main()
{
	
	AssetController::Instance().Initialize(10000000);
	Asset* asset = AssetController::Instance().GetAsset("emoji.jpg");
	cout << "Bytes used by emoji.jpg: " << AssetController::Stack->GetBytesUsed() << endl;
}
