#pragma once
#include "User-System/Student.h"

namespace User_System
{
	class StudentList
	{
		std::vector<std::unique_ptr<Student>> students;
	public:
		void AddStudent(std::unique_ptr<Student> s);
		bool LoginExist(std::string login)const;
		void display()const;
		void displayByLogin(std::string& login)const;
		std::vector<std::unique_ptr<Student>>& GetStudents();
		std::vector<std::unique_ptr<Student>>::const_iterator begin() const;
		std::vector<std::unique_ptr<Student>>::const_iterator end() const;
	};
}
