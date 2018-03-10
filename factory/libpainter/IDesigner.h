#pragma once

class CPictureDraft;

class IDesigner
{
public:
	virtual ~IDesigner() = default;

	virtual CPictureDraft CreateDraft(std::istream &) = 0;
};