#include "Header.h"
#include "Security/HMAC_Generator.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	HMAC_Generator test((const unsigned char*)"test.salt");
	std::cout << u8"Хэш от test: " << test.generate_HMAC("test") << '\n'
		<< u8"Хэш от test1: " << test.generate_HMAC("test1") << '\n'
		<< u8"Сравнение test и хэша от test: " << test.compare_HMAC("test", test.generate_HMAC("test")) << '\n'
		<< u8"Сравнение test1 и хэша от test: " << test.compare_HMAC("test1", test.generate_HMAC("test")) << "\n\n"; 
	system("pause");
}