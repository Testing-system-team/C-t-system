#include "Header.h"
#include "Testing/category.h"

using namespace Testing;

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
