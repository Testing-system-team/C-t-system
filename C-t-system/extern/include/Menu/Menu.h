#pragma once

namespace tMenu
{
	#ifdef UNICODE
		typedef std::wstring tstring;
		extern std::wostream& tcout;
		extern std::wistream& tcin;
	#else
		typedef std::string tstring;
		extern std::ostream& tcout;
		extern std::istream& tcin;
	#endif
}

using namespace tMenu;

class Menu
{
protected:
	//��� ��������� �� �������
	typedef std::function<void()> function_type;
private:
	//
	// ���������
	//
	tstring key;
	tstring back_key;

	std::vector<Menu> menu_list;

	function_type dyn_function;

	//��������� �����������
	Menu();

	//������� �� ������ ����
	void _clean(Menu& iter);
protected:
	// ���������, ������� ��� ������� ����
	bool exit;
public:
	//
	// ������������
	//
	Menu(const tstring name);
	Menu(const tstring name, const function_type &dyn_function);
	Menu(const tstring name, const std::vector<Menu> menu_list);

	//
	// ������ begin � end
	//
	std::vector<Menu>::const_iterator begin() const;
	std::vector<Menu>::const_iterator end() const;

	//
	// ���������� ����������
	//
	virtual Menu& operator=(const function_type &dyn_function);
	virtual Menu& operator=(const std::vector<Menu> menu_list);

	virtual Menu& operator+=(const Menu menu);

	virtual Menu& operator<<(const Menu menu);

	virtual Menu& operator[](const int index);
	virtual Menu& operator[](const TCHAR* name);
	virtual Menu& operator[](tstring name);

	virtual Menu operator--();

	//
	// ��������������
	//
	operator bool() const;
	operator const std::vector<Menu>() const;

	//
	// ������� ������
	//
	bool is_function() const;
	bool is_menu_list() const;

	bool contains(const tstring name) const;

	virtual Menu& push_back(const Menu menu);
	virtual Menu pop_back();

	int size() const;

	virtual void display() const;

	virtual void open(const tstring tchoice = _TEXT("Write your choice: "));

	void close();

	//
	// �������/c������
	//
	tstring getName() const;
	void setName(const tstring name);

	tstring get_exit_name() const;
	void rename_exit(const tstring name);

	tstring get_back_name() const;
	void rename_back(const tstring back);

	//
	// ���������� property
	//
	__declspec(property(get = getName, put = setName)) tstring name;
	__declspec(property(get = get_exit_name, put = rename_exit)) tstring exit_name;
	__declspec(property(get = get_back_name, put = rename_back)) tstring back_name;
};