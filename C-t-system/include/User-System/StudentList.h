#pragma once
#include "User-System/Student.h"

namespace User_System
{
	class StudentList
	{
		// ��������
		std::vector<std::unique_ptr<Student>> students;
	public:
		// �������� �������� � ������
		void AddStudent(std::unique_ptr<Student> s);

		// �������� �� ������������� ������ ����� ��������� ���������
		bool LoginExist(std::string login)const;

		// ������� ���� ���������
		void display()const;

		// ����� �������� �� ������
		void displayByLogin(std::string& login)const;

		// ������ ������� ���������
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
		// ������ begin � end
		//

		std::vector<std::unique_ptr<Student>>::const_iterator begin() const;
		std::vector<std::unique_ptr<Student>>::const_iterator end() const;
		// // //
		int sizeOfList()const;

	
	};
	
}
