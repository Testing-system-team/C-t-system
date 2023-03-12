#include "Header.h"
#include "User-System/StudentList.h"

using namespace User_System;

void StudentList::AddStudent(std::unique_ptr<Student> s)
{
	students.push_back(std::move(s));
}

bool StudentList::LoginExist(std::string login)const
{
	for (auto& iter : students)
		if (Student::getLoginHashGen().compare_HMAC(login, iter->login))
			return true;
	return false;
}

void StudentList::display()const
{
	for (auto& s : students)
	{
		std::cout << "\n--------\n";
		s->display();
	}
}

void StudentList::displayByLogin(std::string& login)const
{
	for (auto& s : students)
		if (Student::getLoginHashGen().compare_HMAC(login, s->login))
			s->display();
}

std::vector<std::unique_ptr<Student>>& StudentList::GetStudents()
{
	return students;
}

void User_System::StudentList::ChangeName(std::string name_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if(i==position-2)
		{
			students[i]->ChangeName(name_);
		}
	}	
}

void User_System::StudentList::ChangeSurname(std::string surname_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if (i == position - 2)
		{
			students[i]->ChangeSurname(surname_);
		}
	}
}

void User_System::StudentList::ChangePatronymic(std::string patronymic_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if (i == position - 2)
		{
			students[i]->ChangePatronymic(patronymic_);
		}
	}
}

void User_System::StudentList::ChangeAdress(std::string adress_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if (i == position - 2)
		{
			students[i]->ChangeAdress(adress_);
		}
	}
}

void User_System::StudentList::ChangePhone(std::string phone_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if (i == position - 2)
		{
			students[i]->ChangePhone(phone_);
		}
	}
}

void User_System::StudentList::ChangeLogin(std::string login_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if (i == position - 2)
		{
			students[i]->ChangeLogin(login_);
		}
	}
}

void User_System::StudentList::ChangePassword(std::string password_, int position)
{
	for (int i = 0; i < students.size(); i++)
	{
		if (i == position - 2)
		{
			students[i]->ChangePassword(password_);
		}
	}
}

std::vector<std::unique_ptr<Student>>::const_iterator StudentList::begin() const
{
	return students.begin();
}

std::vector<std::unique_ptr<Student>>::const_iterator StudentList::end() const
{
	return students.end();
}

int User_System::StudentList::sizeOfList() const
{
	return students.size();
}




