#pragma once
#include <iostream>
#include <boost\format.hpp>

namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
		float r, g, b, a;
	};

	// ����� ��� ������������ ��������� �������
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream & strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // ��������� ���������, ���� ��� ���� ������
			{
				EndDraw();
			}
		}

		// ���� ����� ������ ���� ������ � ������ ���������
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// ��������� ��������� �����
		void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
		{
			if (!m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}
			m_out << (boost::format(R"text(<line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"><color r="%5%" g="%6%" b="%7%" a="%8%" />)text") % start.x % start.y % end.x % end.y % color.r % color.g % color.b % color.a) << std::endl;
		}

		// ���� ����� ������ ���� ������ � ����� ���������
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}
	private:
		std::ostream & m_out;
		bool m_drawing = false;
	};
}