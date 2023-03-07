#pragma once
#include "User-System/StudentList.h"
#include "User-System/Admin.h"

namespace User_System
{
	class DataManager : public Menu
	{
		//
		// Аттрибуты
		//

		std::unique_ptr<User_System::Admin> admin;
		StudentList studentCatalog;
		std::string fileName;
		// // //
	public:
		// Конструктор
		DataManager();

		// Вывод на экран всех пользователей
		void display()const;

		// Вывод на экран пользователя по логину (вообще не знаю, когда это может использоватся)
		void displayByLogin(std::string login) const;

		// Загрузка пользователей из файла
		void loadData();

		//bool LoginExist(std::string _login)const;

		// Проверка на существование логина в файле
		bool FindLogin(std::string login)const;

		// Проверка на существование логина в файле (тоже не знаю, когда это может использоватся)
		bool CheckPassword(std::string password)const;

		// Добавление пользователя в менеджер данных
		void addUser(std::unique_ptr<User> user);

		void deleteUserById(int id);

		// Возвращает каталог студентов
		StudentList& getCatalog();

		// Возвращает админа
		std::unique_ptr<User_System::Admin>& getAdmin();

		// Открывает меню (немного костыль)
		void open(tstring tchoice = _TEXT("Ваш выбор: ")) override;
	};
}
