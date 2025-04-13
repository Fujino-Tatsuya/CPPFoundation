#include "INC_Windows.h"
#include <cmath>
#include <iostream>

enum Shape
{
	Shape_CIRCLE,
	Shape_RECTAGLE,
	Shape_LINE,
};

namespace simplegeo
{
	struct GeoInfo
	{
	public:
		int x;
		int y;
		int size;
		int shape;
	};

	class ShapeBase
	{
	public:
		virtual void Draw(HDC hdc) = 0;
		virtual ~ShapeBase() {}

		virtual GeoInfo GetInfo()
		{
			GeoInfo info = { 0, };
			return info;
		};
	};

	class Circle : public ShapeBase
	{
	public:
		Circle(int centerX, int centerY, int radius, int shape, COLORREF color)
			: m_centerX(centerX), m_centerY(centerY), m_radius(radius), m_shape(shape), m_color(color) {
		}

		void Draw(HDC hdc) override
		{
			// 펜 생성 및 선택
			HPEN hPen = CreatePen(PS_SOLID, 2, m_color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			// 브러시는 내부 채우지 않도록 NULL_BRUSH 사용
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

			Ellipse(hdc,
				m_centerX - m_radius, m_centerY - m_radius,
				m_centerX + m_radius, m_centerY + m_radius);

			// 이전 객체 복원 및 펜 삭제
			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hPen);
		}

		GeoInfo GetInfo() override
		{
			GeoInfo pos = { 0, };

			pos.x = m_centerX;
			pos.y = m_centerY;
			pos.size = m_radius;
			pos.shape = m_shape;
			return pos;
		}
	private:
		int m_centerX, m_centerY, m_radius, m_shape;
		COLORREF m_color;
	};


	class RectangleShape : public ShapeBase
	{
	public:
		RectangleShape(int x, int y, int size, int shape, COLORREF color)
			: m_centerX(x), m_centerY(y), m_size(size), m_shape(shape), m_color(color) {
		}

		void Draw(HDC hdc) override
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, m_color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

			Rectangle(hdc, (m_centerX - m_size), (m_centerY + m_size), (m_centerX + m_size), (m_centerY - m_size));

			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hPen);
		}

		GeoInfo GetInfo() override
		{
			GeoInfo pos = { 0, };

			pos.x = m_centerX;
			pos.y = m_centerY;
			pos.size = m_size;
			pos.shape = m_shape;
			return pos;
		}
	private:
		int m_centerX, m_centerY, m_size, m_shape;
		COLORREF m_color;
	};


	class Line : public ShapeBase
	{
	public:
		Line(int startX, int startY, int endX, int endY, COLORREF color)
			: m_startX(startX), m_startY(startY), m_endX(endX), m_endY(endY), m_color(color) {
		}

		void Draw(HDC hdc) override
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, m_color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

			MoveToEx(hdc, m_startX, m_startY, NULL);
			LineTo(hdc, m_endX, m_endY);

			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
		}

	private:
		int m_startX, m_startY, m_endX, m_endY;
		COLORREF m_color;
	};

	constexpr int MAX_SHAPES = 100; // 최대 도형 개수
	class GeoShapeManager
	{
	public:
		GeoShapeManager() = default;
		~GeoShapeManager()
		{
			for (int i = 0; i < MAX_SHAPES; ++i)
			{
				if (m_shapes[i] != nullptr)
				{
					delete m_shapes[i];
					m_shapes[i] = nullptr;
				}
			}
		}

		void FindEmpty()
		{
			for (int i = 0; i < MAX_SHAPES; ++i)
			{
				if (m_shapes[i] == nullptr)
				{
					m_shapeCount = i;
					std::cout << m_shapeCount << std::endl;
					break;
				}
			}
		}

		bool DetectGeo(int mouseX, int mouseY, int shape) //true 면 지우고 // false면 그리기
		{
			for (int i = 0; i < MAX_SHAPES; i++)
			{
				if (m_shapes[i] != nullptr)
				{
					GeoInfo geoInfo = { 0, };
					geoInfo = m_shapes[i]->GetInfo();

					if (shape == geoInfo.shape && geoInfo.size > sqrt(pow(geoInfo.x - mouseX, 2) + pow(geoInfo.y - mouseY, 2)))
					{
						m_shapes[i] = nullptr;
						//--m_shapeCount;
						return true;
					}
				}
			}
			return false;
		}

		void AddCircle(int centerX, int centerY, int radius, int shape, COLORREF color)
		{
			if (m_shapeCount >= MAX_SHAPES) return;

			m_shapes[m_shapeCount] = new Circle(centerX, centerY, radius, shape, color);
			//++m_shapeCount;
		}

		void AddRectangle(int x, int y, int size, int shape, COLORREF color)
		{
			if (m_shapeCount >= MAX_SHAPES) return;

			m_shapes[m_shapeCount] = new RectangleShape(x, y, size, shape, color);
			//++m_shapeCount;
		}

		void AddLine(int startX, int startY, int endX, int endY, COLORREF color)
		{
			if (m_shapeCount >= MAX_SHAPES) return;

			m_shapes[m_shapeCount] = new Line(startX, startY, endX, endY, color);
			//++m_shapeCount;
		}

		void Draw(HDC hdc)
		{
			for (int i = 0; i < MAX_SHAPES; ++i)
			{
				if (m_shapes[i] == nullptr)
				{
					continue;
				}
				else
				{
					m_shapes[i]->Draw(hdc);
				}
			}
		}

	private:
		ShapeBase* m_shapes[MAX_SHAPES] = { nullptr, }; //ShapeBase
		int m_shapeCount = 0;
	};

	extern GeoShapeManager g_GeoShapeManager;
}