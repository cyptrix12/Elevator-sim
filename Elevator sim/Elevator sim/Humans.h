#pragma once
#include <vector>

	struct Human {
		int Destination;
		int ID;
		int Floor;
		int position[2]; 
		int postionDesination;
		int State = 0;
		int weight = 70;
		/*
		0 - going to the line
		1 - waiting for the elevator
		2 - going to the elevator
		3 - going with elavator
		4 - going out of the elevator
		*/
	};
	Human human_S_Create(int Destination, int ID,int Floor, int postion_x, int position_y);
	void DrawHuman(HDC hdc, Human human);
	int getRandomNumber();
	


