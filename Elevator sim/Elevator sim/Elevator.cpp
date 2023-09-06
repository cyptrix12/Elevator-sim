#include <Windows.h>
#include "Elevator.h"
#include "Draw.h"
#include <gdiplus.h>
#include <vector>


Request CreateRequest(int, int);
std::vector<int>Elev_vect;


void DrawElevator (HDC hdc){
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::Rect rectangle(800 / 3 + 3, posY - (600/5) , 260, 600 / 5);

	gf.DrawRectangle(&pen, rectangle);
}

void UpdateElevatorPosition(HWND hwnd, bool updown)
{
	RECT rectangleS = { 800 / 3 + 3, posY - (600 / 5) -5  , (800 / 3) + 3 + 261, posY + 6};
	InvalidateRect(hwnd, &rectangleS, TRUE);
	if (updown == false)
	{
		posY -= 5;
	}
	else
	{
		posY += 5;
	}
	
	InvalidateRect(hwnd, &rectangleS, TRUE);
}

int ElevatorPosition()
{
	return posY;
}

bool isElevHigher(int Floor_height)
{
	if (posY > Floor_height)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ElevatorOpen(int current_Floor)
{
	/*
	TODO:
	1. sprawdzic czy w windzie jest ktos kto tu chce wysiasc
	2. sprawdzic czy na tym pietrze jest ktos kto chce wsiasc w danym kierunku
	*/

	for (auto it = Elev_vect.begin(); it != Elev_vect.end(); ++it) {
		if (*it == current_Floor) {

			//tutaj funkcja zeby te ludki powychodzily
			
			it = Elev_vect.erase(it); 
			if (it != Elev_vect.begin()) {
				--it;
			}
		}
	}
}

Request CreateRequest(int button_floor, int button_destination)
{
	Request request;
	request.DestinationFloor = button_destination;
	request.RequestFloor = button_floor;
	return request;
}
