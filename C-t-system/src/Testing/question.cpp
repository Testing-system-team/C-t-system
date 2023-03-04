#include "Header.h"
#include "Testing/question.h"

using namespace Testing;

question::question() : data("question"), a("right"), b("wrong"), c("wrong"), rightAnswer("right") {}


question:: question(std::string data, std::string a, std::string b, std::string c, std::string rightAnswer)
	: data(data), a(a), b(b), c(c), rightAnswer(rightAnswer) {}


std::string question:: getrightAnswer()
{
	return rightAnswer;
}

std::string question::getA()
{
	return a;
}

std::string question::getB()
{
	return b;
}

std::string question::getC()
{
	return c;
}
void question::setrightAnswer(std::string rightAnswer)
{
	this->rightAnswer = rightAnswer;
}

void question::display()
{
	std::cout << "\n" << data << "\n";
	std::cout << " a:" << a << " b:" << b << " c:" << c << "\n";
}
