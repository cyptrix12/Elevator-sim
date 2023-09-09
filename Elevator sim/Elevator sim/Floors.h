#pragma once
#include <Windows.h>
#include<vector>
#include "Humans.h"

void Floor_Draw(HDC hdc);

int Floor_posY(int Floor);

void Create_human(int Floor, int Destination);

void Draw_humans_on_floors(HDC hdc);

void CheckHumanStateFloors(HWND hwnd);

bool isSomeoneOnTheFloor(int Floor);

void CheckDestination(int current_floor, bool updown);