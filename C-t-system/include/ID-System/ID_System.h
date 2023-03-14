#pragma once

class ID_System
{
public:
	// ����� ID, ��� ����� ����������� ���������, ������� ������� ������� � ID �������
	template<class T>
	class ID
	{
		//
		// ��������� ID
		//

		int _id;
		std::string _typeName;
		// // //
	public:
		//
		// ������������
		//

		ID();

		// ��� 0 ��������, ID �� ������ � �������
		ID(const int id);

		ID(const ID&) = delete;
		ID(ID&& id);
		// // //

		// ����������
		virtual ~ID();

		//
		// ��������� ����������
		//

		void operator=(const ID&) = delete;
		ID& operator=(ID&& id);
		// // //

		//
		// �������
		//

		int getID() const;
		std::string getTypeName() const;
		// // //

		//
		// ���������� property
		//

		__declspec(property(get = getID)) int id;
		__declspec(property(get = getTypeName)) std::string typeName;
		// // //
	};

	//
	// ������ begin � end
	//

	static std::map<int, ID<void>*>::const_iterator begin();
	static std::map<int, ID<void>*>::const_iterator end();
	// // //

	// �������� ���������� ID, � ID �������
	static int size();

	// ���� ID, � ID �������
	// ���� ���������� �������� ����� nullptr, ������ ID �� ��� ������
	template<class T>
	static ID_System::ID<T>* findID(const int id);

	// ���� �������� �� ID, � ID �������
	// ���� ���������� �������� ����� nullptr, ������ ID �� ��� ������
	template<class T> 
	static T* find_by_ID(const int id);

	// ���� ��� ��������, � ID �������
	// ���� ���������� �������� ����� nullptr, ������ ID �� ��� ������
	template<class T>
	static std::vector<std::pair<int, T*>> find_all_entitys();
private:
	// ����� ID
	static std::map<int, ID<void>*> ID_map;
};

#include "ID-System/Template implementation/T_ID.hpp"

#include "ID-System/Template implementation/T_ID_System.hpp"
