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

std::string Testing::question::getData()
{
	return data;
}

std::string question::getC()
{
	return c;
}
void Testing::question::setData(const std::string data)
{
	this->data = data;
}
void Testing::question::setA(const std::string a)
{
	this->a = a;
}
void Testing::question::setB(const std::string b)
{
	this->b = b;
}
void Testing::question::setC(const std::string c)
{
	this->c = c;
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

Testing::question::operator pt::ptree()
{
	pt::ptree questiontags;
	questiontags.put("data", data);
	questiontags.put("a", a);
	questiontags.put("b", b);
	questiontags.put("c", c);
	questiontags.put("rightAnswer", rightAnswer);
	return questiontags;
}
