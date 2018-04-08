#include "stdafx.h"
#include "Document.h"

CDocument::CDocument()
	: m_title("Untitled document")
{
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(std::string const & text, boost::optional<size_t> position)
{
	return std::shared_ptr<IParagraph>();
}

std::shared_ptr<IImage> CDocument::InsertImage(boost::filesystem::path const & path, unsigned width, unsigned height, boost::optional<size_t> position)
{
	return std::shared_ptr<IImage>();
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

IDocumentItem::Ptr CDocument::GetItem(size_t index) const
{
	return IDocumentItem::Ptr();
}

IDocumentItem::ConstPtr CDocument::GetItem(size_t index)
{
	return IDocumentItem::ConstPtr();
}

void CDocument::DeleteItem(size_t index)
{
}

void CDocument::SetTitle(std::string const & title)
{
	m_title = title;
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return false;
}

void CDocument::Undo()
{
}

bool CDocument::CanRedo() const
{
	return false;
}

void CDocument::Redo()
{
}

void CDocument::Save(boost::filesystem::path const & path) const
{
}
