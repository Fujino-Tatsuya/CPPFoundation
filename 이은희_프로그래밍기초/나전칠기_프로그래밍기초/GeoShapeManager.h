#include "INC_Windows.h"

namespace simplegeo
{
	class ShapeBase
	{
	public:
		virtual void Draw(HDC hdc) = 0;
		virtual ~ShapeBase() {}

		virtual int GetX() {};
		virtual int GetY() {};
	};

	class Circle : public ShapeBase
	{
	public:
		Circle(int centerX, int centerY, int radius, COLORREF color)
			: m_centerX(centerX), m_centerY(centerY), m_radius(radius), m_color(color) {
		}

		void Draw(HDC hdc) override
		{
			// �� ���� �� ����
			HPEN hPen = CreatePen(PS_SOLID, 2, m_color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			// �귯�ô� ���� ä���� �ʵ��� NULL_BRUSH ���
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

			Ellipse(hdc,
				m_centerX - m_radius, m_centerY - m_radius,
				m_centerX + m_radius, m_centerY + m_radius);

			// ���� ��ü ���� �� �� ����
			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hPen);
		}

		int GetX() override
		{
			return m_centerX;
		}

		int GetY() override
		{
			return m_centerY;
		}
	private:
		int m_centerX, m_centerY, m_radius;
		COLORREF m_color;
	};


	class RectangleShape : public ShapeBase
	{
	public:
		RectangleShape(int left, int bottom, int size, COLORREF color)
			: m_left(left), m_bottom(bottom), m_size(size), m_color(color) {
		}

		void Draw(HDC hdc) override
		{
			HPEN hPen = CreatePen(PS_SOLID, 2, m_color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

			Rectangle(hdc, m_left, (m_bottom + m_size), (m_left + m_size), m_bottom);

			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hPen);
		}

		int GetX() override
		{
			return m_bottom;
		}

		int GetY() override
		{
			return m_left;
		}
	private:
		int m_left, m_bottom, m_size;
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

		int GetX() override
		{
			return;
		}

		int GetY() override
		{
			return;
		}
	private:
		int m_startX, m_startY, m_endX, m_endY;
		COLORREF m_color;
	};

	constexpr int MAX_SHAPES = 100; // �ִ� ���� ����
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

		void RemoveGeo(int mouseX, int mouseY)
		{

		}

		void AddCircle(int centerX, int centerY, int radius, COLORREF color)
		{
			if (m_shapeCount >= MAX_SHAPES) return;

			m_shapes[m_shapeCount] = new Circle(centerX, centerY, radius, color);
			++m_shapeCount;
		}

		void AddRectangle(int left, int bottom, int size, COLORREF color)
		{
			if (m_shapeCount >= MAX_SHAPES) return;

			m_shapes[m_shapeCount] = new RectangleShape(left, bottom, size, color);
			++m_shapeCount;
		}

		void AddLine(int startX, int startY, int endX, int endY, COLORREF color)
		{
			if (m_shapeCount >= MAX_SHAPES) return;

			m_shapes[m_shapeCount] = new Line(startX, startY, endX, endY, color);
			++m_shapeCount;
		}

		void Draw(HDC hdc) //
		{
			for (int i = 0; i < MAX_SHAPES; ++i)
			{
				if (m_shapes[i] == nullptr) break;

				m_shapes[i]->Draw(hdc);
			}
		}

	private:
		ShapeBase* m_shapes[MAX_SHAPES] = { nullptr, }; //ShapeBase
		int m_shapeCount = 0;
	};

	extern GeoShapeManager g_GeoShapeManager;
}