#include <Windows.h>
#include "Elevator.h"
#include "Draw.h"
#include <gdiplus.h>

void DrawElevator (HDC hdc){
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));

	
	Gdiplus::Rect rectangle(800 / 3 + 3, posY - (600/5) , 260, 600 / 5);

	gf.DrawRectangle(&pen, rectangle);
}

void UpdateElevatorPosition(bool updown)
{
	if (updown == false)
	{
		posY -= 5;
	}
	else
	{
		posY += 5;
	}
}

int ElevatorPosition()
{
	return posY;
}