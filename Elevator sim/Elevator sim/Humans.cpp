#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include "Draw.h"
#include "Humans.h"
#include "Elevator.h"
#include <vector>

std::vector<Human> human_vect;

Human human_S_Create(int Destination, int ID,int Floor, int position_x, int position_y)
{
	Human human;
	human.Destination = Destination;
	human.ID = ID;
	human.Floor = Floor;
	human.position[0] = position_x;
	human.position[1] = position_y + 48;
	return human;
}

void DrawHuman(HDC hdc, Human human) {
	Gdiplus::Graphics gf(hdc);
	Gdiplus::SolidBrush redBrush(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::Font strFont(L"Arial", 14);
	Gdiplus::Bitmap stickman(L"stickman_v3_b.png");
	Gdiplus::PointF origin((float)human.position[0]+21, (float)human.position[1]+30);
	
	//Gdiplus::Rect stickman_scale(human.position[0], human.position[1], stickman.GetWidth() / 6, stickman.GetHeight() / 6);
	gf.DrawImage(&stickman, human.position[0], human.position[1]);
	gf.DrawString((WCHAR*)std::to_string(human.Destination).c_str(), -1, &strFont, origin, &redBrush);
}