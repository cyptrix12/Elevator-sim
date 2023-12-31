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
	int Destination = -1;
	bool updown = true;
	bool stop;

};

void DrawElevator(HDC hdc);
void UpdateElevatorPosition(HWND hwnd, bool updown);
int ElevatorPosition();
bool isElevHigher(int Floor);
void Add_human_to_elavator(Human human);
void Elavator_logic(HWND hwnd);
void DrawPoepleInElevator(HDC hdc);
void DrawMassCounter(HDC hdc);
void UpdateMassCounter(HWND hwnd);
void ElevatorDrop(HWND hwnd);