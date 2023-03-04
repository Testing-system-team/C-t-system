#pragma once
#include "test.h"
class category
{
	std::string name;
	std::vector<test> tests;
public:
	category();
	category(std::string name);
	void display();
	std::vector<test>& getTests();
};

