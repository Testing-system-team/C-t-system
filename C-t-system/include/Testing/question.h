#pragma once

namespace Testing
{
	class question
	{
		std::string data;
		std::string a, b, c; // варіанти відповіді
		std::string rightAnswer;
	public:

		question();
		question(std::string data, std::string a, std::string b, std::string c, std::string rightAnswer);

		std::string getrightAnswer();

		std::string getA();

		std::string getB();
		std::string getData();
		std::string getC();
		void setData(const std::string data);
		void setA(const std::string a);
		void setB(const std::string b);
		void setC(const std::string c);
		void setrightAnswer(std::string rightAnswer);
		void display();
		operator pt::ptree();
		__declspec(property(get = getA, put = setA)) std::string A;
		__declspec(property(get = getB, put = setB)) std::string B;
		__declspec(property(get = getC, put = setC)) std::string C;
		__declspec(property(get = getData, put = setData)) std::string Data;
		__declspec(property(get = getrightAnswer, put = setrightAnswer)) std::string RightAnswer;
	};
}
