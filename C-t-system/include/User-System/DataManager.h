#pragma once
#include "User-System/StudentList.h"
#include "User-System/Admin.h"

namespace User_System
{
	class DataManager : public Menu
	{
		//
		// ���������
		//

		std::unique_ptr<User_System::Admin> admin;
		StudentList studentCatalog;
		std::string fileName;
		// // //
	public:
		// �����������
		DataManager();
	

		// ����� �� ����� ���� �������������
		void display()const;

		// ����� �� ����� ������������ �� ������ (������ �� ����, ����� ��� ����� �������������)
		void displayByLogin(std::string login) const;

		// �������� ������������� �� �����
		void loadData();

		//bool LoginExist(std::string _login)const;

		// �������� �� ������������� ������ � �����
		bool FindLogin(std::string login)const;

		// �������� �� ������������� ������ � ����� (���� �� ����, ����� ��� ����� �������������)
		bool CheckPassword(std::string password)const;

		// ���������� ������������ � �������� ������
		void addUser(std::unique_ptr<User> user);

		void deleteUserById(int id);

		// ���������� ������� ���������
		StudentList& getCatalog();

		// ���������� ������
		std::unique_ptr<User_System::Admin>& getAdmin();

		// ��������� ���� (������� �������)
		void open(tstring tchoice = _TEXT("��� �����: ")) noexcept override;

		void SaveName(int id, std::string newName);
		void SaveSurname(int id, std::string newSurname);
		void SavePatronymic(int id, std::string newPatronymic);
		void SaveAdress(int id, std::string newAdress);
		void SavePhone(int id, std::string newPhone);
		void SaveLogin(int id, std::string newLogin);
		void SavePassword(int id, std::string newPassword);
	};

	
}
