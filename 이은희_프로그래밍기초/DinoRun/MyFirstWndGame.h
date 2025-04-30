#pragma once
#include "NzWndBase.h"
#include "Utillity.h"
#include "Scene.h"

// [CHECK] #7  전방 선언을 사용하여 헤더파일의 의존성을 줄임.
class GameTimer;
//class GameObjectBase;
//class GameObject;

enum TYPE
{
    RESTART,
    IDLE,
    CLOUDE,
    BIRD1,
    BIRD2,
    CACTUS,
    BIGCACTUS,
    JUMP,
    RUN1,
    RUN2,
    DEAD,
    DUCKING1,
    DUCKING2,
    GROUND,
};

class Scene;
namespace renderHelp
{
    class BitmapInfo;
}

class MyFirstWndGame : public NzWndBase
{
public:
    MyFirstWndGame() = default;
    ~MyFirstWndGame() override = default;

    bool Initialize();
    void Run();
    void Finalize();

    void ChangeScene(SceneType eSceneType);

private:
    void Update();
    void Render();

    void OnResize(int width, int height) override;
    void OnClose() override;

    void OnMouseMove(int x, int y);
    void OnLButtonDown(int x, int y);
    void OnKeyDown(UINT key);

    void FixedUpdate();
    void LogicUpdate();
private:
    HDC m_hFrontDC = nullptr;
    HDC m_hBackDC = nullptr;
    HBITMAP m_hBackBitmap = nullptr;
    HBITMAP m_hDefaultBitmap = nullptr;

    // [CHECK] #8. 게임 타이머를 사용하여 프레임을 관리하는 예시.
    GameTimer* m_pGameTimer = nullptr;
    float m_fDeltaTime = 0.0f;
    float m_fFrameCount = 0.0f;

    // [CHECK] #8. 게임 오브젝트를 관리하는 컨테이너.
    //[20240422] Scene 에서 관리하도록 변경
    //int m_eCurrentScene = SCENE_PLAY; Enter 가 안되서.
    int m_eCurrentScene = SCENE_TITLE;
    Scene* m_pScenes[SceneType::SCENE_MAX] = { nullptr, nullptr, nullptr };
    //GameObjectBase** m_GameObjectPtrTable  = nullptr;

    struct MOUSE_POS
    {
        int x = 0;
        int y = 0;

        bool operator!=(const MOUSE_POS& other) const
        {
            return (x != other.x || y != other.y);
        }
    };

    MOUSE_POS m_MousePos = { 0, 0 };
    MOUSE_POS m_MousePosPrev = { 0, 0 };

    MOUSE_POS m_PlayerTargetPos = { 0, 0 };
    MOUSE_POS m_EnemySpawnPos = { 0, 0 };

    MOUSE_POS m_OnClickPos = { 0,0 };

#pragma region resource
    using BitmapInfo = renderHelp::BitmapInfo;

    BitmapInfo* m_mainBitmapInfo = nullptr;

public:

    using Vector2f = learning::Vector2f;
    //Vector2f PlayerTargetPosition() const { return Vector2f(m_PlayerTargetPos.x, m_PlayerTargetPos.y); }
    // EnemySpawnPosition() const { return Vector2f(m_EnemySpawnPos.x, m_EnemySpawnPos.y); }
    //void ResetEnemySpawnPosition() { m_EnemySpawnPos = { 0, 0 }; } //Queue 로 관리하면 더 예쁨
    Vector2f OnClickPosition() const { return Vector2f(m_OnClickPos.x, m_OnClickPos.y); }

    BitmapInfo* GetMainBitmapInfo() const { return m_mainBitmapInfo; }

    TYPE playerState;

#pragma endregion
};
