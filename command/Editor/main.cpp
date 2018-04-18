#include "stdafx.h"
#include "../libeditor/Document.h"
#include "Editor.h"

int main()
{
	CDocument document;
	CEditor editor(document, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		editor.HandleCommand();
	}
}