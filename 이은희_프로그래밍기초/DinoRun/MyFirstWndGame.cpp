#include "MyFirstWndGame.h"
#include "GameTimer.h"
#include "Collider.h"
#include "GameObject.h"
#include "RenderHelp.h"
#include "TitleScene.h" // 20250421
#include "PlayScene.h"
#include "EndingScene.h"
#include <iostream>
#include <assert.h>

using namespace learning;

//constexpr int MAX_GAME_OBJECT_COUNT = 1000;

bool MyFirstWndGame::Initialize()
{
	m_pGameTimer = new GameTimer();
	m_pGameTimer->Reset();

	const wchar_t* className = L"MyFirstWndGame";
	const wchar_t* windowName = L"DINO RUN";

	if (false == __super::Create(className, windowName, 2400, 400))
	{
		return false;
	}


	RECT rcClient = {};
	GetClientRect(m_hWnd, &rcClient);
	m_width = rcClient.right - rcClient.left;
	m_height = rcClient.bottom - rcClient.top;

	m_hFrontDC = GetDC(m_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hFrontDC);
	m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

	m_hDefaultBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);

#pragma region resource
	m_mainBitmapInfo = renderHelp::CreateBitmapInfo(L"../Resource/sprite.png");

	if (m_mainBitmapInfo == nullptr)
	{
		std::cout << "Bitmap Load Failed!" << std::endl;
		return false;
	}
#pragma endregion

	m_pScenes[SceneType::SCENE_TITLE] = new TitleScene();
	m_pScenes[SceneType::SCENE_TITLE]->Initialize(this);


	m_pScenes[SceneType::SCENE_PLAY] = new PlayScene();
	m_pScenes[SceneType::SCENE_PLAY]->Initialize(this);

	m_pScenes[SceneType::SCENE_ENDING] = new EndingScene();
	m_pScenes[SceneType::SCENE_ENDING]->Initialize(this);
	return true;

}

void MyFirstWndGame::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				MyFirstWndGame::OnLButtonDown(LOWORD(msg.lParam), HIWORD(msg.lParam));
			}
			else if (msg.message == WM_MOUSEMOVE)
			{
				MyFirstWndGame::OnMouseMove(LOWORD(msg.lParam), HIWORD(msg.lParam));
			}
			else if (msg.message == WM_KEYDOWN)
			{
				MyFirstWndGame::OnKeyDown(static_cast<UINT>(msg.wParam));
			}
			else if (msg.message == WM_KEYUP)
			{
				MyFirstWndGame::OnKeyUP(static_cast<UINT>(msg.wParam));
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Update();
			Render();
		}
	}
}

void MyFirstWndGame::Finalize()
{
	delete m_pGameTimer;
	m_pGameTimer = nullptr;

	for (int i = 0; i < SceneType::SCENE_MAX; ++i)
	{
		if (m_pScenes[i])
		{
			m_pScenes[i]->Finalize();
			delete m_pScenes[i];
			m_pScenes[i] = nullptr;
		}
	}

	__super::Destroy();

}

void MyFirstWndGame::ChangeScene(SceneType eSceneType)
{
	if (m_eCurrentScene != eSceneType)
	{
		m_pScenes[m_eCurrentScene]->Leave();
		m_eCurrentScene = eSceneType;
		m_pScenes[m_eCurrentScene]->Enter();
	}
}

void MyFirstWndGame::FixedUpdate()
{
	m_pScenes[m_eCurrentScene]->FixedUpdate();
}

void MyFirstWndGame::LogicUpdate()
{
	m_pScenes[m_eCurrentScene]->Update(m_fDeltaTime);
}


void MyFirstWndGame::Update()
{
	m_pGameTimer->Tick();

	LogicUpdate();

	m_fDeltaTime = m_pGameTimer->DeltaTimeMS();
	m_fFrameCount += m_fDeltaTime;

	while (m_fFrameCount >= 200.0f)
	{
		FixedUpdate();
		m_fFrameCount -= 200.0f;
	}
}

void MyFirstWndGame::Render()
{
	::PatBlt(m_hBackDC, 0, 0, m_width, m_height, WHITENESS);

	m_pScenes[m_eCurrentScene]->Render(m_hBackDC);

	BitBlt(m_hFrontDC, 0, 0, m_width, m_height, m_hBackDC, 0, 0, SRCCOPY);
}

void MyFirstWndGame::OnResize(int width, int height)
{
	std::cout << __FUNCTION__ << std::endl;

	learning::SetScreenSize(width, height);

	__super::OnResize(width, height);

	m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

	HANDLE hPrevBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);

	DeleteObject(hPrevBitmap);
}

void MyFirstWndGame::OnClose()
{
	std::cout << __FUNCTION__ << std::endl;

	SelectObject(m_hBackDC, m_hDefaultBitmap);

	DeleteObject(m_hBackBitmap);
	DeleteDC(m_hBackDC);

	ReleaseDC(m_hWnd, m_hFrontDC);
}

void MyFirstWndGame::OnMouseMove(int x, int y)
{
	m_MousePosPrev = m_MousePos;
	m_MousePos = { x, y };
}

void MyFirstWndGame::OnLButtonDown(int x, int y)
{
	m_OnClickPos = m_MousePos;

	std::cout << m_OnClickPos.x << std::endl << m_OnClickPos.y << std::endl;
}

void MyFirstWndGame::OnKeyDown(UINT key)
{
	Scene* currentScene = m_pScenes[m_eCurrentScene];

	if (m_eCurrentScene == SceneType::SCENE_PLAY)
	{
		PlayScene* playScene = dynamic_cast<PlayScene*>(currentScene);

		playScene->SetGamePlay();

		if (playScene)
		{
			GameObject* player = playScene->GetPlayer();
			if (player)
			{
				switch (key)
				{
				case VK_UP:
						player->SetState(JUMP);
						player->SetJump();
					break;
				case VK_DOWN:
					if (player->GetOnGround())
					{
						player->SetState(DUCKING1);
					}
					break;
				case VK_SPACE:
						player->SetState(JUMP);
						player->SetJump();
					break;	
				}
			}
		}
	}
}

void MyFirstWndGame::OnKeyUP(UINT key)
{
	Scene* currentScene = m_pScenes[m_eCurrentScene];

	if (m_eCurrentScene == SceneType::SCENE_PLAY)
	{
		PlayScene* playScene = dynamic_cast<PlayScene*>(currentScene);

		playScene->SetGamePlay();

		if (playScene)
		{
			GameObject* player = playScene->GetPlayer();
			if (player)
			{
				switch (key)
				{
				case VK_DOWN:
					if (player->GetOnGround())
					{
						player->SetState(RUN1);
					}
					break;
				}
			}
		}
	}
}

