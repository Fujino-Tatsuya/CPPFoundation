#include <Windows.h>
#include <iostream>
#include "GeoShapeManager.h"

namespace
{
	using namespace std;

	class DebugConsole
	{
		DebugConsole(const DebugConsole&) = delete;
		DebugConsole& operator=(const DebugConsole&) = delete;
		DebugConsole(DebugConsole&&) = delete;
		DebugConsole& operator=(DebugConsole&&) = delete;
	public:
		DebugConsole()
		{
			AllocConsole();

			FILE* stream;
			freopen_s(&stream, "CONOUT$", "w", stdout);
			freopen_s(&stream, "CONIN$", "r", stdin);
		}

		~DebugConsole()
		{
			fclose(stdout);
			fclose(stdin);

			FreeConsole();
		}

		static void Show()
		{
			::ShowWindow(GetConsoleWindow(), SW_SHOW);
		}

		static void Hide()
		{
			::ShowWindow(GetConsoleWindow(), SW_HIDE);
		}

		static void SetTitle(const wchar_t* title)
		{
			::SetConsoleTitle(title);
		}

		static void ToggleShow()
		{
			HWND hwnd = GetConsoleWindow();
			if (hwnd)
			{
				if (::IsWindowVisible(hwnd))
				{
					Hide();
				}
				else
				{
					Show();
				}
			}
		}
	};

	DebugConsole g_debugConsole;

	// @breif  À©µµ¿ì ÇÁ·Î½ÃÀú
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_PAINT:
		{
			std::cout << "WM_PAINT" << std::endl;

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

			simplegeo::g_GeoShapeManager.Draw(hdc);

			EndPaint(hwnd, &ps);

		}break;

		case WM_LBUTTONDOWN:
		{
			std::cout << "WM_LBUTTONDBLCLK" << std::endl;
			// ¸¶¿ì½º ¿ÞÂÊ ¹öÆ° ´õºí Å¬¸¯
			// ÁÂÇ¥¸¦ °¡Á®¿Â´Ù.
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			int shape = Shape_CIRCLE;

			simplegeo::g_GeoShapeManager.FindEmpty();
			if (!simplegeo::g_GeoShapeManager.DetectGeo(x, y, shape)) //true Áö¿ò, flase °Å¸® ³» ¾øÀ½, Not ¿¬»êÀ¸·Î ¹ÝÀü
			{
				simplegeo::g_GeoShapeManager.AddCircle(x, y, 10, Shape_CIRCLE, RGB(255, 0, 0));
			}
			::InvalidateRect(hwnd, NULL, TRUE); //InvalidateRect È£­½Ã WM_PAINT ¸Þ¼¼Áö Àü´Þ
		}break;
		case WM_RBUTTONDOWN:
		{
			std::cout << "WM_RBUTTONDBLCLK" << std::endl;
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			int shape = Shape_RECTAGLE;

			simplegeo::g_GeoShapeManager.FindEmpty();
			if (!simplegeo::g_GeoShapeManager.DetectGeo(x, y, shape))
			{
				simplegeo::g_GeoShapeManager.AddRectangle(x, y, 10, Shape_RECTAGLE, RGB(0, 0, 255));
			}
			::InvalidateRect(hwnd, NULL, TRUE);

		}break;
		case WM_CREATE:
		{
			std::cout << "WM_CREATE" << std::endl;
		}break;

		case WM_CLOSE:
		{
			std::cout << "WM_CLOSE" << std::endl;
			// À©µµ¿ì¸¦ Á¾·áÇÏ±â À§ÇÑ ¸Þ½ÃÁö
			PostQuitMessage(0); // WM_QUIT
		}break;

		case WM_KEYDOWN:
		{
			if (wparam == 'C' || wparam == 'c')
			{
				DebugConsole::ToggleShow();
			}
		}break;
		default:
			return::DefWindowProc(hwnd, msg, wparam, lparam);
		}
		return NULL;
	}

	// @breif  À©µµ¿ì Å¬·¡½º µî·Ï
	HWND CreateWidow(const wchar_t* className, const wchar_t* windowName, int width, int height)
	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = className;
		wc.lpfnWndProc = WndProc; // À©µµ¿ì ÇÁ·Î½ÃÀú(ÇÔ¼ö)ÀÇ Æ÷ÀÎÅÍ µî·Ï
		wc.lpfnWndProc = &WndProc; // °°Àº ÀÇ¹Ì


		ATOM classId = 0;
		if (!GetClassInfoEx(HINSTANCE(), L"NzWindowClass", &wc))
		{
			classId = RegisterClassEx(&wc);

			if (0 == classId) return NULL;
		}

		RECT rc = { 0, 0, width, height };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		std::cout << "width: " << rc.right - rc.left << " height: " << rc.bottom - rc.top << std::endl;

		HWND hWnd = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, HWND(), HMENU(), HINSTANCE(), NULL);

		if (NULL == hWnd) return (HWND)(NULL);

		::SetWindowText((HWND)hWnd, windowName);

		ShowWindow((HWND)hWnd, SW_SHOW);
		UpdateWindow((HWND)hWnd);

		return hWnd;
	}

	void GameLoop()
	{
		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, HWND(), 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); //Å° ÀÔ·ÂÀ» char·Î º¯È¯ÇÑ´ë ±×·¸´ë
				DispatchMessage(&msg);
			}
			else
			{
				///HERE: GAME LOGIC UPATE & RENDERING
			}
		}
	}
}//namespace

int main()
{
	// GUI Ã¢ »ý¼º
	HWND hWnd = CreateWidow(L"NzWindowClass", L"³ªÀüÄ¥±â", 1280, 720);

	if (NULL == hWnd)
	{
		std::cout << "À©µµ¿ì »ý¼º ½ÇÆÐ" << std::endl;
		system("pause");
		return -1;
	}

	std::cout << "hWnd: " << hWnd << std::endl;
	//std::cout << (*hWnd).unused << std::endl; ·±Å¸ÀÓ ¿¡·¯!

	GameLoop();

	DestroyWindow(hWnd);

	return 0;

}