#pragma once
#include "Testing/test.h"

namespace Testing::Statistic
{
	class Statistic
	{
		int userId;
		std::string categoryName;
		std::string testName;
		size_t questionsCount;
		int result;
		double percentage;
		int mark;
	public:
		Statistic();
		Statistic(const int userId, const std::string categoryName, test test);
		Statistic(const pt::ptree tree);

		void display() const;

		operator pt::ptree() const;

		int getUserId() const;
	};
}
