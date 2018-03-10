#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory & factory);
	~CDesigner();
	CPictureDraft CreateDraft(std::istream & inputData)override;
private:
	IShapeFactory & m_factory;
};

