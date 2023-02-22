#pragma once

namespace Security
{
	class HMAC_Generator
	{
		//
		// ���������
		//

		std::basic_string<unsigned char> salt;
		int iterations;
		int keyLen;
		// // //

		// �������������� �������� �� ����������� ������� � �����������������
		std::string dec_to_hex(const std::basic_string<unsigned char> dec) const;
		// �������������� �������� �� ������������������ ������� � ����������
		std::basic_string<unsigned char> hex_to_dec(const std::string hex) const;
	public:
		//
		// ������������
		//

		HMAC_Generator(std::basic_string<unsigned char> salt);
		HMAC_Generator(std::basic_string<unsigned char> salt, int iterations, int keyLen);
		// // //

		// ��������� ����
		std::string generate_HMAC(std::string pass);

		// ��������� ���� � �������
		bool compare_HMAC(std::string pass, std::string hash);
	};
}
