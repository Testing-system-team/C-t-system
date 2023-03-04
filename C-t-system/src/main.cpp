#include "Header.h"

#ifdef _DEBUG
#include "Auth-System/Authorization.h"
#include "Testing/category.h"
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	Testing::test t = Testing::test("test", 11);

	t.addQuestion(Testing::question(u8"2+2?", u8"2", u8"3", u8"4", u8"4"));
	t.display();
	t.startTest();
	
}
#else
int main()
{

}
#endif // 


