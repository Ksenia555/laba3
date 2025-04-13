#include <iostream>
#include "TString.h"
#include "../build/stringlib/Redactor.h"


int main()
{

	TextEditor::SetTextColor(TextEditor::MAGENTA, TextEditor::BOLD);
	TString s1("lol"), s2("lol");
	TString s3;

	s3 = s1;
	std:: cout << s3 << std::endl;

	TString s4;
	std::cin >> s4;
	std::cout << s4 << std::endl;

	int sos = 0;
	std::cout << "Write the lenght of string - ";
	std::cin >> sos;
	TextEditor editor(sos);

	editor.SetPosition(15, 15);

	std::cout << "Coping:\n\n";

	// Запускаем ввод
	editor.RunInput();

	// Получаем результат
	std::cout << "\n\nVivod: " << editor.GetText() << std::endl;

	return 0;
}