#include "Header.h"
#include "Menu/Menu.h"

#undef max

#ifdef UNICODE
	std::wostream& tMenu::tcout = std::wcout;
	std::wistream& tMenu::tcin = std::wcin;
#else
	std::ostream& tMenu::tcout = std::cout;
	std::istream& tMenu::tcin = std::cin;
#endif

using namespace tMenu;

//
// Private
//

//Приватный конструктор
Menu::Menu() : key(_TEXT("Exit")), dyn_function(nullptr), menu_list(), back_key(_TEXT("Back")) {}

//Очистка от пустых меню
void Menu::_clean(Menu& iter)
{
	std::vector<Menu> temp;
	for (auto& subiter : iter.menu_list)
	{
		if (subiter.is_menu_list() && subiter.menu_list.size() > 1)
			_clean(subiter);
		if (subiter.is_function() || subiter.menu_list.size() != 1)
			temp.push_back(subiter);
	}
	iter.menu_list = temp;
}

//
// Public
//

//
// Конструкторы
//

Menu::Menu(const tstring name) : key(name), dyn_function(nullptr), menu_list({Menu()}), back_key(_TEXT("Back")) {}

Menu::Menu(const tstring name, const function_type &dyn_function) : key(name), dyn_function(dyn_function), menu_list({ Menu() }), back_key(_TEXT("Back")) {}

Menu::Menu(const tstring name, std::vector<Menu> menu_list) : key(name), dyn_function(nullptr), menu_list({ Menu() }), back_key(_TEXT("Back"))
{
	for (auto iter = menu_list.begin();
		iter != menu_list.end();
		iter++)
	{
		this->menu_list.push_back(*iter);
		this->menu_list[menu_list.size()].exit_name = back_key;
		this->menu_list[menu_list.size() - 1].back_key = back_key;
	}
}

//
// Методы begin и end
//

std::vector<Menu>::iterator Menu::begin()
{
	if (menu_list.size())
		return (menu_list.begin()) + 1;
	else
		return menu_list.begin();
}

std::vector<Menu>::iterator Menu::end()
{
	return menu_list.end();
}

std::vector<Menu>::const_iterator Menu::begin() const
{
	if (menu_list.size())
		return (menu_list.begin()) + 1;
	else
		return menu_list.begin();
}

std::vector<Menu>::const_iterator Menu::end() const
{
	return menu_list.end();
}

//
// Перегрузка операторов
//

Menu& Menu::operator=(const function_type &dyn_function)
{
	this->dyn_function = dyn_function;
	return *this;
}

Menu& Menu::operator=(const std::vector<Menu> menu_list)
{
	this->dyn_function = nullptr;
	clear();
	for (auto iter = menu_list.begin();
		iter != menu_list.end();
		iter++)
	{
		this->menu_list.push_back(*iter);
		(this->menu_list.end() - 1)->exit_name = back_key;
	}
	return *this;
}


Menu& Menu::operator+=(const Menu menu)
{
	menu_list.push_back(menu);
	this->menu_list[menu_list.size() - 1].exit_name = back_key;
	this->menu_list[menu_list.size() - 1].back_key = back_key;
	return *this;
}

Menu& Menu::operator<<(const Menu menu)
{
	*this += menu;
	return *this;
}

Menu& Menu::operator[](const int index)
{
	if (index > 1 && index < menu_list.size()) return menu_list[index];
	else return *(Menu*)nullptr;
}

Menu& Menu::operator[](const TCHAR* name)
{
	return (*this)[tstring(name)];
}

Menu& Menu::operator[](tstring name)
{
	for (std::vector<Menu>::iterator iter = menu_list.begin() + 1;
		iter != menu_list.end();
		iter++)
	{
		if (((Menu)*iter).key == name) return *iter;
	}
	menu_list.push_back(name);
	this->menu_list[menu_list.size() - 1].exit_name = back_key;
	this->menu_list[menu_list.size() - 1].back_key = back_key;
	return this->menu_list[menu_list.size() - 1];
}

Menu Menu::operator--()
{
	return pop_back();
}

//
// Преобразования
//

Menu::operator bool() const { return menu_list.size() > 1; }

Menu::operator const std::vector<Menu>() const
{
	return menu_list;
}

//
// Обычные методы
//

bool Menu::is_function() const
{
	return dyn_function != nullptr;
}

bool Menu::is_menu_list() const
{
	return dyn_function == nullptr && menu_list.size();
}

bool Menu::contains(const tstring name) const
{
	for (auto menu : menu_list) if (menu.key == name) return true;
	return false;
}

Menu& Menu::push_back(const Menu menu)
{
	return *this += menu;
}

Menu Menu::pop_back()
{
	if (menu_list.size() > 1)
	{
		Menu temp(menu_list[menu_list.size() - 1]); 
		menu_list.pop_back();
		return temp;
	}
	return (Menu)nullptr;
}

int Menu::size() const
{
	if (menu_list.size())
		return menu_list.size() - 1;
	return 0;
}

void Menu::display() const
{
	#ifdef UNICODE
	auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
	#endif

	tcout << key << ":\n";

	int i = 1;
	for (std::vector<Menu>::const_iterator iter = menu_list.begin() + i;
		iter != this->menu_list.end();
		iter++, i++)
	{
		tcout << i << ". " << ((const Menu)*iter).key << '\n';
	}

	tcout << "0. " << menu_list[0].key << '\n';

	#ifdef UNICODE
	_setmode(_fileno(stdout), prev_out);
	#endif
}

void Menu::open(const tstring tchoice)
{
	_clean(*this);

	exit = 0;
	do
	{
		#ifdef UNICODE
		auto prev_out = _setmode(_fileno(stdout), _O_U8TEXT);
		auto prev_in = _setmode(_fileno(stdin), _O_U16TEXT);
		#endif

		int choice = -1;
		system("cls");
		display();
		tcout << '\n' << tchoice;

		tcin >> choice;
		tcin.ignore();
		try
		{
			if (tcin.fail())
				throw std::ios_base::failure("Input fail");
			else if (choice < 0 || choice >= menu_list.size())
				throw std::runtime_error("Wrong choice");
		}
		catch (std::ios_base::failure& ex)
		{
			system("cls");
			std::cerr << "> std::ios_base::failure: " << ex.what() << "\n\n";
			system("pause");

			tcin.clear();
			tcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			choice = -1;
		}
		catch (std::runtime_error& ex)
		{
			system("cls");
			std::cerr << "> std::runtime_error: " << ex.what() << "\n\n";
			system("pause");
		}

		#ifdef UNICODE
		_setmode(_fileno(stdout), prev_out);
		_setmode(_fileno(stdin), prev_in);
		#endif

		if (choice > 0 && choice < menu_list.size())
		{
			if (menu_list[choice].is_function())
			{
				system("cls");
				menu_list[choice].dyn_function();
			}
			else menu_list[choice].open(tchoice);
		}
		else if (!choice) exit = 1;
	} while (!exit);

	system("cls");
}

void Menu::close()
{
	exit = 1;
}

void Menu::clear()
{
	if (menu_list.size())
		menu_list.erase(menu_list.begin() + 1, menu_list.end());
}

//
// Геттеры/cеттеры
//

tstring Menu::getName() const
{
	return key;
}

void Menu::setName(const tstring name)
{
	key = name;
}

tstring Menu::get_exit_name() const
{
	if (!is_function() && !is_menu_list())
		return key;
	else
		return menu_list[0].key;
}

void Menu::rename_exit(const tstring name)
{
	if (!is_function() && !is_menu_list())
		key = name;
	else
		menu_list[0].key = name;
}

tstring Menu::get_back_name() const { return back_key; }

void Menu::rename_back(const tstring name) { back_key = name; }

std::vector<Menu>& Menu::getMenuList()
{
	return menu_list;
}
