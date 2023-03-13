#pragma once
#include "test.h"

namespace Testing
{
	class category
	{
		std::string name;
		std::vector<test> tests;
	public:
		category();
		category(std::string name);
		void display();
		std::vector<test>& getTests();
		void addtest(const test& t);
		std::string getname();
		operator pt::ptree();
	};
}
