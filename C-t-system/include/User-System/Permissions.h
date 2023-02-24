#pragma once

namespace User_System
{
	struct Permissions
	{
		bool configureUsers;
		bool configureTests;
		bool passTests;
		bool watchStatistics;

		operator pt::ptree() const;
	};
}
