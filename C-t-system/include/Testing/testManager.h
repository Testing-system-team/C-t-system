#pragma once
#include "Testing/category.h"

namespace Testing
{
	class testManager : public Menu
	{
		std::vector<category>categories;
		std::string fileName;

		void _addCategory();
		void _categoryChange(tstring tchoice);
		void _categoryMenu(tstring tchoice, std::vector<category>::iterator category);
		void _addTest(category& category);
		void _changeCategoryName(category& category);
		void _testChange(tstring tchoice, category& category);
		void _testMenu(tstring tchoice, category& category, std::vector<test>::iterator test);
		void _addQuestion(test& test);
		void _changeTestName(test& test);
		void _questionsChange(tstring tchoice, test& test);
		void _questionMenu(tstring tchoice, test& test, std::vector<question>::iterator question);
		void _changeQuestionData(question& question);
		void _changeQuestionA(question& question);
		void _changeQuestionB(question& question);
		void _changeQuestionC(question& question);
		void _changeQuestionRightAnswer(question& question);
	public:
		testManager();
		testManager(std::string fileName);
		void display();
		void loadData();
		void saveData();
		void addcategory(const Testing::category & c);
		std::vector<category>& getcategories();

		void open(tstring tchoice = L"Ваш выбор: ") noexcept override;
	};
}


