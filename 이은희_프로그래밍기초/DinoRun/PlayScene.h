#pragma once
#include "Scene.h"

class GameObjectBase;
class GameObject;
class MyFirstWndGame;

class PlayScene :public Scene
{
 public:
    PlayScene() = default;
    ~PlayScene() override = default;

    void Initialize(NzWndBase* pWnd) override;
    void Finalize() override;

    virtual void Enter() override;
    virtual void Leave() override;

    void FixedUpdate() override;
    void Update(float deltaTime) override;
    void Render(HDC hDC) override;


    GameObject* GetPlayer() const { return (GameObject*)m_GameObjectPtrTable[0]; }
    GameObject* GetGround(int index) const { return (GameObject*)m_GameObjectPtrTable[index]; }
  
private:
    void CreatePlayer();
    void CreateEnemy();
    void CreateGround(int count, int pos);

    void UpdatePlayerInfo();
    void UpdateGroundInfo();


    MyFirstWndGame* m_pGame = nullptr;
};

