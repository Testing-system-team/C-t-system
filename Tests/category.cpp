#include "category.h"

category::category(): name("-")
{
}

category::category(std::string name): name(name)
{
}

void category::display()
{
	std::cout << u8"\n �����: " << name << "\n";
	for (auto t : tests)
	{
		t.display();
	}
}

std::vector<test> category::getTests()
{
	return tests;
}
