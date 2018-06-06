#include "stdafx.h"
#include "Editor.h"

CEditor::CEditor(IDocument& document, std::istream& in, std::ostream& out)
	: m_document(document), m_in(in), m_out(out)
	, m_actionMap({
		{ "InsertParagraph", std::bind(&CEditor::InsertParagraph, this, std::placeholders::_1) },
		{ "InsertImage", std::bind(&CEditor::InsertImage, this, std::placeholders::_1) },
		{ "SetTitle", std::bind(&CEditor::SetTitle, this, std::placeholders::_1) },
		{ "ReplaceText", std::bind(&CEditor::ReplaceText, this, std::placeholders::_1) },
		{ "ResizeImage", std::bind(&CEditor::ResizeImage, this, std::placeholders::_1) },
		{ "DeleteItem", std::bind(&CEditor::DeleteItem, this, std::placeholders::_1) },
		{ "Undo", std::bind(&CEditor::Undo, this, std::placeholders::_1) },
		{ "Redo", std::bind(&CEditor::Redo, this, std::placeholders::_1) },
		{ "Save", std::bind(&CEditor::Save, this, std::placeholders::_1) },
	})
{
	PrintHelp();
	PrintDocument();
	PrintCarriage();
}

void CEditor::HandleCommand()
{
	std::string commandLine;
	std::getline(m_in, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	ClearConsole();

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			it->second(strm);
			m_out << "Success!" << std::endl << std::endl;
		}
		catch (const std::exception& e)
		{
			m_out << "Error!" << std::endl;
			m_out << e.what() << std::endl;
		}
	}
	else
	{
		m_out << "Unknown command!" << std::endl << std::endl;
		PrintHelp();
	}

	PrintDocument();
	PrintCarriage();
}

void CEditor::PrintCarriage()
{
	m_out << std::endl << std::endl << "> ";
}

void CEditor::PrintHelp()
{
	m_out << "InsertParagraph <position=end> [text]" << std::endl
		<< "InsertImage <position=end> <image> <width> <height>" << std::endl
		<< "SetTitle <title>" << std::endl
		<< "ReplaceText <index> [text]" << std::endl
		<< "ResizeImage <index> <width> <height>" << std::endl
		<< "DeleteItem <index>" << std::endl
		<< "Undo" << std::endl
		<< "Redo" << std::endl
		<< "Save <path>" << std::endl;
}

void CEditor::PrintDocument()
{
	m_out << std::endl << "Title: " << m_document.GetTitle() << std::endl;

	size_t itemsCount = m_document.GetItemsCount();
	if (itemsCount == 0)
	{
		m_out << "Empty!" << std::endl;
	}
	for (size_t i = 0; i < itemsCount; ++i)
	{
		m_out << i << ": " << m_document.GetItem(i)->GetDescription() << std::endl;
	}
	m_out << "History: " << (m_document.CanUndo() ? "Undo" : "----") << "/" << (m_document.CanRedo() ? "Redo" : "----") << std::endl;
}

void CEditor::InsertParagraph(std::istream& args)
{
	const std::string usageCommand("\nInsertParagraph <position=end> [text]");
	boost::optional<size_t> position;
	try
	{
		position = ReadPositionFromInput(args);
	}
	catch (std::runtime_error const& e)
	{
		throw std::runtime_error(e.what() + usageCommand);
	}

	std::string text = ReadLineFromRemainingInput(args);
	m_document.InsertParagraph(text, position);
}

void CEditor::InsertImage(std::istream& args)
{
	const std::string usageCommand("\nInsertImage <position=end> <imagePath> <width> <height>");
	boost::optional<size_t> position;
	try
	{
		position = ReadPositionFromInput(args);
	}
	catch (std::runtime_error const& e)
	{
		throw std::runtime_error(e.what() + usageCommand);
	}

	std::string imagePath;
	args >> imagePath;
	if (args.fail())
	{
		throw std::runtime_error("ImagePath is required!" + usageCommand);
	}

	unsigned width;
	args >> width;
	if (args.fail())
	{
		throw std::runtime_error("Width must be an unsigned integer!" + usageCommand);
	}

	unsigned height;
	args >> height;
	if (args.fail())
	{
		throw std::runtime_error("Height must be an unsigned integer!" + usageCommand);
	}

	m_document.InsertImage(imagePath, width, height, position);
}

void CEditor::SetTitle(std::istream& args)
{
	std::string title = ReadLineFromRemainingInput(args);

	m_document.SetTitle(title);
}

void CEditor::ReplaceText(std::istream& args)
{
	size_t index;
	args >> index;
	if (args.fail())
	{
		throw std::runtime_error("Index is required!");
	}

	std::string text = ReadLineFromRemainingInput(args);

	auto paragraph = m_document.GetItem(index)->GetParagraph();
	if (paragraph == nullptr)
	{
		throw std::runtime_error("The specified item is not a paragraph!");
	}

	paragraph->SetText(text);
}

void CEditor::ResizeImage(std::istream& args)
{
	const std::string usageCommand("\nResizeImage <index> <width> <height>");

	size_t index;
	args >> index;
	if (args.fail())
	{
		throw std::runtime_error("Index is required!" + usageCommand);
	}

	unsigned width;
	args >> width;
	if (args.fail())
	{
		throw std::runtime_error("Width must be an unsigned integer!" + usageCommand);
	}

	unsigned height;
	args >> height;
	if (args.fail())
	{
		throw std::runtime_error("Height must be an unsigned integer!" + usageCommand);
	}

	auto image = m_document.GetItem(index)->GetImage();
	if (image == nullptr)
	{
		throw std::runtime_error("The specified item is not a paragraph!");
	}

	image->Resize(width, height);
}

void CEditor::DeleteItem(std::istream& args)
{
	size_t index;
	args >> index;
	if (args.fail())
	{
		throw std::runtime_error("Index is required!");
	}

	m_document.DeleteItem(index);
}

void CEditor::Undo(std::istream&)
{
	if (!m_document.CanUndo())
	{
		throw std::runtime_error("Nothing to undo!");
	}
	m_document.Undo();
}

void CEditor::Redo(std::istream&)
{
	if (!m_document.CanRedo())
	{
		throw std::runtime_error("Nothing to redo!");
	}
	m_document.Redo();
}

void CEditor::Save(std::istream& args)
{
	std::string path;
	args >> path;

	if (path.empty())
	{
		throw std::runtime_error("Save path is required!");
	}

	m_document.Save(path);
}

void CEditor::ClearConsole()
{
	system("cls");
}

std::string CEditor::ReadLineFromRemainingInput(std::istream& in)
{
	std::string result;
	std::getline(in, result);
	return result.erase(0, 1);
}

boost::optional<size_t> CEditor::ReadPositionFromInput(std::istream& in)
{
	std::string positionStr;
	size_t position;
	boost::optional<size_t> optionalPosition;

	in >> positionStr;
	if (positionStr == "end")
	{
		optionalPosition = boost::none;
	}
	else if (std::stringstream(positionStr) >> position)
	{
		optionalPosition = position;
	}
	else
	{
		throw std::runtime_error("Position must be an unsigned integer or \"end\"!");
	}
	return optionalPosition;
}