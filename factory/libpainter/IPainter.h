#pragma once
#include "IPictureDraft.h"
#include "ICanvas.h"

class IPainter
{
public:
	virtual void DrawPicture(IPictureDraft const&, ICanvas&) = 0;
	virtual ~IPainter() = default;
};