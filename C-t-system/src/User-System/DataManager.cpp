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

void User_System::DataManager::open(tstring tchoice) noexcept
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
			if (tMenu::tcin.fail())
				throw std::ios_base::failure("Bad input");
			else if (choice < 0 || choice > users.size())
				throw std::runtime_error("Bad choice");

			if (choice)
			{
				// Самая главная часть этого метода
				/* 
					Тут добавляются дополнительные варианты меню, к меню пользователей
				*/
				Menu userMenu = *users[choice - 1];
				userMenu.exit_name = back_name;
				userMenu.back_name = back_name;
				#undef max
				if (auto user = dynamic_cast<Student*>(users[choice - 1]))
				{
					userMenu[L"Изменить"][L"Имя"] = [&]()
					{

						std::string newName;
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::cout << "Enter new Name-> ";
						
						std::getline(std::cin, newName);
						user->ChangeName(newName);
						
						SaveName(user->id, newName);
						system("pause");
					};
					userMenu[L"Изменить"][L"Фамилию"] = [&]()
					{
						std::string newSurname;
						std::cout << "Enter new Surname-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newSurname);
						user->ChangeSurname(newSurname);

						SaveSurname(user->id, newSurname);
						system("pause");
					};
					userMenu[L"Изменить"][L"Отчество"] = [&]()
					{
						std::string newPatronymic;
						std::cout << "Enter new Patronymic-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newPatronymic);
						user->ChangePatronymic(newPatronymic);

						SavePatronymic(user->id, newPatronymic);
						system("pause");
					};
					userMenu[L"Изменить"][L"Адрес"] = [&]()
					{
						std::string newAdress;
						std::cout << "Enter new Adress-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newAdress);
						user->ChangeAdress(newAdress);
						
						SaveAdress(user->id, newAdress);
						system("pause");
					};
					userMenu[L"Изменить"][L"Номер Телефона"] = [&]()
					{
						std::string newPhone;
						std::cout << "Enter new Phone-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newPhone);
						user->ChangePhone(newPhone);

						SavePhone(user->id, newPhone);
						system("pause");
					};
					userMenu[L"Изменить"][L"Логин"] = [&]()
					{
						std::string newLogin;
						std::cout << "Enter new Login-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newLogin);
						user->ChangeLogin(newLogin);

						SaveLogin(user->id, newLogin);
						system("pause");
					};
					userMenu[L"Изменить"][L"Пароль"] = [&]()
					{
						std::string newPassword;
						std::cout << "Enter new Password-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newPassword);
						user->ChangePassword(newPassword);

						SavePassword(user->id, newPassword);
						system("pause");
					};
					userMenu[L"Удалить"] = [&]()
					{
						deleteUserById(user->id);
						userMenu.close();
					};
				}
				else if (auto user = dynamic_cast<Admin*>(users[choice - 1]))
				{
					userMenu[L"Изменить"][L"Логин"] = [&]()
					{
						std::string newLogin;
						std::cout << "Enter new Login-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newLogin);
						user->login = newLogin;

						SaveLogin(user->id, newLogin);
						system("pause");
					};
					userMenu[L"Изменить"][L"Пароль"] = [&]()
					{
						std::string newPassword;
						std::cout << "Enter new Password-> ";
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\0');
						std::getline(std::cin, newPassword);
						user->password = newPassword;

						SavePassword(user->id, newPassword);
						system("pause");
					};
				}
				
				
				userMenu.open(tchoice);
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

void DataManager::SaveName(int id,std::string newName)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if(idXml==id)
		{
			
			//tree.put("name" , newName);
			user.second.put("name", newName);
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
	
}

void User_System::DataManager::SaveSurname(int id, std::string newSurname)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if (idXml == id)
		{

			//tree.put("name" , newName);
			user.second.put("surname", newSurname);
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
}

void User_System::DataManager::SavePatronymic(int id, std::string newPatronymic)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if (idXml == id)
		{

			//tree.put("name" , newName);
			user.second.put("patronymic", newPatronymic);
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
}
void User_System::DataManager::SaveAdress(int id, std::string newAdress)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if (idXml == id)
		{

			//tree.put("name" , newName);
			user.second.put("adress", newAdress);
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
}
void User_System::DataManager::SavePhone(int id, std::string newPhone)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if (idXml == id)
		{

			//tree.put("name" , newName);
			user.second.put("phoneNumber", newPhone);
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
}
void User_System::DataManager::SaveLogin(int id, std::string newLogin)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if (idXml == id)
		{

			//tree.put("name" , newName);
			if (user.first == convertTypeName(typeid(Student).name()))
				user.second.put("loginHash", Student::getLoginHashGen().generate_HMAC(newLogin));
			else if (user.first == convertTypeName(typeid(Admin).name()))
				user.second.put("loginHash", Admin::getLoginHashGen().generate_HMAC(newLogin));
			
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
}
void User_System::DataManager::SavePassword(int id, std::string newPassword)
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	pt::xml_writer_settings<std::string> settings('\t', 1);
	BOOST_FOREACH(auto & user, tree.get_child("Users"))
	{
		int idXml = user.second.get<int>("ID");
		if (idXml == id)
		{

			//tree.put("name" , newName);
			
			if (user.first == convertTypeName(typeid(Student).name()))
				user.second.put("passwordHash", Student::getPassHashGen().generate_HMAC(newPassword));
			else if (user.first == convertTypeName(typeid(Admin).name()))
				user.second.put("passwordHash", Admin::getPassHashGen().generate_HMAC(newPassword));
			//user.second.put_value("name", newName);
			break;
		}
	}
	write_xml(fileName, tree, std::locale(), settings);
}
