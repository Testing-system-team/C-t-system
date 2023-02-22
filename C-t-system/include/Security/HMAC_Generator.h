#pragma once

namespace Security
{
	class HMAC_Generator
	{
		//
		// Аттрибуты
		//

		std::basic_string<unsigned char> salt;
		int iterations;
		int keyLen;
		// // //

		// Преобразование символов из десятичного формата в шестнадцатеричный
		std::string dec_to_hex(const std::basic_string<unsigned char> dec) const;
		// Преобразование символов из шестнадцатеричного формата в десятичный
		std::basic_string<unsigned char> hex_to_dec(const std::string hex) const;
	public:
		//
		// Конструкторы
		//

		HMAC_Generator(std::basic_string<unsigned char> salt);
		HMAC_Generator(std::basic_string<unsigned char> salt, int iterations, int keyLen);
		// // //

		// Генерация хэша
		std::string generate_HMAC(std::string pass);

		// Сравнение хэша с паролем
		bool compare_HMAC(std::string pass, std::string hash);
	};
}
