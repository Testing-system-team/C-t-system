#include "Header.h"
#include "Testing/category.h"

using namespace Testing;

category::category(): name("-")
{
}

category::category(std::string name): name(name)
{
}
category::operator pt::ptree()
{
	pt::ptree categorytags;
	categorytags.put("name", name);
	for (test& t : tests)
	{
		categorytags.add_child("Tests.test", t);
	}
	return categorytags;
}
void category::display()
{
	std::cout << u8"\n Розділ: " << name << "\n";
	if (tests.size() == 0)
	{
		std::cout << u8"В цьому розділі поки що відсутні тести\n";
	}
	else
	{
		for (auto &t : tests)
		{
			t.display();
		}
	}
}

std::vector<test>& category::getTests()
{
	return tests;
}

void Testing::category::addtest(const test& t)
{
	tests.push_back(t);
}

std::string Testing::category::getname()
{
	return name;
}
