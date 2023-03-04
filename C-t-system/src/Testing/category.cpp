#include "Testing/category.h"
#include "Header.h"
category::category(): name("-")
{
}

category::category(std::string name): name(name)
{
}

void category::display()
{
	std::cout << u8"\n Розділ: " << name << "\n";
	for (auto t : tests)
	{
		t.display();
	}
}

std::vector<test>& category::getTests()
{
	return tests;
}
