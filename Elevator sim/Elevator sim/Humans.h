#pragma once
#include <vector>




	struct Human {
		int Destination;
		int ID;
		int position[2];
		int State = 0;
		/*
		0 - going to the line
		1 - waiting for the elevator
		2 - going to the elevator
		3 - going with elavator
		4 - going out of the elevator
		*/
		//jakos dopisac jego sprite'a
	};
	Human human_S_Create(int Destination, int ID, int postion_x, int position_y);
	void DrawHuman(HDC hdc, Human human);
	
	


