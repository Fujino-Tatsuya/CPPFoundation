#include "INC_Windows.h"

#include "Collider.h"
#include "RenderHelp.h"
#include "GameObject.h"
#include "Utillity.h"
#include <assert.h>
#include <iostream>

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

GameObject::~GameObject()
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

void GameObject::Update(float deltaTime)
{
	UpdateFrame(deltaTime);
	Move(deltaTime);

	// Collider 업데이트
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
	DrawBitmap(hdc);
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

// 과제: 해당 코드의 문제는 무엇일까요? 어떻게 개선하면 좋을까요?
// 개선 방향에 대해 서로 토론하고 비교해 보세요.
void GameObject::DrawCollider(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
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

	// 이전 객체 복원 및 펜 삭제
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
}

void GameObject::SetBitmapInfo(BitmapInfo* bitmapInfo)
{
	assert(m_pBitmapInfo == nullptr && "BitmapInfo must be null!");

	m_pBitmapInfo = bitmapInfo;

	m_frameXY[RESTART] = { 1,1,72,64 };
	m_frameXY[IDLE] = { 75,5,88,90 };
	m_frameXY[CLOUDE] = { 166,1,92,27 };
	m_frameXY[BIRD1] = { 259,13,92,68 };
	m_frameXY[BIRD2] = { 352,2,92,60 };
	m_frameXY[CACTUS] = { 446,2,68,70 };
	m_frameXY[BIGCACTUS] = { 801,1,150,100 };
	m_frameXY[JUMP] = { 1337,1,88,94 };
	m_frameXY[RUN1] = { 1513,1,88,94 };
	m_frameXY[RUN2] = { 1602,1,88,94 };
	m_frameXY[DEAD] = { 1690,1,88,94 };
	m_frameXY[DUCKING1] = { 1865,35,118,60 };
	m_frameXY[DUCKING2] = { 1983,35,118,60 };
	m_frameXY[GROUND] = { 0,102,2402,27 };

	m_frameIndex = 0;
}

void GameObject::SetState(int state)
{
	switch (state)
	{
	case RESTART:
		SetWidth(72);
		SetHeight(64);
		m_addFrameIndex = 0;
		m_frameCount = 1;
		break;
	case IDLE:
		SetWidth(88);
		SetHeight(90);
		m_addFrameIndex = 1;
		m_frameCount = 1;
		break;
	case CLOUDE:
		SetWidth(92);
		SetHeight(27);
		m_addFrameIndex = 2;
		m_frameCount = 1;
		break;
	case BIRD1:
		SetWidth(92);
		SetHeight(68);
		m_addFrameIndex = 3;
		m_frameCount = 2;
		break;
	case CACTUS:
		SetWidth(68);
		SetHeight(70);
		m_addFrameIndex = 5;
		m_frameCount = 1;
		break;
	case BIGCACTUS:
		SetWidth(150);
		SetHeight(100);
		m_addFrameIndex = 6;
		m_frameCount = 1;
		break;
	case JUMP:
		SetWidth(88);
		SetHeight(94);
		m_addFrameIndex = 7;
		m_frameCount = 1;
		break;
	case RUN1:
		SetWidth(88);
		SetHeight(94);
		m_addFrameIndex = 8;
		m_frameCount = 2;
		break;
	case DEAD:
		SetWidth(88);
		SetHeight(94);
		m_addFrameIndex = 10;
		m_frameCount = 1;
		break;
	case DUCKING1:
		SetWidth(118);
		SetHeight(60);
		m_addFrameIndex = 11;
		m_frameCount = 2;
		break;
	case GROUND:
		SetWidth(2402);
		SetHeight(27);
		m_addFrameIndex = 13;
		m_frameCount = 1;
		break;
	}
}

void GameObject::DrawBitmap(HDC hdc)
{
	if (m_pBitmapInfo == nullptr) return;
	if (m_pBitmapInfo->GetBitmapHandle() == nullptr) return;

	HDC hBitmapDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, m_pBitmapInfo->GetBitmapHandle());
	// BLENDFUNCTION 설정 (알파 채널 처리)
	BLENDFUNCTION blend = { 0 };
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;  // 원본 알파 채널 그대로 사용
	blend.AlphaFormat = AC_SRC_ALPHA;

	const int x = m_pos.x - m_width / 2;
	const int y = m_pos.y - m_height / 2;

	const int srcX = m_frameXY[m_frameIndex + m_addFrameIndex].x;
	const int srcY = m_frameXY[m_frameIndex + m_addFrameIndex].y;

	AlphaBlend(hdc, x, y, m_width, m_height,
		hBitmapDC, srcX, srcY, m_frameXY[m_frameIndex + m_addFrameIndex].width, m_frameXY[m_frameIndex + m_addFrameIndex].height, blend);

	// 비트맵 핸들 복원
	SelectObject(hBitmapDC, hOldBitmap);
	DeleteDC(hBitmapDC);

}

void GameObject::Move(float deltaTime)
{
	GameObjectBase::Move(deltaTime);
}

void GameObject::UpdateFrame(float deltaTime)
{
	m_frameTime += deltaTime;
	if (m_frameTime >= m_frameDuration)
	{
		m_frameTime = 0.0f;
		m_frameIndex = (m_frameIndex + 1) % (m_frameCount);
	}
	//와 0을 나눠버리면 오류 나니까 상수 +1 과 나머지 조합으로 0이 나오지 않도록, 하지만 인덱스는 순회하도록
}

void GameObjectBase::SetName(const char* name)
{
	if (name == nullptr) return;

	strncpy_s(m_name, name, OBJECT_NAME_LEN_MAX - 1);
	m_name[OBJECT_NAME_LEN_MAX - 1] = '\0';
}

