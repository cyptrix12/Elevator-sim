#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include "Draw.h"
#include "Humans.h"
#include <string>
#include "Elevator.h"
#include<vector>


Human human_Create(int Destination, int ID)
{
	Human human;
	human.Destination = Destination;
	human.ID = ID;
	return human;
}