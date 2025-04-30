#include "TitleScene.h"
#include "MyFirstWndGame.h"
#include "GameObject.h"
#include "Utillity.h"
#include <assert.h>

#include <iostream> // debug¿ë

using namespace learning;

void TitleScene::Initialize(NzWndBase* pWnd)
{
    m_pGame = dynamic_cast<MyFirstWndGame*>(pWnd);
    assert(m_pGame != nullptr && "Game object is not initialized!");

    Background* pNewObject = new Background(ObjectType::BACKGROUND);
    pNewObject->SetPosition(0.0f, 0.0f);

    int width = m_pGame->GetWidth();
    int height = m_pGame->GetHeight();

    pNewObject->SetWidth(width);
    pNewObject->SetHeight(height);

    pNewObject->SetBitmapInfo(m_pGame->GetMainBitmapInfo());

    m_rect.left = width / 2 - 36;
    m_rect.top = height / 2 - 32;
    m_rect.right = m_rect.left + 72;
    m_rect.bottom = m_rect.top + 64;

    m_pBackground = pNewObject;
}

void TitleScene::Update(float deltaTime)
{
    Vector2f onclickpos = m_pGame->OnClickPosition();

    if (onclickpos.x > m_rect.left && onclickpos.x < m_rect.right && onclickpos.y < m_rect.bottom && onclickpos.y > m_rect.top)
    {
        std::cout << "SceneChange" << std::endl;
        m_pGame->ChangeScene(SceneType::SCENE_PLAY);
    }
}

void TitleScene::Render(HDC hDC)
{
    assert(m_pGame != nullptr && "Game object is not initialized!");

    m_pBackground->Render(hDC);

    DrawText(hDC, m_szTitle, -1, &m_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void TitleScene::Finalize()
{
    if (m_pBackground)
    {
        delete m_pBackground;
        m_pBackground = nullptr;
    }
}

void TitleScene::Enter()
{

}

void TitleScene::Leave()
{
}

