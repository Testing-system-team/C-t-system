#include "Header.h"
#include "User-System/DataManager.h"
#include "User-System/Student.h"
#include "User-System/StudentList.h"
#include "User-System/User_System.h"
#include "Security/HMAC_Generator.h"


using namespace User_System;

DataManager::DataManager() : Menu(L"Пользователи"), fileName("Users.xml") { loadData(); exit_name = L"Выход"; back_name = L"Назад"; }

void DataManager::display() const
{
	if (admin) admin->Display();
	studentCatalog.display();
}
void DataManager::displayByLogin(std::string login) const
{
	if (admin && Admin::getLoginHashGen().compare_HMAC(login, admin->login))
		admin->Display();
	else
		studentCatalog.displayByLogin(login);
}

void DataManager::loadData()
{
	admin.reset();
	studentCatalog.GetStudents().clear();

	if (std::filesystem::exists(fileName))
	{
		pt::ptree tree;

		pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);

		try
		{
			BOOST_FOREACH(auto & user, tree.get_child("Users"))
			{
				if (user.first == convertTypeName(typeid(Student).name()))
					studentCatalog.AddStudent(std::make_unique<Student>(user.second));
				else if (user.first == convertTypeName(typeid(Admin).name()))
					admin = std::make_unique<Admin>(user.second);
			}
		}
		catch (pt::ptree_bad_path) {}
	}
}



bool DataManager::FindLogin(std::string login) const
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	try
	{
		BOOST_FOREACH(auto & user, tree.get_child("Users"))
		{
			if (user.first == convertTypeName(typeid(Student).name()))
			{
				if (Student::getLoginHashGen().compare_HMAC(login, user.second.get<std::string>("loginHash")))
					return true;
			}
			else if (user.first == convertTypeName(typeid(Admin).name()))
				if (Admin::getLoginHashGen().compare_HMAC(login, user.second.get<std::string>("loginHash")))
					return true;
		}
	}
	catch (pt::ptree_bad_path) {}
	return false;
	
}

bool DataManager::CheckPassword(std::string password) const
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	try
	{
		BOOST_FOREACH(auto & user, tree.get_child("Users"))
		{
			if (user.first == convertTypeName(typeid(Student).name()))
			{
				if (Student::getPassHashGen().compare_HMAC(password, user.second.get<std::string>("passwordHash")))
					return true;
			}
			else if (user.first == convertTypeName(typeid(Admin).name()))
				if (Admin::getPassHashGen().compare_HMAC(password, user.second.get<std::string>("passwordHash")))
					return true;
		}
	}
	catch (pt::ptree_bad_path) {}
	return false;
}

void User_System::DataManager::addUser(std::unique_ptr<User> user)
{
	pt::xml_writer_settings<std::string> settings('\t', 1);
	pt::ptree tree;
	if (std::filesystem::exists(fileName)) pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	tree.add_child("Users." + convertTypeName(typeid(*user).name()), *user);

	write_xml(fileName, tree, std::locale(), settings);

	if (typeid(*user) == typeid(Student)) studentCatalog.AddStudent(std::move((std::unique_ptr<User_System::Student>&)user));
	else if (typeid(*user) == typeid(Admin)) admin = std::move((std::unique_ptr<User_System::Admin>&)(user));
}

void User_System::DataManager::deleteUserById(int id)
{
	if (auto result = std::find_if(studentCatalog.GetStudents().begin(), studentCatalog.GetStudents().end(),
		[id](std::unique_ptr<Student>& student) { return student->id == id; }); result != studentCatalog.GetStudents().end())
	{
		pt::xml_writer_settings<std::string> settings('\t', 1);
		pt::ptree tree;
		pt::ptree users_tree;
		pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
		users_tree = tree.get_child("Users");
		tree.get_child("Users").erase(std::find_if(tree.get_child("Users").begin(), tree.get_child("Users").end(),
			[id](std::pair<const std::string, pt::ptree> pair) 
			{ return pair.second.get<int>("ID") == id; }));

		studentCatalog.GetStudents().erase(result);

		write_xml(fileName, tree, std::locale(), settings);
	}
}

StudentList& DataManager::getCatalog()
{
	return studentCatalog;
}

std::unique_ptr<User_System::Admin>& User_System::DataManager::getAdmin()
{
	return admin;
}

void User_System::DataManager::open(tstring tchoice)
{
	exit = 0;

	while (!exit)
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		std::vector<User*> users;
		int choice = 0;

		system("cls");

		tMenu::tcout << name << ": " << '\n';

		if (admin)
		{
			tMenu::tcout << users.size() + 1 << ". " << ((Menu)*admin).name << '\n';
			users.push_back(admin.get());
		}
		for (auto& student : studentCatalog.GetStudents())
		{
			tMenu::tcout << users.size() + 1 << ". " << ((Menu)*student).name << '\n';
			users.push_back(student.get());
		}

		tMenu::tcout << "0. " << exit_name << '\n'
			<< '\n'

			<< tchoice;
		tMenu::tcin >> choice;

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif

		try
		{
			if (tMenu::tcout.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice > users.size())
				throw std::runtime_error("Bad choice");

			if (choice)
			{
				// Самая главная часть этого метода
				/* 
					Тут добавляются дополнительные варианты меню, к меню пользователей
				*/
				Menu temp = *users[choice - 1];
				temp.exit_name = back_name;
				temp.back_name = back_name;

				if (typeid(*users[choice - 1]) == typeid(Student))
				{
					temp[L"Удалить"] = [&]() 
						{ 
							deleteUserById(dynamic_cast<Student*>(users[choice - 1])->id);
							temp.close();
						};
				}

				temp.open(tchoice);
				// // //
			}
			else exit = 1;
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "std::ios_base::failure: " << ex.what() << '\n';
			system("pause");

			tcin.clear();
			tcin.ignore();
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "std::runtime_error: " << ex.what() << '\n';
			system("pause");
		}
	}
}


