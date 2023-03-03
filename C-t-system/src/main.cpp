#include "Header.h"

#ifdef _DEBUG
#include "Auth-System/Authorization.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	auto managerPtr = std::make_unique<User_System::DataManager>();
	Auth_System::Authorization test(managerPtr.get());
	test.open();
}
#else
int main()
{

}
#endif // 


