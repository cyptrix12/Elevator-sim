#pragma once
#include <Windows.h>
#include<vector>
#include "Humans.h"

struct Request {
	int RequestFloor;
	int DestinationFloor;
};

struct Elavator
{
	int Destination;
	bool updown;
	bool stop;

};

void DrawElevator(HDC hdc);
void UpdateElevatorPosition(HWND hwnd, bool updown);
int ElevatorPosition();
bool isElevHigher(int Floor_height);
void ElevatorOpen(int current_Floor);
void CheckHumanStateElvator();
void Add_human_to_elavator(Human human);
