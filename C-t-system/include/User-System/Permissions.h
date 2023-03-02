#pragma once

namespace User_System
{
	struct Permissions
	{
		//
		// Разрешения пользователей
		//

		bool configureUsers;
		bool configureTests;
		bool passTests;
		bool watchStatistics;
		// // //

		// Преобразование в property_tree
		operator pt::ptree() const;
	};
}
