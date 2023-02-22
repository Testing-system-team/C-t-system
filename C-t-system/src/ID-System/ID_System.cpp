#include "Header.h"
#include "ID-System/ID_System.h"

std::map<int, ID_System::ID<void>*> ID_System::ID_map;

std::map<int, ID_System::ID<void>*>::const_iterator ID_System::begin()
{
	return ID_map.begin();
}

std::map<int, ID_System::ID<void>*>::const_iterator ID_System::end()
{
	return ID_map.end();
}

int ID_System::size()
{
	return ID_map.size();
}
