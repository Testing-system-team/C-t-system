#pragma once
#include "User-System/User.h"
#include "ID-System/ID_System.h"
#include "Security/HMAC_Generator.h"

namespace User_System
{
	class Student : public User, public ID_System::ID<Student>
	{
		//
		// Хэш генераторы
		//

		static Security::HMAC_Generator loginHashGen;
		static Security::HMAC_Generator passHashGen;
		// // //

		//
		// Аттрибуты
		//

		std::string name;
		std::string surname;
		std::string patronymic;
		std::string adress;
		std::string phoneNumber;
		// // //
	public:
		//
		// Конструкторы
		//

		Student();
		Student(std::string name, std::string surname, std::string patronymic, std::string adress, std::string phoneNumber, std::string login, std::string password);
		Student(const pt::ptree& s);
		// // //

		// Вывод на экран
		void display() const;

		// Геттер имени студента
		std::string GetName() const;

		// Преобразование в property_tree
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
		// Геттеры хэш генераторов
		//

		static const Security::HMAC_Generator getLoginHashGen();
		static const Security::HMAC_Generator getPassHashGen();
		// // //

		//
		// Сеттеры для логина и пароля
		//

		void setLogin(const std::string login) override;
		void setPassword(const std::string pass) override;
		// // //
	};
}
