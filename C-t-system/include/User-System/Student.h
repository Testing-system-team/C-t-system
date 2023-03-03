#pragma once
#include "User-System/User.h"

namespace User_System
{
	class Student : public User
	{
		std::string name;
		std::string surname;
		std::string patronymic;
		std::string adress;
		std::string phoneNumber;
	public:
		Student();
		Student(std::string name, std::string surname, std::string patronymic, std::string adress, std::string phoneNumber, std::string login, std::string password);
		Student(const pt::ptree& s);
		void display() const;
		std::string GetName() const;
		operator pt::ptree() const override;
	};
}
