#pragma once
#include "memory"
#include "string"

class IDocumentItem
{
public:
	typedef std::shared_ptr<IDocumentItem> Ptr;
	typedef std::shared_ptr<const IDocumentItem> ConstPtr;

	virtual std::string GetDescription()const = 0;

	~IDocumentItem() = default;
};