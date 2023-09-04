#pragma once
#include <Windows.h>
#include<vector>

struct Request {};
std::vector<int>Elev_vect;
void DrawElevator(HDC hdc);
void UpdateElevatorPosition(bool updown);
int ElevatorPosition();
bool isElevHigher(int Floor_height);
bool ElevatorOpen(int current_Floor);


static int posY = 590;
