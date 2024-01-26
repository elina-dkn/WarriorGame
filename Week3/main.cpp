// Week3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "FileController.h"
#include "StackAllocator.h"
#include "ObjectPool.h"
#include "Resource.h"

int main()
{
	Resource::Pool = new ObjectPool<Resource>();
	Resource* r1 = Resource::Pool->GetResource();
	r1->AssignNonDefaultValues();

	ofstream writeSttream("resource.bin", ios::out | ios::binary);
	r1->Serialize(writeSttream);
	writeSttream.close();
	cout << "r1 values: ";
	r1->ToString();


	Resource* r2 = Resource::Pool->GetResource();
	ifstream readSttream("resource.bin", ios::in | ios::binary);
	r2->Deserialize(readSttream);
	readSttream.close();
	cout << "r2 values: ";
	r2->ToString();

	delete Resource::Pool;
}
