#pragma once

class ID_System
{
public:
	// Класс ID, его нужно наследовать сущностью, которая долнжна входить в ID систему
	template<class T>
	class ID
	{
		//
		// Аттрибуты ID
		//

		int _id;
		std::string _typeName;
		// // //
	public:
		//
		// Конструкторы
		//

		ID();

		// При 0 значении, ID не входит в систему
		ID(const int id);

		ID(const ID&) = delete;
		ID(ID&& id);
		// // //

		// Деструктор
		virtual ~ID();

		//
		// Операторы присвоения
		//

		void operator=(const ID&) = delete;
		ID& operator=(ID&& id);
		// // //

		//
		// Геттеры
		//

		int getID() const;
		std::string getTypeName() const;
		// // //

		//
		// Декларация property
		//

		__declspec(property(get = getID)) int id;
		__declspec(property(get = getTypeName)) std::string typeName;
		// // //
	};

	//
	// Методы begin и end
	//

	static std::map<int, ID<void>*>::const_iterator begin();
	static std::map<int, ID<void>*>::const_iterator end();
	// // //

	// Выводить количество ID, в ID системе
	static int size();

	// Ищет ID, в ID системе
	// Если получаемое значение равно nullptr, значит ID не был найден
	template<class T>
	static ID_System::ID<T>* findID(const int id);

	// Ищет сущность по ID, в ID системе
	// Если получаемое значение равно nullptr, значит ID не был найден
	template<class T> 
	static T* find_by_ID(const int id);

	// Ищет все сущности, в ID системе
	// Если получаемое значение равно nullptr, значит ID не был найден
	template<class T>
	static std::vector<std::pair<int, T*>> find_all_entitys();
private:
	// Карта ID
	static std::map<int, ID<void>*> ID_map;
};

#include "ID-System/Template implementation/T_ID.hpp"

#include "ID-System/Template implementation/T_ID_System.hpp"
