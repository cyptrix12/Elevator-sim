#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include "Draw.h"
#include <string>
#include "Elevator.h"



LRESULT CALLBACK WindowProcessMassages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void draw(HDC hdc);
void ButtonsDraw(HWND hwnd, HINSTANCE instance);


//(600 / 5)* currentFloor - 10

const int timerID = 1;
const int FPS = 30;
const int Floors_Positions[5] = { 590,470,350,230,110 };
bool isMoving = false;
bool updown = false;
int TargetFloor = 0;
std::vector<int> Que;

#define ID_BUTTON1 1000
HWND hButton;




int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	const char* CLASS_NAME = "myWin32WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMassages;
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(CLASS_NAME, "Elevator",
		WS_SYSMENU| WS_VISIBLE | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 640,
		nullptr, nullptr, nullptr, nullptr);

	SetTimer(hwnd, timerID, 1000/FPS, NULL);
	// Create the button
	// Create the button
	/*
	hButton = CreateWindowExA(0, "BUTTON", "1",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 25, 25,
		hwnd, (HMENU)ID_BUTTON1, currentInstance, NULL);
		*/
	ButtonsDraw(hwnd, currentInstance);



	//hButton = CreateWindowExA(0, TEXT("BUTTON"), TEXT("chuj"),
		//WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		//100, 100, 50, 50, hwnd, (HMENU)1000, currentInstance, NULL);


	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

LRESULT CALLBACK WindowProcessMassages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		DrawMain(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_COMMAND:
		{int wmId = LOWORD(param);
		switch (wmId)
			{
			case 1004:
			case 1008:
			case 1012:
			case 1016:
			{
				isMoving = true;
				TargetFloor = 0;
				updown = isElevHigher(Floors_Positions[TargetFloor]);
				break;
			}
			case 1000:
			case 1009:
			case 1013:
			case 1017:
				isMoving = true;
				TargetFloor = 1;
				updown = isElevHigher(Floors_Positions[TargetFloor]);
				break;
			case 1001:
			case 1005:
			case 1014:
			case 1018:
				isMoving = true;
				TargetFloor = 2;
				updown = isElevHigher(Floors_Positions[TargetFloor]);
				break;
			case 1002:
			case 1006:
			case 1010:
			case 1019:
				isMoving = true;
				TargetFloor = 3;
				updown = isElevHigher(Floors_Positions[TargetFloor]);
				break;
			case 1003:
			case 1007:
			case 1011:
			case 1015:
				isMoving = true;
				TargetFloor = 4;
				updown = isElevHigher(Floors_Positions[TargetFloor]);
				break;
			}
			
		}
	case WM_TIMER:
		if (param == timerID)
		{
			
			if (isMoving == true) {
				if (ElevatorPosition() == Floors_Positions[TargetFloor])
				{
					isMoving = false;
				}
				else
				{
					UpdateElevatorPosition(updown);
					InvalidateRect(hwnd, NULL, FALSE); // Request a repaint
				}
			}
			
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}

void draw(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));
	Gdiplus::Bitmap stickman(L"stickman.png");
	Gdiplus::Rect stickman_scale(0, 0, stickman.GetWidth() / 10, stickman.GetHeight() / 10);
	
		//Rect compressionRect(210, 10, myBitmap.GetWidth() / 2,
			//myBitmap.GetHeight() / 2);

	gf.DrawImage(&stickman, stickman_scale);
	gf.DrawLine(&pen, 800 / 3, 0, 800 / 3 , 600);
	gf.DrawLine(&pen, 800 / 3 * 2, 0, 800 / 3 * 2, 600);
	gf.DrawLine(&pen, 0, 590, 800/3 ,590 );
	gf.DrawLine(&pen, 0, 600 / 5, 800 / 3 , 600 / 5);
	gf.DrawLine(&pen, 800, 600 / 5 *2, 800 / 3 * 2, 600 / 5 *2 );
	gf.DrawLine(&pen, 0, 600 / 5 * 3, 800 / 3 , 600 / 5 * 3);
	gf.DrawLine(&pen, 800, 600 / 5 * 4, 800 / 3 * 2, 600 / 5 * 4);
	//gf.DrawLine(&pen, 0, 0, screen_width(hwnd) / 3, 0);
	//gf.DrawLine(&pen, 0, 0, screen_width(hwnd) / 3, 0);
	//gf.DrawLine(&pen, 0, 0, screen_width(hwnd) / 3, 0);
	//gf.DrawLine(&pen, 0, 0, 500, 500);
	//gf.FillRectangle(&brush, 400, 200, 100, 100);
	//gf.DrawRectangle(&pen, 450, 400, 100, 150);

}

void ButtonsDraw(HWND hwnd, HINSTANCE instance)
{
	int button_x = 0;
	int button_y = 590-25;
	int button_size = 25;
	int button_ID = 1000;

	for (int currentFloor = 0; currentFloor < 5; currentFloor++)
	{
		if (currentFloor % 2 == 0)
		{
			button_x = 0;
		}
		else
		{
			button_x = 755;
		}
		for (int button_number = 0; button_number < 5; button_number++)
		{
			if (button_number == currentFloor)
			{
				continue;
			}
			hButton = CreateWindowExA(0, "BUTTON", std::to_string(button_number).c_str(),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				button_x, button_y, button_size, button_size,
				hwnd, (HMENU)button_ID, instance, NULL);
			button_ID++;
			button_y -= 25;
		}
		button_y -= 20;
	}
	/*
	for(; button_ID <1020; button_ID++)
	{
		if (button_ID % 4 == 0)
		{
			if(button_ID==1000)
			{
				button_y += 10;
			}
			else
			{
				button_y += 20;
			}
			left = !left;
			currentFloor--;
			if (left == true)
			{
				button_x = 0;
			}
			else
			{
				button_x = 755;
			}
		}
		int floorbutton = button_ID % 5;
		if (floorbutton == currentFloor)
		{
			floorbutton++;
		}
		hButton = CreateWindowExA(0, "BUTTON", std::to_string(floorbutton).c_str(),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			button_x, button_y, button_size, button_size,
			hwnd, (HMENU)button_ID, instance, NULL);
		button_y += 25;
	}
	*/

}