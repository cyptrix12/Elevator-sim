#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include "Draw.h"
#include "Humans.h"
#include "Elevator.h"
#include <vector>

std::vector<Human> human_vect;

Human human_S_Create(int Destination, int ID, int position_x, int position_y)
{
	Human human;
	human.Destination = Destination;
	human.ID = ID;
	human.position[0] = position_x;
	human.position[1] = position_y + 54;
	return human;
}

void DrawHuman(HDC hdc, Human human) {
	Gdiplus::Graphics gf(hdc);
	Gdiplus::SolidBrush redBrush(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::Font strFont(L"Arial", 13);
	Gdiplus::Bitmap stickman(L"stickman.png");
	Gdiplus::PointF origin((float)human.position[0]+25, (float)human.position[1] + 20);
	
	Gdiplus::Rect stickman_scale(human.position[0], human.position[1], stickman.GetWidth() / 6, stickman.GetHeight() / 6);
	gf.DrawImage(&stickman, stickman_scale);
	gf.DrawString((WCHAR*)std::to_string(human.Destination).c_str(), -1, &strFont, origin, &redBrush);
}