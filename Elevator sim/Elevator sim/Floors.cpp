#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <random>
#include "Floors.h"
#include "Elevator.h"
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

	humans_on_floors[Floor].push_back(human_S_Create(Destination, Human_id_count,Floor, Floor_posX(Floor), Floor_posY(Floor)-120));
	Human_id_count++;
	/*
	int n = humans_on_floors[Floor].size();
	humans_on_floors[Floor][humans_on_floors[Floor].size() - 1];
	*/
	
}

void add_human_to_floor(Human human)
{
	humans_on_floors[human.Destination].push_back(human);
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
				if (humans_on_floors[current_floor][current_human].Floor % 2 == 0)
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
				RECT humanRect = { humans_on_floors[current_floor][current_human].position[0] + 10, humans_on_floors[current_floor][current_human].position[1], humans_on_floors[current_floor][current_human].position[0] + 55, humans_on_floors[current_floor][current_human].position[1] + 75 };
				InvalidateRect(hwnd, &humanRect, TRUE);
			}
			else if (humans_on_floors[current_floor][current_human].State == 1);
			else if (humans_on_floors[current_floor][current_human].State == 2)
			{
				if (humans_on_floors[current_floor][current_human].Floor % 2 == 0)
				{
					humans_on_floors[current_floor][current_human].position[0] += 5;
					if (humans_on_floors[current_floor][current_human].position[0] >= humans_on_floors[current_floor][current_human].postionDesination)
					{
						humans_on_floors[current_floor][current_human].State = 3;
						Add_human_to_elavator(humans_on_floors[current_floor][current_human]);
						if (current_human >= 0 && current_human < humans_on_floors[current_floor].size())
						{
							humans_on_floors[current_floor].erase(humans_on_floors[current_floor].begin() + current_human);
						}
					}
				}
				else
				{
					humans_on_floors[current_floor][current_human].position[0] -= 5;
					if (humans_on_floors[current_floor][current_human].position[0] <= humans_on_floors[current_floor][current_human].postionDesination)
					{
						humans_on_floors[current_floor][current_human].State = 3;
						Add_human_to_elavator(humans_on_floors[current_floor][current_human]);
						if (current_human >= 0 && current_human < humans_on_floors[current_floor].size()) 
						{
							humans_on_floors[current_floor].erase(humans_on_floors[current_floor].begin() + current_human);
						}
					}
				}
			}
			else if (humans_on_floors[current_floor][current_human].State == 4)
			{
				if (humans_on_floors[current_floor][current_human].Destination % 2 == 0)
				{
					humans_on_floors[current_floor][current_human].position[1] -= 5;
					if (humans_on_floors[current_floor][current_human].position[1] < 10)
					{
						if (current_human >= 0 && current_human < humans_on_floors[current_floor].size())
						{
							humans_on_floors[current_floor].erase(humans_on_floors[current_floor].begin() + current_human);
						}
					}
				}
				else
				{
					humans_on_floors[current_floor][current_human].position[1] += 5;
					if (humans_on_floors[current_floor][current_human].position[1] > 800)
					{
						if (current_human >= 0 && current_human < humans_on_floors[current_floor].size())
						{
							humans_on_floors[current_floor].erase(humans_on_floors[current_floor].begin() + current_human);
						}
					}
				}
			}
		}
	}
}

bool isSomeoneOnTheFloor(int Floor)
{
	return (humans_on_floors[Floor].size() > 0) ? true : false;
}

bool isSomeoneGoingToTheElavator()
{
	for (int current_floor = 0; current_floor < 5; current_floor++)
	{
		for (int current_human = 0; current_human < humans_on_floors[current_floor].size(); current_human++)
		{
			if (humans_on_floors[current_floor][current_human].State == 2)
			{
				return true;
			}
		}
	}
	return false;
}

void CheckDestination(int current_floor, bool updown)
{
	for (int current_human = 0; current_human < humans_on_floors[current_floor].size(); current_human++)
	{
		if (updown == true)
		{
			if (humans_on_floors[current_floor][current_human].Destination > current_floor)
			{
				humans_on_floors[current_floor][current_human].State = 2;
			}
		}
		else
		{
			if (humans_on_floors[current_floor][current_human].Destination < current_floor)
			{
				humans_on_floors[current_floor][current_human].State = 2;
			}
		}
	}
}
int LookForDestination(int currentElevatorFloor, bool updown)
{
	bool destination_for_up = false;
	bool destination_for_down = false;
	for (int current_floor = 0; current_floor < 5; current_floor++)
	{
		for (int current_human = 0; current_human < humans_on_floors[current_floor].size(); current_human++)
		{
			if (humans_on_floors[current_floor][current_human].Destination > currentElevatorFloor && humans_on_floors[current_floor][current_human].Floor >= currentElevatorFloor)
				destination_for_up = true;
			else if (humans_on_floors[current_floor][current_human].Destination < currentElevatorFloor && humans_on_floors[current_floor][current_human].Floor <= currentElevatorFloor)
				destination_for_down = true;
		}
	}
	if (destination_for_up == true)
		return 1;
	else if (destination_for_down == true)
		return 2;
	else
		return 0;
}