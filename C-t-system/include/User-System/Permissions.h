#pragma once

namespace User_System
{
	struct Permissions
	{
		//
		// ���������� �������������
		//

		bool configureUsers;
		bool configureTests;
		bool passTests;
		bool watchStatistics;
		// // //

		// �������������� � property_tree
		operator pt::ptree() const;
	};
}
