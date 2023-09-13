#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include "Draw.h"
#include "Elevator.h"
#include "Floors.h"
#include "Humans.h"


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
		if (posY <= 110)
			elevator.updown = false;
		posY -= 5;
		for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
		{
			humans_in_elavator[current_human].position[1] -= 5;
		}
	}
	else
	{
		if (posY >= 590)
			elevator.updown = true;
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
	if (humans_in_elavator.size() > 7)
	{
		if (isSomeoneGoingToTheElavator() == true)
		{
			return;
		}
		ElevatorDrop(hwnd);
		return;
	}

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
	else 
	{

		/*
		1. sprawdzic ludzi w windzie czy ktos juz wysiada + czy dalej ktos chce jechac w tym kierunku
		2. sprawdzic czy ktos jest na pietrze kto powinien wsiasc
		3. sprawdzic czy ktos jest dalej w danym kierunku na kolejnych pietrach kto by chcial w danym kierunku
		4. czy ktos jest w danym kierunku ale by chcial w drugi kierunek
		5. czy jest ktos w zlym kierunku 
		*/
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
						current_human--;
					}
					UpdateMassCounter(hwnd);
				}
			}
		}
		if (isSomeoneGettingOut() == true)
		{
			return;
		}
		
		if (isSomeoneOnTheFloor(current_floor) == true)
		{
				CheckDestination(current_floor, elevator.updown); // 
		}
		else 
		{
			if (humans_in_elavator.size() != 0)
			{
				UpdateElevatorPosition(hwnd, elevator.updown);
				return;
			}
			int destination_buffer = LookForDestination(current_floor, elevator.updown);
			switch (destination_buffer)
			{
			case 0:
				//looking for destination
				return;
			case 1:
				elevator.updown = true;
				UpdateElevatorPosition(hwnd, elevator.updown);
				return;
			case 2:
				elevator.updown = false;
				UpdateElevatorPosition(hwnd, elevator.updown);
				return;
			case 3:
				elevator.updown = false;
				UpdateElevatorPosition(hwnd, elevator.updown);
			case 4:
				elevator.updown = true;
				UpdateElevatorPosition(hwnd, elevator.updown);

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

bool IsThereAPlace()
{
	return (humans_in_elavator.size() >= 8) ? false : true;
}

void DrawMassCounter(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0));
	Gdiplus::Font strFont(L"Arial", 13, 1);
	Gdiplus::PointF elevatorPanelOrigin(400, 5);
	Gdiplus::StringFormat stringFormat;

	stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);

	Gdiplus::PointF kgPanelOrigin(700, 5);
	gf.DrawString((WCHAR*)(std::to_wstring(humans_in_elavator.size() * 70) + L" kg").c_str(), -1, &strFont, kgPanelOrigin, &stringFormat, &blackBrush);

}

void UpdateMassCounter(HWND hwnd)
{
	RECT rectangleS = { 800 / 3 + 3, posY - (600 / 5) - 5  , (800 / 3) + 3 + 261, posY + 6 };
	rectangleS = { 600, 0 , 800, 50 };
	InvalidateRect(hwnd, &rectangleS, TRUE);
}

void ElevatorDrop(HWND hwnd)
{
	RECT rectangleS = { 800 / 3 + 3, posY - (600 / 5) - 5  , (800 / 3) + 3 + 261, posY + 6 };
	InvalidateRect(hwnd, &rectangleS, TRUE);
	posY += 10;
	for (int current_human = 0; current_human < humans_in_elavator.size(); current_human++)
	{
		humans_in_elavator[current_human].position[1] += 10;
	}
	rectangleS = { 800 / 3 + 3, posY - (600 / 5) - 5  , (800 / 3) + 3 + 261, posY + 6 };
	InvalidateRect(hwnd, &rectangleS, TRUE);
}