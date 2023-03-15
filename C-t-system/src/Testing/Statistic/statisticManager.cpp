#include "Header.h"
#include "Testing/Statistic/statisticManager.h"

Testing::Statistic::statisticManager::statisticManager() : fileName("Statistic.xml")
{
	loadData();
}

void Testing::Statistic::statisticManager::loadData()
{
	statistics.clear();

	if (std::filesystem::exists(fileName))
	{
		pt::ptree tree;
		pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);

		try
		{
			BOOST_FOREACH(auto & statistic, tree.get_child("Statistics"))
			{
				statistics.push_back(statistic.second);
			}
		}
		catch (pt::ptree_bad_path&) {}
	}
}

void Testing::Statistic::statisticManager::saveData() const
{
	pt::xml_writer_settings<std::string> settings('\t', 1);
	pt::ptree tree;

	for (auto& statistic : statistics)
		tree.add_child("Statistics.statistic", statistic);

	pt::write_xml(fileName, tree, std::locale(), settings);
}

void Testing::Statistic::statisticManager::addStatistic(const Statistic statistic)
{
	statistics.push_back(statistic);
	saveData();
}

void Testing::Statistic::statisticManager::deleteUsersStatistics(const int userId)
{
	auto findCondition = [userId](auto& statistic) { return userId == statistic.getUserId(); };
	auto findFunc = [&]() { return std::find_if(statistics.begin(), statistics.end(), findCondition); };
	for (auto statistic = findFunc(); statistic != statistics.end(); statistic = findFunc())
		statistics.erase(statistic);
	saveData();
}

std::vector<Testing::Statistic::Statistic>& Testing::Statistic::statisticManager::getStatistics()
{
	return statistics;
}
