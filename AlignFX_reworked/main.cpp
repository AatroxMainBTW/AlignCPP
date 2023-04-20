#include <iostream>
#include "PreProcessing.hpp"

int main() {
	std::vector<std::string> test = { "Hello-'_ /&1","HIIII","Hello-'_'1","Hello-'_ /&1","ss"};
	std::cout << "Before" << "\n";
	for (int i = 0; i < test.size(); i++)
	{
		std::cout <<test[i] << "\n";

	}
	std::cout << "After" << "\n";
	preProcessArrayString(test);
	for (int i = 0; i < test.size(); i++)
	{
		std::cout << test[i] << "\n";

	}
	std::cout << "After dup" << "\n";

	removeDuplicates(test);

	for (int i = 0; i < test.size(); i++)
	{
		std::cout << test[i] << "\n";

	}
	return 0;
}
