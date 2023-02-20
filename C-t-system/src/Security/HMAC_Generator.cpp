#include "Header.h"
#include "Security/HMAC_Generator.h"

std::string HMAC_Generator::dec_to_hex(const std::basic_string<unsigned char> dec) const
{
	std::string hex;
	for (auto ch : dec)
	{
		char temp[3];
		sprintf_s(temp, 3, "%02x", 255 & ch);
		hex += temp;
	}
	return hex;
}

std::basic_string<unsigned char> HMAC_Generator::hex_to_dec(const std::string hex) const
{
	std::basic_string<unsigned char> dec;
	for (auto ch = hex.begin(); ch != hex.end(); ch++)
	{
		std::stringstream ss;
		unsigned int x;
		ss << std::hex << std::string{ *ch, *++ch };
		ss >> x;
		dec += x;
	}
	return dec;
}

HMAC_Generator::HMAC_Generator(std::basic_string<unsigned char> salt) : salt(salt), iterations(2048), keyLen(32) {}

HMAC_Generator::HMAC_Generator(std::basic_string<unsigned char> salt, int iterations, int keyLen)
	: salt(salt), iterations(iterations), keyLen(keyLen)
{}

std::string HMAC_Generator::generate_HMAC(std::string pass)
{
	auto digest = std::make_unique<unsigned char[]>(keyLen);
	PKCS5_PBKDF2_HMAC(pass.c_str(), pass.size(), salt.c_str(), salt.size(),
		iterations, EVP_sha256(), keyLen, digest.get());
	return dec_to_hex(std::basic_string<unsigned char>(digest.get(), keyLen));
}

bool HMAC_Generator::compare_HMAC(std::string pass, std::string hash)
{
	auto digest = std::make_unique<unsigned char[]>(keyLen);
	PKCS5_PBKDF2_HMAC(pass.c_str(), pass.size(), salt.c_str(), salt.size(),
		iterations, EVP_sha256(), keyLen, digest.get());
	return dec_to_hex(std::basic_string<unsigned char>(digest.get(), keyLen)) == hash;
}
