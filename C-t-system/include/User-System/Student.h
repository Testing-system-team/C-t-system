#pragma once
#include "User-System/User.h"
#include "ID-System/ID_System.h"
#include "Security/HMAC_Generator.h"

namespace User_System
{
	class Student : public User, public ID_System::ID<Student>
	{
		//
		// ��� ����������
		//

		static Security::HMAC_Generator loginHashGen;
		static Security::HMAC_Generator passHashGen;
		// // //

		//
		// ���������
		//

		std::string name;
		std::string surname;
		std::string patronymic;
		std::string adress;
		std::string phoneNumber;
		// // //
	public:
		//
		// ������������
		//

		Student();
		Student(std::string name, std::string surname, std::string patronymic, std::string adress, std::string phoneNumber, std::string login, std::string password);
		Student(const pt::ptree& s);
		// // //

		// ����� �� �����
		void display() const;

		// ������ ����� ��������
		std::string GetName() const;

		// �������������� � property_tree
		operator pt::ptree() const override;
		operator Menu() override;

		//
		void ChangeName(std::string name_);
		void ChangeSurname(std::string surname_);
		void ChangePatronymic(std::string patronymic_);
		void ChangeAdress(std::string adress_);
		void ChangePhone(std::string phone_);
		void ChangeLogin(std::string surname_);
		void ChangePassword(std::string password_);
		//

		//
		// ������� ��� �����������
		//

		static const Security::HMAC_Generator getLoginHashGen();
		static const Security::HMAC_Generator getPassHashGen();
		// // //

		//
		// ������� ��� ������ � ������
		//

		void setLogin(const std::string login) override;
		void setPassword(const std::string pass) override;
		// // //
	};
}
