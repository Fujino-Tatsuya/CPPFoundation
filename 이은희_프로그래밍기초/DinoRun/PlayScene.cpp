#include "PlayScene.h"
#include "MyFirstWndGame.h"
#include "GameObject.h"
#include "Utillity.h"
#include <assert.h>

using namespace learning;

constexpr int MAX_GAME_OBJECT_COUNT = 1000;


void PlayScene::Initialize(NzWndBase* pWnd)
{
    m_pGame = dynamic_cast<MyFirstWndGame*>(pWnd);
    assert(m_pGame != nullptr);

    m_GameObjectPtrTable = new GameObjectBase*[MAX_GAME_OBJECT_COUNT];

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        m_GameObjectPtrTable[i] = nullptr;
    }

}

void PlayScene::FixedUpdate()
{
    assert(m_pGame != nullptr && "Game object is not initialized!");

    GameObject* pPlayer = GetPlayer();

    pPlayer->UpdateJump();

}
    

void PlayScene::Update(float deltaTime)
{
    if (GetisStart() == false) return;

    UpdatePlayerInfo();
    UpdateGroundInfo();

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (m_GameObjectPtrTable[i])
        {
            m_GameObjectPtrTable[i]->Update(deltaTime);
        }
    }
}

void PlayScene::Render(HDC hDC)
{
    assert(m_pGame != nullptr && "Game object is not initialized!");

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (m_GameObjectPtrTable[i])
        {
            m_GameObjectPtrTable[i]->Render(hDC);
        }
    }
}

void PlayScene::SetGameStop()
{
    isGameStart = false;
}

void PlayScene::SetGamePlay()
{
    isGameStart = true;
}

bool PlayScene::GetisStart()
{
    return isGameStart;
}

void PlayScene::Finalize()
{
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

      delete [] m_GameObjectPtrTable;
   }
}

void PlayScene::Enter()
{
    CreatePlayer();
    CreateGround(1, 1201);
    CreateGround(2, 3603);
}

void PlayScene::Leave()
{

}

void PlayScene::CreatePlayer()
{
    assert(m_GameObjectPtrTable[0] == nullptr && "Player object already exists!");
    assert(m_pGame != nullptr && "Game object is not initialized!");

    GameObject* pNewObject = new GameObject(ObjectType::PLAYER);

    pNewObject->SetName("Player");
    pNewObject->SetPosition(55, 333 ); // 일단, 임의로 설정 
    pNewObject->SetSpeed(0); // 일단, 임의로 설정 
    pNewObject->SetWidth(88); // 일단, 임의로 설정
    pNewObject->SetHeight(94); // 일단, 임의로 설정

    pNewObject->SetBitmapInfo(m_pGame->GetMainBitmapInfo()); //게임이 로드한 이미지 setting
    pNewObject->SetState(IDLE);
    pNewObject->SetColliderBox(60, 90);

    pNewObject->SetOnGround(true);

    m_GameObjectPtrTable[0] = pNewObject;
}

void PlayScene::CreateEnemy()
{
    assert(m_pGame != nullptr && "Game object is not initialized!");

    GameObject* pNewObject = new GameObject(ObjectType::ENEMY);

    pNewObject->SetName("Enemy");

    pNewObject->SetSpeed(0.1f); // 일단, 임의로 설정  
    pNewObject->SetWidth(92); // 일단, 임의로 설정
    pNewObject->SetHeight(80); // 일단, 임의로 설정

    
    pNewObject->SetBitmapInfo(m_pGame->GetMainBitmapInfo()); //여기

    //pNewObject->SetColliderCircle(50.0f);

    int i = 1;
    while (++i < MAX_GAME_OBJECT_COUNT) //0번째 player, 1번쨰 ground
    {
        if (nullptr == m_GameObjectPtrTable[i])
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

void PlayScene::CreateGround(int count, int pos)
{
    assert(m_pGame != nullptr && "Game object is not initialized!");

    GameObject* pNewObject = new GameObject(ObjectType::GROUND);

    pNewObject->SetName("Ground1");

    pNewObject->SetPosition(pos, 366);

    pNewObject->SetSpeed(1);
    pNewObject->SetWidth(2402);
    pNewObject->SetHeight(27);
    pNewObject->SetState(GROUND);

    pNewObject->SetBitmapInfo(m_pGame->GetMainBitmapInfo());

    m_GameObjectPtrTable[count] = pNewObject;
}

void PlayScene::UpdatePlayerInfo()
{
    GameObject* pPlayer = GetPlayer();

    assert(pPlayer != nullptr);
    assert(m_pGame != nullptr && "MyFirstWndGame is null!");

    Vector2f playerPos = pPlayer->GetPosition();

    std::cout << pPlayer->GetOnGround() << std::endl;

    

    /*if (playerPos.y >= 333)
    {
        playerPos.y = 333;
        pPlayer->SetOnGround(true);
    }
    else if(playerPos.y < 333)
    {
        pPlayer->SetOnGround(false);
    }*/
}

void PlayScene::UpdateGroundInfo()
{
    GameObject* pGround1 = GetGround(1);
    GameObject* pGround2 = GetGround(2);

    Vector2f gPos1 = pGround1->GetPosition();
    Vector2f gPos2 = pGround2->GetPosition();
    if (gPos1.x < -1201)
    {
        pGround1->SetPosition(3603, 366);
    }
    if (gPos2.x < -1201)
    {
        pGround2->SetPosition(3603, 366);
    }
}

