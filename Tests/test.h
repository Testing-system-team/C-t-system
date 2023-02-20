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
	float percentage;
public:
	
	test();

	test(std::string name, int numOfQuestions);


	void addQuestion(const question& q);


	void display();

	void startTest();
	

	void displayResult();
	void loadTest();
	void saveTest();
	void saveResult();



};

