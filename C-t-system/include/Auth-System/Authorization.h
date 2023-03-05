#pragma once
#include "User-System/DataManager.h"

namespace Auth_System
{
	class Authorization
	{
		// ������� �������������� ������������
		User_System::User* currentUser;

		// ��������� �� ��������� ������
		User_System::DataManager* managerPtr;

		// ����������� ��������������
		void _firstLogin();
	public:
		// �����������
		Authorization(User_System::DataManager* managerPtr);

		// ��������� ���� �����������
		void open();

		// ����������� ��������
		void studentRegistration();

		// ����
		void login();

		// ���������� �������� ������������
		User_System::User* getCurrentUser();
	};
}
