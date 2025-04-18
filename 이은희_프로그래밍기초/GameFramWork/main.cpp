#define _CRTDBG_MAP_ALLOC

// @brief  나전칠기 프로그래밍 기초 연습장
#include "MyFirstWndGame.h"
#include <iostream>

//#check 헤더 부터 보자
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(162);

	MyFirstWndGame game;
	if (false == game.Initialize())
	{
		std::cout << "Failed to initialize the game. Error: " << GetLastError() << std::endl;
		return -1;
	}

	game.Run();

	game.Finalize();

	return 0;

}