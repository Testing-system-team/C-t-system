#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
class question
{
	std::string data;
	std::string a, b, c; // варіанти відповіді
	std::string rightAnswer;
public:

	question()  ;
	question(std::string data, std::string a, std::string b, std::string c, std::string rightAnswer);
		
	std::string getrightAnswer();
	
	std::string getA();
	
	std::string getB();
	
	std::string getC();
	void setrightAnswer(std::string rightAnswer);
	void display();

	__declspec(property(get = getA)) std::string A;
	__declspec(property(get = getB)) std::string B;
	__declspec(property(get = getC)) std::string C;
	__declspec(property(get = getrightAnswer,put = setrightAnswer)) std::string RightAnswer;
	

	
};

