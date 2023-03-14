#include "Header.h"
#include "Testing/Statistic/Statistic.h"

Testing::Statistic::Statistic::Statistic() : userId(0), categoryName(""), testName(""), questionsCount(0), result(0), percentage(0.0), mark(0) {}

Testing::Statistic::Statistic::Statistic(const int userId, const std::string categoryName, test test) :
	userId(userId), 
	categoryName(categoryName),
	testName(test.getname()),
	questionsCount(test.getQuestions().size()),
	result(test.getResult()),
	percentage(test.getPercentage()),
	mark(test.getMark())
{}

Testing::Statistic::Statistic::Statistic(const pt::ptree tree) :
	userId(tree.get<int>("userId")),
	categoryName(tree.get<std::string>("categoryName")),
	testName(tree.get<std::string>("testName")),
	questionsCount(tree.get<size_t>("questionsCount")),
	result(tree.get<int>("result")),
	percentage(tree.get<double>("percentage")),
	mark(tree.get<int>("mark"))
{}

void Testing::Statistic::Statistic::display() const
{
	std::cout << u8"Сделано пользователем с ИД: " << userId << '\n'
		<< u8"Название категории: " << categoryName << '\n'
		<< u8"Название теста: " << testName << '\n'
		<< u8"Количество вопросов: " << questionsCount << '\n'
		<< '\n'
		<< u8"Результаты пользователя:\n"
		<< u8"Отвечено правильно на " << result << u8" вопросов\n"
		<< u8"Оценка в процентах: " << percentage << "%\n"
		<< u8"Оценка по 12 бальной системе: " << mark << u8" балов\n";
}


Testing::Statistic::Statistic::operator pt::ptree() const
{
	pt::ptree tree;
	tree.put("userId", userId);
	tree.put("categoryName", categoryName);
	tree.put("testName", testName);
	tree.put("questionsCount", questionsCount);
	tree.put("result", result);
	tree.put("percentage", percentage);
	tree.put("mark", mark);
	return tree;
}

int Testing::Statistic::Statistic::getUserId() const
{
	return userId;
}
