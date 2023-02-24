#pragma once
#include "question.h"
#include <vector>

class test
{
	std::string name;
	std::vector <question> questions;
	int numOfQuestions;
	int result;
	int mark;
	double percentage;
public:
	
	test();

	test(std::string name, int numOfQuestions);


	void addQuestion(const question& q);


	void display();

	void startTest();
	

	void displayResult();

	int getResult();
	int getMark();
	double getPercentage();
	std::vector<question> getQuestions();



};

