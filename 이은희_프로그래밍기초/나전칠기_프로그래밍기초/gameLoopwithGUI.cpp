// @brief  ����ĥ�� ���α׷��� ���� ������
#include "INC_Windows.h"
#include "GameTimer.h"
#include "GeoShapeManager.h"
#include <iostream>

namespace
{
	// @breif  ������ ���ν���
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_CREATE:
		{
			std::cout << "WM_CREATE" << std::endl;
		}break;

		case WM_CLOSE:
		{
			std::cout << "WM_CLOSE" << std::endl;

			PostQuitMessage(0); // WM_QUIT
		}break;
		default:
			return::DefWindowProc(hwnd, msg, wparam, lparam);
		}
		return NULL;
	} //������ ���ν��� ����
	//�ϴ� �ʿ��Ѱ͸� �����ϰ� �������� �⺻���� ����.
	//return Null �� ����ó������

	// @breif  ������ Ŭ���� ���
	HWND CreateWidow(const wchar_t* className, const wchar_t* windowName, int width, int height)
	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = className;
		wc.lpfnWndProc = WndProc; // ������ ���ν���(�Լ�)�� ������ ���


		ATOM classId = 0;
		if (!GetClassInfoEx(HINSTANCE(), L"NzWindowClass", &wc))
		{
			classId = RegisterClassEx(&wc);

			if (0 == classId) return NULL;
		}
		//NzWindowClass �̸��� ���� Ŭ������ �̹� �ִ��� üũ
		//������ �� Ŭ���� ���
		//������ Return ��ȯ

		RECT rc = { 0, 0, width, height };
		//�簢�� ����ü

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

	void GameInit(HWND hWnd)
	{
		RECT rcClient = {};
		GetClientRect(hWnd, &rcClient);

		const int circleRadius = 50;
		const int& clientWidth = rcClient.right - rcClient.left;
		const int& clientHeight = rcClient.bottom - rcClient.top;

		simplegeo::g_GeoShapeManager.AddCircle(clientWidth / 2, clientHeight / 2, circleRadius, RGB(0, 0, 255));
	}

	void GameUpdate(float deltaTime)
	{
		static float acculatedTime = 0;

		acculatedTime += deltaTime;

		if (acculatedTime < 1000.0) return;

		acculatedTime -= 1000.0;
		//���� ������ ������ ���� �ʱ� �ڵ�
	}

	void GameRender(HWND hWnd)
	{
		HDC hDC = GetDC(hWnd);

		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		FillRect(hDC, &clientRect, (HBRUSH)(COLOR_WINDOW + 1)); //������� ä���

		simplegeo::g_GeoShapeManager.Draw(hDC); // �׸���

		ReleaseDC(hWnd, hDC);
	}

	void GameLoop(HWND hWnd)
	{
		GameTimer timer;
		timer.Reset();

		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, HWND(), 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				///HERE: GAME LOGIC UPATE & RENDERING
				timer.Tick();
				GameUpdate(timer.DeltaTimeMS());
				GameRender(hWnd);
			}
		}
	}
}//namespace

int main()
{
	HWND hWnd = CreateWidow(L"NzWindowClass", L"���ϳ�", 1280, 720);

	if (NULL == hWnd)
	{
		std::cout << "������ ���� ����" << std::endl;
		system("pause");
		return -1;
	}

	GameInit(hWnd);

	GameLoop(hWnd);

	DestroyWindow(hWnd);

	return 0;

}