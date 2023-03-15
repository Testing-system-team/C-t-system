#pragma once
#include "Testing/Statistic/Statistic.h"

namespace Testing::Statistic
{
	class statisticManager
	{
		std::string fileName;
		std::vector<Statistic> statistics;
	public:
		statisticManager();

		void loadData();

		void saveData() const;

		void addStatistic(const Statistic statistic);
		void deleteUsersStatistics(const int userId);

		std::vector<Statistic>& getStatistics();
	};
}
