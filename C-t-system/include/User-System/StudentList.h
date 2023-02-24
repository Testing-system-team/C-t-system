#pragma once
#include "User-System/Student.h"

namespace User_System
{
	class StudentList
	{
		std::vector<Student> students;
	public:
		void AddStudent(const Student& s);
		bool LoginExist(std::string login)const;
		void display()const;
		void displayByLogin(std::string& login)const;
		std::vector<Student>& GetStudents();
		std::vector<Student>::const_iterator begin() const;
		std::vector<Student>::const_iterator end() const;
	};
}
