#include "INC_Windows.h"

#include "Collider.h"
#include "GameObject.h"
#include <assert.h>

GameObject::~GameObject() //�Ҹ��� �ݶ��̴� ������ ������
{
    if (m_pColliderCircle)
    {
        delete m_pColliderCircle;
        m_pColliderCircle = nullptr;
    }

    if (m_pColliderBox)
    {
        delete m_pColliderBox;
        m_pColliderBox = nullptr;
    }
}

void GameObject::Update(float deltaTime) //�̵��̶� collider update 
{
    Move(deltaTime);

    // Collider ������Ʈ
    if (m_pColliderCircle)
    {
        m_pColliderCircle->center = m_pos;
    }
    if (m_pColliderBox)
    {
        m_pColliderBox->center = m_pos;
    }
}

void GameObject::Render(HDC hdc)
{
    //����Ͽ� �̹��� �ε��ؼ� �̹����� �׸���
    DrawCollider(hdc);
}


void GameObject::SetColliderCircle(float radius)
{
    if (m_pColliderCircle)
    {
        delete m_pColliderCircle;
        m_pColliderCircle = nullptr;
    }

    m_pColliderCircle = new ColliderCircle;

    assert(m_pColliderCircle != nullptr && "Failed to create ColliderCircle!");

    m_pColliderCircle->radius = radius;
    m_pColliderCircle->center = m_pos;
}


void GameObject::SetColliderBox(float width, float height)
{
    if (m_pColliderBox)
    {
        delete m_pColliderBox;
        m_pColliderBox = nullptr;
    }

    m_pColliderBox = new ColliderBox;

    assert(m_pColliderBox != nullptr && "Failed to create ColliderBox!");

    m_pColliderBox->center = m_pos;
    m_pColliderBox->halfSize.x = width / 2.0f;
    m_pColliderBox->halfSize.y = height / 2.0f;
}

learning::ColliderCircle GameObject::GetColliderCircle()
{
    return *this->m_pColliderCircle;
}

enum Color
{
    RED,
    BLUE,
    GREEN
};

// ����: �ش� �ڵ��� ������ �����ϱ��? ��� �����ϸ� �������?
// ���� ���⿡ ���� ���� ����ϰ� ���� ������.
void GameObject::DrawCollider(HDC hdc,Color index)
{
    HPEN hPen = nullptr;

    switch(index)
    {
    case RED: hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        break;
    case BLUE: hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
        break;
    case GREEN: hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
        break;
    }
    
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    if (m_pColliderCircle)
    {
        Ellipse(hdc, m_pColliderCircle->center.x - m_pColliderCircle->radius,
            m_pColliderCircle->center.y - m_pColliderCircle->radius,
            m_pColliderCircle->center.x + m_pColliderCircle->radius,
            m_pColliderCircle->center.y + m_pColliderCircle->radius);
    }

    if (m_pColliderBox)
    {
        Rectangle(hdc, m_pColliderBox->center.x - m_pColliderBox->halfSize.x,
            m_pColliderBox->center.y - m_pColliderBox->halfSize.y,
            m_pColliderBox->center.x + m_pColliderBox->halfSize.x,
            m_pColliderBox->center.y + m_pColliderBox->halfSize.y);
    }

    // ���� ��ü ���� �� �� ����
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
}

void GameObject::Move(float deltaTime)
{
    GameObjectBase::Move(deltaTime);
}

void GameObjectBase::SetName(const char* name)
{
    if (name == nullptr) return;

    strncpy_s(m_name, name, OBJECT_NAME_LEN_MAX - 1);
    m_name[OBJECT_NAME_LEN_MAX - 1] = '\0';
}

void GameObjectBase::SetBitmapInfo(BitmapInfo* bitmapInfo)
{
    //m_pBitmapInfo = bitmapInfo
}
