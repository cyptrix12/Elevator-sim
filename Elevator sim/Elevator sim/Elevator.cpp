#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include "Draw.h"
#include "Elevator.h"
#include "Floors.h"
#include "Humans.h"




std::vector<int>Elev_vect;
std::vector<Human> humans_in_elavator;

Elavator elevator;

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
	if (updown == true)
	{
		posY -= 5;
		for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
		{
			humans_in_elavator[current_human].position[1] -= 5;
		}
	}
	else
	{
		posY += 5;
		for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
		{
			humans_in_elavator[current_human].position[1] += 5;
		}
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
	int current_floor = -1;
	elevator.stop = false;
	for (int i = 0; i < 5; i++)
	{
		if (posY == Floor_posY(i))
		{
			elevator.stop = true;
			current_floor = i;
		}
	}
	
	if (elevator.stop == false)
	{
		UpdateElevatorPosition(hwnd, elevator.updown);
		return;
	}
	else // od tego miejsca rob co uwazasz za sluszne. imo bedzie trzeba wyjebac elevator.destination bo useless sie wydaje
	{

		/*
		1. sprawdzic ludzi w windzie czy ktos juz wysiada + czy dalej ktos chce jechac w tym kierunku
		2. sprawdzic czy ktos jest na pietrze kto powinien wsiasc
		3. sprawdzic czy ktos jest dalej w danym kierunku na kolejnych pietrach kto by chcial w danym kierunku
		4. czy ktos jest w danym kierunku ale by chcial w drugi kierunek
		5. czy jest ktos w zlym kierunku 
		*/
		if (isSomeoneGettingOut() == true)
		{
			return;
		}
		if (humans_in_elavator.size() != 0)
		{
			for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
			{
				if (humans_in_elavator[current_human].Destination == current_floor)
				{
					humans_in_elavator[current_human].State = 4;
					add_human_to_floor(humans_in_elavator[current_human]);
					if (current_human >= 0 && current_human < humans_in_elavator.size())
					{
						humans_in_elavator.erase(humans_in_elavator.begin() + current_human);
					}
				}
			}
			// tera znowu wywolac tego fora i sprawdzic czy ktos dalej chce jechac w tym kierunku. mozna do tego zrobic osobna bool funkcje
		}
		
		if (isSomeoneOnTheFloor(current_floor) == true)
		{
			//tego ifa raczej wyjebac calkowicie i zostawic samo CheckDestination
			if(current_floor != elevator.Destination)
			{
				CheckDestination(current_floor, elevator.updown); // 
			}
			else
			{
				//????
				//Destination = -1;????
			}
		}
		else 
		{
			//ta funkcja LookForDestination do przeksztalcenia jest lekkiego ale zamysl imo git
			int destination_buffer = LookForDestination(current_floor, elevator.updown);
			switch (destination_buffer)
			{
			case 0:
				return;
			case 1:
				elevator.updown = true;
				UpdateElevatorPosition(hwnd, elevator.updown);
				return;
			case 2:
				elevator.updown = false;
				UpdateElevatorPosition(hwnd, elevator.updown);
				return;
			}
		}

		//1. czy ktos jest na pietrze
		//	jesli tak to:
		//	jesli chce jechac w dobrym kierunku to po pierwsze sprawdzic czy poszerza on destination a po drugie dodac go do windy
		//  jesli nie chce w dobrym kierunku to wyjebane 
		//2. czy ktos jest w windzie kto chce wysiasc na tym pietrze
		//

		if (isSomeoneGoingToTheElavator() == true)
		{
			return;
		}
		else
		{
			elevator.stop = false;
			UpdateElevatorPosition(hwnd, elevator.updown);
			return;
		}
		if (humans_in_elavator.size() == 0)
		{
			elevator.stop = false;
		}
	}
}

void DrawPoepleInElevator(HDC hdc)
{
	for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
	{
		DrawHuman(hdc, humans_in_elavator[current_human]);
	}
}