#pragma once
#include <vector>




	struct Human {
		int Destination;
		int ID;
		int position[2];
		//jakos dopisac jego sprite'a
	};
	Human human_S_Create(int Destination, int ID, int postion_x, int position_y);
	void DrawHuman(HDC hdc, Human human);
	
	


