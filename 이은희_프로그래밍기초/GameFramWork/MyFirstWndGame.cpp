#include "MyFirstWndGame.h"
#include "MyFirstWndGame.h"
#include "GameTimer.h"
#include "Collider.h"
#include "GameObject.h"
#include <iostream>
#include <assert.h>

using namespace learning;

constexpr int MAX_GAME_OBJECT_COUNT = 1000;

bool MyFirstWndGame::Initialize()
{
	m_pGameTimer = new GameTimer();
	m_pGameTimer->Reset();

	const wchar_t* className = L"MyFirstWndGame";
	const wchar_t* windowName = L"MyFirstWndGame";

	if (false == __super::Create(className, windowName, 1024, 720))
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

	m_GameObjectPtrTable = new GameObjectBase * [MAX_GAME_OBJECT_COUNT];

	for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
	{
		m_GameObjectPtrTable[i] = nullptr;
	}

#pragma region resource
	//m_pPlayerBitmapInfo = renderHelp::CreateBitmapInfo(L"../Resource/redbird.png");
	//m_pEnemyBitmapInfo = renderHelp::CreateBitmapInfo(L"../Resource/graybird.png");

	/*if (m_pPlayerBitmapInfo == nullptr || m_pEnemyBitmapInfo == nullptr)
	{
		std::cout << "Bitmap Load Failed!" << std::endl;
		return false;
	}*/

#pragma endregion

	// [CHECK]. 첫 번째 게임 오브젝트는 플레이어 캐릭터로 고정!
	CreatePlayer();

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
			else if (msg.message == WM_RBUTTONDOWN)
			{
				MyFirstWndGame::OnRButtonDown(LOWORD(msg.lParam), HIWORD(msg.lParam));
			}
			else if (msg.message == WM_MOUSEMOVE)
			{
				MyFirstWndGame::OnMouseMove(LOWORD(msg.lParam), HIWORD(msg.lParam));
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

	if (m_GameObjectPtrTable)
	{
		for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
		{
			if (m_GameObjectPtrTable[i])
			{
				delete m_GameObjectPtrTable[i];
				m_GameObjectPtrTable[i] = nullptr;
			}
		}
		//delete m_GameObjectPtrTable;
	}

	__super::Destroy();
}

void MyFirstWndGame::FixedUpdate()
{
	if (m_EnemySpawnPos.x != 0 && m_EnemySpawnPos.y != 0) //적 스폰 위치가 변경되었을 때 (오른쪽 클릭시) 적 생성.
	{
		CreateEnemy();
	}
}

void MyFirstWndGame::LogicUpdate()
{

	UpdatePlayerInfo();
	UpdateEnemyInfo();

	for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
	{
		if (m_GameObjectPtrTable[i])
		{
			m_GameObjectPtrTable[i]->Update(m_fDeltaTime);
		}
	}
}

void MyFirstWndGame::CreatePlayer()
{
	assert(m_GameObjectPtrTable[0] == nullptr && "Player object already exists!");

	GameObject* pNewObject = new GameObject(ObjectType::PLAYER);

	pNewObject->SetName("Player");
	pNewObject->SetPosition(0.0f, 0.0f); // 일단, 임의로 설정 
	pNewObject->SetSpeed(1.0f); // 일단, 임의로 설정   

	pNewObject->SetColliderCircle(50.0f); // 일단, 임의로 설정. 오브젝트 설정할 거 다 하고 나서 하자.

	m_GameObjectPtrTable[0] = pNewObject;
}

void MyFirstWndGame::CreateEnemy()
{
	GameObject* pNewObject = new GameObject(ObjectType::ENEMY);

	pNewObject->SetName("Enemy");

	float x = m_EnemySpawnPos.x;
	float y = m_EnemySpawnPos.y;

	m_EnemySpawnPos = { 0, 0 };

	pNewObject->SetPosition(x, y);
	pNewObject->SetSpeed(0.5f); // 일단, 임의로 설정   

	pNewObject->SetColliderCircle(50.0f); // 일단, 임의로 설정. 오브젝트 설정할 거 다 하고 나서 하자.

	for (int i = 1; i < MAX_GAME_OBJECT_COUNT; ++i)
	{
		if (m_GameObjectPtrTable[i] == nullptr) break;

		if (learning::Intersect(static_cast<GameObject*>(m_GameObjectPtrTable[i])->GetColliderCircle(), pNewObject->GetColliderCircle()))
		{
			return;
		}
	}

	int i = 0;
	while (++i < MAX_GAME_OBJECT_COUNT) //0번째는 언제나 플레이어!
	{
		if (nullptr == m_GameObjectPtrTable[i]) //i가 null이면 생성하고 break;
		{
			m_GameObjectPtrTable[i] = pNewObject;
			break;
		}
	}

	if (i == MAX_GAME_OBJECT_COUNT)
	{
		// 게임 오브젝트 테이블이 가득 찼습니다.
		delete pNewObject;
		pNewObject = nullptr;
	}
}

void MyFirstWndGame::UpdateEnemyInfo()
{
	static GameObject* pPlayer = GetPlayer();

	for (int i = 1; i < MAX_GAME_OBJECT_COUNT; ++i)
	{
		if (m_GameObjectPtrTable[i] == nullptr) break;

		if (learning::Intersect(static_cast<GameObject*>(m_GameObjectPtrTable[i])->GetColliderCircle(), pPlayer->GetColliderCircle())) //플레이어랑 충돌중이면 BLUE
		{
			static_cast<GameObject*>(m_GameObjectPtrTable[i])->SetColor(BLUE);
		}
		else
		{
			static_cast<GameObject*>(m_GameObjectPtrTable[i])->SetColor(RED);
		}
	}
	
}

void MyFirstWndGame::UpdatePlayerInfo()
{
	static GameObject* pPlayer = GetPlayer();

	assert(pPlayer != nullptr);

	Vector2f mousePos(m_PlayerTargetPos.x, m_PlayerTargetPos.y);
	Vector2f playerPos = pPlayer->GetPosition();

	Vector2f playerDir = mousePos - playerPos;
	float distance = playerDir.Length(); // 거리 계산

	if (distance > 50.0f) //임의로 설정한 거리
	{
		playerDir.Normalize(); // 정규화
		pPlayer->SetDirection(playerDir); // 플레이어 방향 설정
	}
	else
	{
		pPlayer->SetDirection(Vector2f(0, 0)); // 플레이어 정지
	}

	for (int i = 1; i < MAX_GAME_OBJECT_COUNT; ++i)
	{
		if (m_GameObjectPtrTable[i] == nullptr) break;

		if (learning::Intersect(static_cast<GameObject*>(m_GameObjectPtrTable[i])->GetColliderCircle(), pPlayer->GetColliderCircle())) //전부 순회하며 하나라도 충돌중이라면 BLUE
		{
			pPlayer->SetColor(BLUE);
			break;
		}
		else
		{
			pPlayer->SetColor(RED);
		}
	}
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
	//Clear the back buffer
	::PatBlt(m_hBackDC, 0, 0, m_width, m_height, WHITENESS);

	//메모리 DC에 그리기
	for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
	{
		if (m_GameObjectPtrTable[i])
		{
			m_GameObjectPtrTable[i]->Render(m_hBackDC);
		}
	}

	//메모리 DC에 그려진 결과를 실제 DC(m_hFrontDC)로 복사
	BitBlt(m_hFrontDC, 0, 0, m_width, m_height, m_hBackDC, 0, 0, SRCCOPY);
}

void MyFirstWndGame::OnResize(int width, int height)
{
	// 미션. 창 사이즈 변경시 원을 가운데로
	std::cout << __FUNCTION__ << std::endl;


	__super::OnResize(width, height);

	m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

	HANDLE hPrevBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);

	DeleteObject(hPrevBitmap);



	learning::SetScreenSize(width, height); // 별로 안중요함
}

void MyFirstWndGame::OnClose()
{
	std::cout << __FUNCTION__ << std::endl;

	SelectObject(m_hBackDC, m_hDefaultBitmap);

	DeleteObject(m_hBackBitmap);
	DeleteDC(m_hBackDC);

	ReleaseDC(m_hWnd, m_hFrontDC); //DC 해제
}

void MyFirstWndGame::OnMouseMove(int x, int y)
{
	/*   std::cout << __FUNCTION__ << std::endl;
	   std::cout << "x: " << x << ", y: " << y << std::endl;*/
	m_MousePosPrev = m_MousePos;
	m_MousePos = { x, y };
}

void MyFirstWndGame::OnLButtonDown(int x, int y)
{
	/*  std::cout << __FUNCTION__ << std::endl;
 std::cout << "x: " << x << ", y: " << y << std::endl;*/

	m_PlayerTargetPos.x = x;
	m_PlayerTargetPos.y = y;

}

void MyFirstWndGame::OnRButtonDown(int x, int y)
{
	/*  std::cout << __FUNCTION__ << std::endl;
   std::cout << "x: " << x << ", y: " << y << std::endl;*/

	m_EnemySpawnPos.x = x;
	m_EnemySpawnPos.y = y;
}