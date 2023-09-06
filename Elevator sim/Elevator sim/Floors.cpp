#include <Windows.h>
#include <gdiplus.h>
#include "Floors.h"
#include <vector>
#include "Humans.h"

std::vector<Human> humans_on_floors[5];

const int Floor_count = 5;

static int Human_id_count = 1;

int Floor_posY(int Floor)
{
	int realFloor = 5 - Floor;
	return ((600 / 5)* realFloor - 10);
}

int Floor_posX(int Floor)
{
	return (Floor % 2 == 0) ? 20 : 700;
}

void Floor_Draw(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	for (int currentFloor = 0; currentFloor < Floor_count; currentFloor++)
	{
		
		if (currentFloor % 2 == 0)
		{
			
			gf.DrawLine(&pen, 0, Floor_posY(currentFloor), 800 / 3, Floor_posY(currentFloor));
		}
		else
		{
			gf.DrawLine(&pen, (800/3) * 2, Floor_posY(currentFloor), 800, Floor_posY(currentFloor));
		}
		
	}
}

void Create_human(int Floor, int Destination)
{

	humans_on_floors[Floor].push_back(human_S_Create(Destination, Human_id_count, Floor_posX(Floor), Floor_posY(Floor)-120));
	Human_id_count++;
	/*
	int n = humans_on_floors[Floor].size();
	humans_on_floors[Floor][humans_on_floors[Floor].size() - 1];
	*/
	
}

void Draw_humans_on_floors(HDC hdc)
{
	for (int current_floor = 0; current_floor < 5; current_floor++)
	{
		for (int current_human = 0; current_human < humans_on_floors[current_floor].size(); current_human++)
		{
			DrawHuman(hdc, humans_on_floors[current_floor][current_human]);
		}
	}
}

void CheckHumanStateFloors(HWND hwnd)
{
	for (int current_floor = 0; current_floor < 5; current_floor++)
	{
		for (int current_human = 0; current_human < humans_on_floors[current_floor].size(); current_human++)
		{
			if (humans_on_floors[current_floor][current_human].State == 0)
			{
				
				if (humans_on_floors[current_floor][current_human].position[0] < 800 / 2)
				{
					humans_on_floors[current_floor][current_human].position[0] += 5;
					if (humans_on_floors[current_floor][current_human].position[0] >= ((800 / 3 - 60) - 30 * current_human))
					{
						humans_on_floors[current_floor][current_human].State = 1;
					}
				}
				else
				{
					humans_on_floors[current_floor][current_human].position[0] -= 5;
					if (humans_on_floors[current_floor][current_human].position[0] <= (800 / 3 * 2 + 30 * current_human))
					{
						humans_on_floors[current_floor][current_human].State = 1;
					}
				}
				RECT humanRect = { humans_on_floors[current_floor][current_human].position[0], humans_on_floors[current_floor][current_human].position[1], humans_on_floors[current_floor][current_human].position[0] + 60, humans_on_floors[current_floor][current_human].position[1] + 75 };
				InvalidateRect(hwnd, &humanRect, TRUE);
			}
		}
	}
}
