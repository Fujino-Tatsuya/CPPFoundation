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

	// @breif  ������ ���ν���
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
			// ���콺 ���� ��ư ���� Ŭ��
			// ��ǥ�� �����´�.
			int x = LOWORD(lparam);
			int y = HIWORD(lparam);
			int shape = Shape_CIRCLE;

			simplegeo::g_GeoShapeManager.FindEmpty();
			if (!simplegeo::g_GeoShapeManager.DetectGeo(x, y, shape)) //true ����, flase �Ÿ� �� ����, Not �������� ����
			{
				simplegeo::g_GeoShapeManager.AddCircle(x, y, 10, Shape_CIRCLE, RGB(255, 0, 0));
			}
			::InvalidateRect(hwnd, NULL, TRUE); //InvalidateRect ȣ���� WM_PAINT �޼��� ����
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
			// �����츦 �����ϱ� ���� �޽���
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

	// @breif  ������ Ŭ���� ���
	HWND CreateWidow(const wchar_t* className, const wchar_t* windowName, int width, int height)
	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = className;
		wc.lpfnWndProc = WndProc; // ������ ���ν���(�Լ�)�� ������ ���
		wc.lpfnWndProc = &WndProc; // ���� �ǹ�


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
				TranslateMessage(&msg); //Ű �Է��� char�� ��ȯ�Ѵ� �׷���
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
	// GUI â ����
	HWND hWnd = CreateWidow(L"NzWindowClass", L"����ĥ��", 1280, 720);

	if (NULL == hWnd)
	{
		std::cout << "������ ���� ����" << std::endl;
		system("pause");
		return -1;
	}

	std::cout << "hWnd: " << hWnd << std::endl;
	//std::cout << (*hWnd).unused << std::endl; ��Ÿ�� ����!

	GameLoop();

	DestroyWindow(hWnd);

	return 0;

}