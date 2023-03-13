#pragma once
#include "question.h"
#include "Menu/Menu.h"

namespace Testing
{
	class test
	{
		std::string name;
		std::vector <question> questions;
		
		int result;
		int mark;
		double percentage;
	public:

		test();

		test(std::string name);

		operator Menu();

		void addQuestion(const question& q);


		void display();

		void startTest();


		void displayResult();
		operator pt::ptree();
		int getResult();
		int getMark();
		std::string getname();
		double getPercentage();
		std::vector<question>& getQuestions();
	};
}
