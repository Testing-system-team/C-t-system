#include "question.h"



question::question() : Question("question"), a("right"), b("wrong"), c("wrong"), rightAnswer("right") {}


question:: question(std::string Question, std::string a, std::string b, std::string c, std::string rightAnswer)
	: Question(Question), a(a), b(b), c(c), rightAnswer(rightAnswer) {}


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
void question::display()
{
	std::cout << "\n" << Question << "\n";
	std::cout << " a:" << a << " b:" << b << " c:" << c << "\n";
}
