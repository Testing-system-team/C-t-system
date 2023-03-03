#pragma once
#include "Header.h"

template<class T>
ID_System::ID<T>::ID() throw(std::runtime_error)
{
	_typeName = typeid(T).name();

	if (std::is_base_of_v<ID, T>)
	{
		int i = 1;
		for (auto pair : ID_map)
		{
			if (i != pair.first) break;
			else i++;
		}

		_id = i;
		ID_map[i] = (ID_System::ID<void>*)this;
	}
	else
	{
		_id = 0;
		throw std::runtime_error(u8" ласс ID не наследуетс€ шаблонным именем");
	}
}

template<class T>
ID_System::ID<T>::ID(const int id) throw(std::runtime_error)
{
	_typeName = typeid(T).name();

	if (std::is_base_of_v<ID, T> && id)
	{
		if (auto result = ID_map.find(id); result != ID_map.end())
		{
			std::stringstream in_adress;
			std::stringstream system_adress;
			in_adress << this;
			system_adress << result->second;
			_id = 0;

			throw std::runtime_error(std::string
			(
				u8"ID(" + std::to_string(id) + u8") уже сущестует\n"
				+ '\n'
				+ u8"ID обратившийс€ к системе:\n"
				+ u8"»м€ типа: " + _typeName + '\n'
				+ u8"—сылка на €чейку в пам€ти: " + in_adress.str() + '\n'
				+ '\n'
				+ u8"ID в системе:\n"
				+ u8"»м€ типа: " + _typeName + '\n'
				+ u8"—сылка на €чейку в пам€ти: " + system_adress.str()
			).c_str());
		}
		else
		{
			_id = id;
			ID_map[id] = (ID_System::ID<void>*)this;
		}
	}

	// ≈сли ID указываетс€ как 0, то он не входит в ID систему
	else if (std::is_base_of_v<ID, T>) _id = 0;

	else
	{
		_id = 0;
		throw std::runtime_error(u8" ласс ID не наследуетс€ шаблонным именем");
	}
}

template<class T>
ID_System::ID<T>::~ID()
{
	if (_id) ID_map.erase(_id);
}

template<class T>
int ID_System::ID<T>::getID() const
{
	return _id;
}

template<class T>
std::string ID_System::ID<T>::getTypeName() const
{
	return _typeName;
}
