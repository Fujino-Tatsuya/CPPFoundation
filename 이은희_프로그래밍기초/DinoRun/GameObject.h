#pragma once

#include "Utillity.h"
#include <algorithm>

#include <iostream>
// [CHECK]. namespace 포함해서 전방 선언해야 함
namespace learning
{
	struct ColliderCircle;
	struct ColliderBox;
}

namespace renderHelp
{
	class BitmapInfo;
}

enum class ObjectType
{
	PLAYER,
	ENEMY,
	BULLET,
	ITEM,
	BACKGROUND,
	CACTUS,
	BIRD,
	GROUND,
	BUTTON,
};

constexpr int OBJECT_NAME_LEN_MAX = 15;

class GameObjectBase
{
	using Vector2f = learning::Vector2f;
public:
	GameObjectBase() = delete;
	GameObjectBase(const GameObjectBase&) = delete;

	GameObjectBase(ObjectType type) : m_type(type) {}

	virtual ~GameObjectBase() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc) = 0;

	void SetPosition(float x, float y) { m_pos = { x, y }; }
	void SetDirection(Vector2f dir) { m_dir = dir; }
	void SetSpeed(float speed) { m_speed = speed; }
	void SetName(const char* name);

	void SetWidth(int width) { m_width = width; }
	void SetHeight(int height) { m_height = height; }

	int GetWidth() const { return m_width; } // 2025-04-22
	int GetHeight() const { return m_height; } // 2025-04-22

	ObjectType Type() const { return m_type; }

	const char* GetName() const { return m_name; }

	Vector2f GetPosition() const { return m_pos; }
	Vector2f GetDirection() const { return m_dir; }

	float GetSpeed() const { return m_speed; }


protected:

	void Move(float deltaTime)
	{
		m_pos.x -= m_speed * deltaTime;
	}

protected:
	ObjectType m_type;

	int m_width = 0;
	int m_height = 0;

	Vector2f m_pos = { 0.0f, 0.0f };
	Vector2f m_dir = { 0.0f, 0.0f }; // 방향 (단위 벡터)

	float m_speed = 0.0f; // 속력

	char m_name[OBJECT_NAME_LEN_MAX] = "";
};

class GameObject : public GameObjectBase
{
	using ColliderCircle = learning::ColliderCircle;
	using ColliderBox = learning::ColliderBox;
	using BitmapInfo = renderHelp::BitmapInfo;

public:
	GameObject(const GameObject&) = delete;
	GameObject(ObjectType type) : GameObjectBase(type) {}
	~GameObject() override;

	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

	void SetColliderCircle(float radius);
	void SetColliderBox(float halfWidth, float halfHeight);

	void SetBitmapInfo(BitmapInfo* bitmapInfo);
	void SetState(int state);

	void SetOnGround(bool current);
	bool GetOnGround();

	void UpdateJump();
	void SetJump();

protected:
	void DrawCollider(HDC hdc);
	void DrawBitmap(HDC hdc);

	void Move(float deltaTime);
	void UpdateFrame(float deltaTime);

	// Collider
	ColliderCircle* m_pColliderCircle = nullptr;
	ColliderBox* m_pColliderBox = nullptr;

	BitmapInfo* m_pBitmapInfo = nullptr;

	struct SpriteFrame
	{
		int x;
		int y;
		int width;
		int height;
	};

	SpriteFrame m_frameXY[15] = { { 0, 0 ,0 ,0 }, };
	int m_frameIndex = 0;
	int m_frameCount = 2; // 프레임 수
	
	int m_addFrameIndex = 0;

	bool isGround = true;

	float m_frameTime = 0.0f;
	float m_frameDuration = 100.0f;

	float velocityY = 0.0f;
	const float gravity = 0.9f;
	const float jumpPower = -20.0f;

};