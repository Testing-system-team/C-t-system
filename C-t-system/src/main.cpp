#include "Header.h"

#ifdef _DEBUG
#include "Auth-System/Authorization.h"
#include "Testing/category.h"
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	test t = test("test", 11);

	t.addQuestion(question(u8"2+2?", u8"2", u8"3", u8"4", u8"4"));
	t.display();
	t.startTest();
	
}
#else
int main()
{

}
#endif // 


