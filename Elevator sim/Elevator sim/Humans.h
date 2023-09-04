#pragma once
#include <vector>

struct Human {
	int Destination;
	int ID;
	Gdiplus::Bitmap stickman();
	//jakos dopisac jego sprite'a
};
Human human_Create(int Destination, int ID);

std::vector<Human> human_vect;