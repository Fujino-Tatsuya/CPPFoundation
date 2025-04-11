#include <Windows.h>
#include <iostream>

namespace //�͸���ӽ����̽�
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
		
	{
		switch (msg)
		{
		case WM_CREATE: //WM: window Massage
		{
			std::cout << "WM_CREATE" << std::endl;
		}break;

		case WM_CLOSE:
		{
			std::cout << "WM_CLOSE" << std::endl;
			// �����츦 �����ϱ� ���� �޽���
			PostQuitMessage(0); // WM_QUIT
		}break;
		default:
			return::DefWindowProc(hwnd, msg, wparam, lparam);
		}
		return NULL;
	}

	HWND CreateWidow(const wchar_t* className, const wchar_t* windowName, int width, int height)
		

	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = className;
		wc.lpfnWndProc = WndProc; // ������ ���ν���(�Լ�)�� ������ ���
		wc.lpfnWndProc = &WndProc; // �����̶� ����, ��� �Լ��� �ٸ���


		ATOM classId = 0;
		if (!GetClassInfoEx(HINSTANCE(), L"NzWindowClass", &wc))
		{
			classId = RegisterClassEx(&wc); // ���� ���� Ŭ���� ������ ������ �ü������ '������ �������' �ϳ� �������
			//RegisterClassEx(WNDCLASSEX): ������ ��� ������ ä���� ID �����޶�� ��û�ϴ� �Լ�

			if (0 == classId) return NULL;
		}

		RECT rc = { 0, 0, width, height };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false); // Ŭ���̾�Ʈ ũ�⿡ ������ �� ���̱�?

		std::cout << "width: " << rc.right - rc.left << " height: " << rc.bottom - rc.top << std::endl; // â ũ�� ������ ���

		// �غ�� WNDCLASSEX wc �� �ü���� ����� classID�� ���� ������(Ŀ��) ��ü ���� ��û
		// ������ �ڵ� �޾ƿ���
		HWND hWnd = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, HWND(), HMENU(), HINSTANCE(), NULL);

		if (NULL == hWnd) return (HWND)(NULL); //�� ������ٸ� false

		::SetWindowText((HWND)hWnd, windowName); // ������ â�� �̸� ����

		ShowWindow((HWND)hWnd, SW_SHOW); // ������ ������
		UpdateWindow((HWND)hWnd); // ���� �ִ°� ��������

		return hWnd;
	}
	
	void GameLoop()
	{
		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, HWND(), 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); //���� A, key A ����
				DispatchMessage(&msg);
			}
			else
			{
				///HERE: GAME LOGIC UPATE & RENDERING
			}
		}
	}
}

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