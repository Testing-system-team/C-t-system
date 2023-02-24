#include "Header.h"
#include "User-System/StudentList.h"
#include "User-System/Student.h"

using namespace User_System;

void StudentList::AddStudent(const Student& s)
{
	students.push_back(s);
	
}
bool StudentList::LoginExist(std::string login)const
{
	for (auto iter : students)
		if (login == iter.login)
			return true;
	return false;
}
void StudentList::display()const
{
	if(students.size())
	{
		for (auto s : students)
		{
			std::cout << "\n--------\n";
			s.display();
		}
	}
}
void StudentList::displayByLogin(std::string& login)const
{
	if (students.size())
	{
		for (auto s : students)
			if(s.login==login)
				s.display();	
	}
}
std::vector<Student>& StudentList::GetStudents()
{
	return students;
}
std::vector<Student>::const_iterator StudentList::begin() const
{
	return students.begin();
}

std::vector<Student>::const_iterator StudentList::end() const
{
	return students.end();
}
