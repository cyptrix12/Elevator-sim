#pragma once
#include <Windows.h>

void DrawElevator(HDC hdc);
void UpdateElevatorPosition(bool updown);
int ElevatorPosition();
bool isElevHigher(int Floor_height);


static int posY = 590;
