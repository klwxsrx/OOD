#pragma once
#include "graphics_lib.h"

// ������������ ���� ���������� ��� ��������� ����� (���������� graphics_lib)
// ��� ���������� ���������� ��� ���������
namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	// ��������� ��������, ������� ����� ���� ���������� �� ������ �� graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(const Point & p1, const Point & p2, const Point & p3, uint32_t color = 0x000000)
			: m_vertex1(p1), m_vertex2(p2), m_vertex3(p3), m_color(color)
		{
		}

		void Draw(graphics_lib::ICanvas & canvas)const override
		{
			canvas.SetColor(m_color);
			canvas.MoveTo(m_vertex1.x, m_vertex1.y);
			canvas.LineTo(m_vertex2.x, m_vertex2.y);
			canvas.LineTo(m_vertex3.x, m_vertex3.y);
			canvas.LineTo(m_vertex1.x, m_vertex1.y);
		}
	private:
		Point m_vertex1, m_vertex2, m_vertex3;
		uint32_t m_color;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point & leftTop, int width, int height, uint32_t color = 0x000000)
			: m_leftTop(leftTop), m_width(width), m_height(height), m_color(color)
		{
		}

		void Draw(graphics_lib::ICanvas & canvas)const override
		{
			canvas.SetColor(m_color);
			canvas.MoveTo(m_leftTop.x, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y);
		}
	private:
		Point m_leftTop;
		int m_width, m_height;
		uint32_t m_color;
	};

	// ��������, ��������� �������� ICanvasDrawable-������� �� ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib::ICanvas & canvas)
			: m_canvas(canvas)
		{
		}
		void Draw(const ICanvasDrawable & drawable)
		{
			drawable.Draw(m_canvas);
		}
	private:
		graphics_lib::ICanvas& m_canvas;
	};
}