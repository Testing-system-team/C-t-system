#include "test.h"
#include <iomanip>
test::test() : name("-"), numOfQuestions(5), result(0), mark(0), percentage(0)
{
	for (int i = 0; i < numOfQuestions; i++)
	{
		questions.push_back(question());
	}
}
test::test(std::string name, int numOfQuestions) : name(name), numOfQuestions(numOfQuestions), result(0), mark(0), percentage(0)
{
	for (int i = 0; i < numOfQuestions; i++)
	{
		questions.push_back(question());
	}
}

void test::addQuestion(const question& q)
{
	questions.push_back(q);
	
}

void test::display()
{

	std::cout << u8"\n Тест: " << name << " (" << questions.size() << u8" питань)\n";
}
void test::startTest()
{
	if (questions.size() == 0)
	{
		std::cout << u8"\n Тест не був завантажений\n";

	}
	else
	{
		std::string answer;
		char ans;
		for (auto iter = questions.begin(); iter != questions.end(); iter++)
		{
			int k = 0;
			iter->display();
			do 
			{
				if (k == 0)
				{
					std::cout << u8"Ваша відповідь(a/b/c): "; std::cin >> ans;
				}
				else
				{
					std::cout << u8"Оберіть існуючий варіант(a/b/c): "; std::cin >> ans;
				}
				system("pause");
				switch (ans)
				{
				case 'a':
				case 'A':
					answer = iter->A;
					k = 0;
					break;
				case 'b':
				case 'B':
					answer = iter->B;
					k = 0;
					break;
				case 'c':
				case 'C':
					answer = iter->C;
					k = 0;
					
					break;
				default: std::cout << u8" Зазначений вами варіант відповіді відсутній\n";
					k++;
					break;
					 
				}
			} while (k != 0);
			if (answer == iter->RightAnswer)
			{
				result++;
			}

		}
	}
}

void test::displayResult()
{
	std::cout << u8"\nВи відповіли правильно на " << result << u8" питань з " << questions.size() << "\n";
	std::cout << std::fixed;
	percentage = (float)(result * 100) / questions.size();
	std::cout << u8"\nВідсоток правильних відповідей - " << std::setprecision(1) 
		<< percentage << "%\n";
	;
	if (percentage <= 100 and percentage >= 95)
	{
		mark = 12;
	}
	else if (percentage >= 85 and percentage <= 94)
	{
		mark = 11;
	}
	else if (percentage >= 80 and percentage <= 84)
	{
		mark = 10;
	}
	else if (percentage >= 70 and percentage <= 79)
	{
		mark = 9;
	}
	else if (percentage >= 65 and percentage <= 69)
	{
		mark = 8;
	}
	else if (percentage >= 60 and percentage <= 64)
	{
		mark = 7;
	}
	else if (percentage >= 50 and percentage <= 59)
	{
		mark = 6;
	}
	else if (percentage >= 47 and percentage <= 49)
	{
		mark = 5;
	}
	else if (percentage >= 40 and percentage <= 46)
	{
		mark = 4;
	}
	else if (percentage >= 20 and percentage <= 39)
	{
		mark = 3;
	}
	else if (percentage >= 3 and percentage <= 19)
	{
		mark = 2;
	}
	else if (percentage == 0)
	{
		mark = 1;
	}
	std::cout << u8"Оцінка - " << mark << "\n";

}

void test::loadTest()
{
}

void test::saveTest()
{
}

void test::saveResult()
{
}
