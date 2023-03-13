#pragma once
#include "Testing/category.h"
namespace Testing
{
	class testManager
	{
		std::vector<category>categories;
		std::string fileName;
	public:
		testManager();
		testManager(std::string fileName);
		void display();
		void loadData();
		void saveData();
		void addcategory(const Testing::category & c);
		std::vector<category>& getcategories();
	};
}


