#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include "Draw.h"
#include "Elevator.h"
#include "Floors.h"
#include "Humans.h"




std::vector<int>Elev_vect;
std::vector<Human> humans_in_elavator;

Elavator elavator;

static int posY = 590;


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

bool isElevHigher(int Floor)
{
	if (posY > Floor_posY(Floor))
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

void Add_human_to_elavator(Human human)
{
	humans_in_elavator.push_back(human);
}

void Elavator_logic(HWND hwnd)
{
	if (elavator.stop == true)
	{
		//sprawdz czy dalej powinna stac
		//return
	}   
	int current_floor = -1;
	for (int i = 0; i < 5; i++)
	{
		if (posY == Floor_posY(i))
		{
			elavator.stop = true;
			current_floor = i;
		}
	}
	if (elavator.stop == false)
	{
		UpdateElevatorPosition(hwnd, elavator.updown);
		return;
	}
	else
	{
		//1. czy ktos jest na pietrze
		//	jesli tak to:
		//	jesli chce jechac w dobrym kierunku to po pierwsze sprawdzic czy poszerza on destination a po drugie dodac go do windy
		//  jesli nie chce w dobrym kierunku to wyjebane 
		//2. czy ktos jest w windzie kto chce wysiasc na tym pietrze
		//

		if (isSomeoneOnTheFloor(current_floor) == true)
		{
			if(current_floor != elavator.Destination)
			{
				CheckDestination(current_floor, elavator.updown); // 
			}
			else
			{
				//????
				//Destination = -1;????
			}
		}
		if (humans_in_elavator.size() != 0)
		{
			for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
			{
				if (humans_in_elavator[current_human].Destination == current_floor)
				{
					humans_in_elavator[current_human].State = 4;
				}
			}
		}
		if (humans_in_elavator.size() == 0)
		{
			elavator.stop = false;
		}
	}
}