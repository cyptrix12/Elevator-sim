#include <windows.h>
#include <gdiplus.h>

LRESULT CALLBACK WindowProcessMassages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void draw(HDC hdc);

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

	CreateWindow(CLASS_NAME, "Elevator",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 640,
		nullptr, nullptr, nullptr, nullptr);

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

		draw(hdc);

		EndPaint(hwnd, &ps);
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