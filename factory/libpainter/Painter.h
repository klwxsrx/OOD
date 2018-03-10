#pragma once
#include "IPainter.h"

class CPainter : public IPainter
{
public:
	void DrawPicture(IPictureDraft const& draft, ICanvas& canvas) override;
};

