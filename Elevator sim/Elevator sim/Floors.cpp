#include <Windows.h>
#include <gdiplus.h>
#include "Floors.h"
#include<vector>

void Floor_Draw(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	for (int currentFloor = 1; currentFloor <= Floor_count; currentFloor++)
	{
		int Floor_posY = (600 / Floor_count) * currentFloor - 10;
		if (currentFloor % 2 == 1)
		{
			
			gf.DrawLine(&pen, 0, Floor_posY, 800 / 3, Floor_posY);
		}
		else
		{
			gf.DrawLine(&pen, (800/3) * 2, Floor_posY, 800, Floor_posY);
		}
		
	}
}