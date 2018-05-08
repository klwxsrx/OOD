#pragma once
#include <iostream>
#include <iomanip>

namespace graphics_lib
{
	// Холст для рисования
	class ICanvas
	{
	public:
		// Ставит "перо" в точку x, y
		virtual void MoveTo(int x, int y) = 0;
		// Рисует линию с текущей позиции, передвигая перо в точку x,y
		virtual void LineTo(int x, int y) = 0;
		// Установка цвета в формате 0xRRGGBB
		virtual void SetColor(uint32_t rgbColor) = 0;
		virtual ~ICanvas() = default;
	};

	// Реализация холста для рисования
	class CCanvas : public ICanvas
	{
	public:
		void MoveTo(int x, int y) override
		{
			std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
		}
		void LineTo(int x, int y) override
		{
			std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
		}
		void SetColor(uint32_t rgbColor) override
		{
			std::cout << "SetColor ("
				<< std::hex << std::setw(8) << std::setfill('0') << std::uppercase << rgbColor << std::nouppercase << std::dec
				<< ")" << std::endl;
		}
	};
}