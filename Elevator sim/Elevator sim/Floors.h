#pragma once
#include <Windows.h>
#include<vector>
#include "Humans.h"
#include "Elevator.h"

void Floor_Draw(HDC hdc);

int Floor_posY(int Floor);

void Create_human(int Floor, int Destination);

void add_human_to_floor(Human human);

void Draw_humans_on_floors(HDC hdc);

void CheckHumanStateFloors(HWND hwnd);

bool isSomeoneOnTheFloor(int Floor);

bool isSomeoneGoingToTheElavator();

void CheckDestination(int current_floor, bool updown);

int LookForDestination(int currentElevatorFloor, bool updown); // 1 - good destination 2 - down 0 - none

bool isSomeoneGettingOut();