#include <Windows.h>
#include <iostream>

namespace //익명네임스페이스
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
			// 윈도우를 종료하기 위한 메시지
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
		wc.lpfnWndProc = WndProc; // 윈도우 프로시저(함수)의 포인터 등록
		wc.lpfnWndProc = &WndProc; // 윗줄이랑 같음, 멤버 함수는 다르대


		ATOM classId = 0;
		if (!GetClassInfoEx(HINSTANCE(), L"NzWindowClass", &wc))
		{
			classId = RegisterClassEx(&wc); // 지금 만든 클래스 정보를 가지고 운영체제에게 '윈도우 등록정보' 하나 만들어줘
			//RegisterClassEx(WNDCLASSEX): 나머지 멤버 변수를 채워서 ID 만들어달라고 요청하는 함수

			if (0 == classId) return NULL;
		}

		RECT rc = { 0, 0, width, height };

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false); // 클라이언트 크기에 프레임 덧 붙이기?

		std::cout << "width: " << rc.right - rc.left << " height: " << rc.bottom - rc.top << std::endl; // 창 크기 조정값 출력

		// 준비된 WNDCLASSEX wc 를 운영체제에 등록한 classID를 갖고 윈도우(커널) 객체 생성 요청
		// 윈도우 핸들 받아오기
		HWND hWnd = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, HWND(), HMENU(), HINSTANCE(), NULL);

		if (NULL == hWnd) return (HWND)(NULL); //못 만들었다면 false

		::SetWindowText((HWND)hWnd, windowName); // 윈도우 창의 이름 설정

		ShowWindow((HWND)hWnd, SW_SHOW); // 윈도우 보여줘
		UpdateWindow((HWND)hWnd); // 갖고 있는거 갱신해줘

		return hWnd;
	}
	
	void GameLoop()
	{
		MSG msg = {};
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, HWND(), 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); //문자 A, key A 구분
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
	// GUI 창 생성
	HWND hWnd = CreateWidow(L"NzWindowClass", L"나전칠기", 1280, 720);

	if (NULL == hWnd)
	{
		std::cout << "윈도우 생성 실패" << std::endl;
		system("pause");
		return -1;
	}

	std::cout << "hWnd: " << hWnd << std::endl;
	//std::cout << (*hWnd).unused << std::endl; 런타임 에러!

	GameLoop();

	DestroyWindow(hWnd);

	return 0;
}