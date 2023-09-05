#pragma once
#include <Windows.h>
#include<vector>

struct Request {
	int RequestFloor;
	int DestinationFloor;
};

void DrawElevator(HDC hdc);
void UpdateElevatorPosition(bool updown);
int ElevatorPosition();
bool isElevHigher(int Floor_height);
void ElevatorOpen(int current_Floor);


static int posY = 590;
