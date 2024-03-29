#pragma once
#include "Header.h"

template<class T>
ID_System::ID<T>::ID()
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
		throw std::runtime_error(u8"����� ID �� ����������� ��������� ������");
	}
}

template<class T>
ID_System::ID<T>::ID(const int id)
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
				u8"ID(" + std::to_string(id) + u8") ��� ���������\n"
				+ '\n'
				+ u8"ID ������������ � �������:\n"
				+ u8"��� ����: " + _typeName + '\n'
				+ u8"������ �� ������ � ������: " + in_adress.str() + '\n'
				+ '\n'
				+ u8"ID � �������:\n"
				+ u8"��� ����: " + _typeName + '\n'
				+ u8"������ �� ������ � ������: " + system_adress.str()
			).c_str());
		}
		else
		{
			_id = id;
			ID_map[id] = (ID_System::ID<void>*)this;
		}
	}

	// ���� ID ����������� ��� 0, �� �� �� ������ � ID �������
	else if (std::is_base_of_v<ID, T>) _id = 0;

	else
	{
		_id = 0;
		throw std::runtime_error(u8"����� ID �� ����������� ��������� ������");
	}
}

template<class T>
ID_System::ID<T>::ID(ID&& id)
{
	_typeName = typeid(T).name();
	_id = id._id;
	ID_map[id] = (ID_System::ID<void>*)this;

	id._id = 0;
}

template<class T>
ID_System::ID<T>::~ID()
{
	if (_id) ID_map.erase(_id);
}

template<class T>
ID_System::ID<T>& ID_System::ID<T>::operator=(ID&& id)
{
	_typeName = typeid(T).name();
	_id = id._id;
	ID_map[id] = (ID_System::ID<void>*)this;

	id._id = 0;
	return *this;
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
