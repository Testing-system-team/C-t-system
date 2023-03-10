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

		void ChangeName(std::string name_, int position);
		void ChangeSurname(std::string surname_, int position);
		void ChangePatronymic(std::string patronymic_, int position);
		void ChangeAdress(std::string adress_, int position);
		void ChangePhone(std::string phone_, int position);
		void ChangeLogin(std::string login_, int position);
		void ChangePassword(std::string password_, int position);

		//
		// Методы begin и end
		//

		std::vector<std::unique_ptr<Student>>::const_iterator begin() const;
		std::vector<std::unique_ptr<Student>>::const_iterator end() const;
		// // //
		int sizeOfList()const;

	
	};
	
}
