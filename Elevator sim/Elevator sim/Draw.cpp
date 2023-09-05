#include <Windows.h>
#include "Draw.h"
#include "Elevator.h"
#include "Floors.h"
#include <gdiplus.h>
#include<vector>

void DrawMain(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));
	Gdiplus::Bitmap stickman(L"stickman.png");
	Gdiplus::Rect stickman_scale(0, 0, stickman.GetWidth() / 10, stickman.GetHeight() / 10);

	//Rect compressionRect(210, 10, myBitmap.GetWidth() / 2,
		//myBitmap.GetHeight() / 2);
	gf.Clear(Gdiplus::Color::White); // Clear the off-screen buffer

	//osG.DrawImage(&stickman, stickman_scale);
	/*
	gf.DrawLine(&pen, 800 / 3 * 2, 0, 800 / 3 * 2, 600);
	gf.DrawLine(&pen, 800 / 3, 0, 800 / 3, 600);
	gf.DrawLine(&pen, 0, 590, 800 / 3, 590);
	gf.DrawLine(&pen, 0, 600 / 5, 800 / 3, 600 / 5);
	gf.DrawLine(&pen, 800, 600 / 5 * 2, 800 / 3 * 2, 600 / 5 * 2);
	gf.DrawLine(&pen, 0, 600 / 5 * 3, 800 / 3, 600 / 5 * 3);
	gf.DrawLine(&pen, 800, 600 / 5 * 4, 800 / 3 * 2, 600 / 5 * 4);
	*/
	Floor_Draw(hdc);
	DrawElevator(hdc);
	Draw_humans_on_floors(hdc);
}