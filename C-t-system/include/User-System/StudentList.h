#pragma once
#include "User-System/Student.h"

namespace User_System
{
	class StudentList
	{
		// Аттрибут
		std::vector<std::unique_ptr<Student>> students;
	public:
		// Добавлет студента в кталог
		void AddStudent(std::unique_ptr<Student> s);

		// Проверка на существование логина среди какталога студентов
		bool LoginExist(std::string login)const;

		// Выводит всех студентов
		void display()const;

		// Вывод студента по логину
		void displayByLogin(std::string& login)const;

		// Геттер вектора студентов
		std::vector<std::unique_ptr<Student>>& GetStudents();

		//
		// Методы begin и end
		//

		std::vector<std::unique_ptr<Student>>::const_iterator begin() const;
		std::vector<std::unique_ptr<Student>>::const_iterator end() const;
		// // //
	};
}
