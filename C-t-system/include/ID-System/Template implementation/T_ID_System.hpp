#pragma once
#include "Header.h"

template<class T>
inline ID_System::ID<T>* ID_System::findID(const int id)
{
	if (auto result = ID_map.find(id); result != ID_map.end())
		if (result->second->typeName == typeid(T).name())
			return (ID_System::ID<T>*)result->second;

	return nullptr;
}

template<class T>
inline T* ID_System::find_by_ID(const int id)
{
	return (T*)findID<T>(id);
}

template<class T>
inline std::vector<std::pair<int, T*>> ID_System::find_all_entitys()
{
	std::vector<std::pair<int, T*>> temp;
	for (auto ID : ID_map)
		if (ID.second->typeName == typeid(T).name())
			temp.push_back(std::pair(ID.first, (T*)(ID_System::ID<T>*)ID.second));

	return temp;
}