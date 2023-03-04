#include "Header.h"
#include "Testing/test.h"

using namespace Testing;

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

	std::cout << u8"\n ����: " << name << " (" << questions.size() << u8" ������)\n";
}
void test::startTest()
{
	if (questions.size() == 0)
	{
		std::cout << u8"\n ���� �� ��� ������������\n";

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
					std::cout << u8"���� �������(a/b/c): "; std::cin >> ans;
				}
				else
				{
					std::cout << u8"������ �������� ������(a/b/c): "; std::cin >> ans;
				}
				
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
				default: std::cout << u8" ���������� ���� ������ ������ �������\n";
					k++;
					break;
					 
				}
			} while (k != 0);
			if (answer == iter->RightAnswer)
			{
				result++;
			}
		}
		displayResult();
	}
}

void test::displayResult()
{
	std::cout << u8"\n�� ������� ��������� �� " << result << u8" ������ � " << questions.size() << "\n";
	std::cout << std::fixed;
	percentage = (float)(result * 100) / questions.size();
	std::cout << u8"\n³������ ���������� �������� - " << std::setprecision(1) 
		<< percentage << "%\n";
	;
	mark = ((float)result / questions.size()) * 12;
	std::cout << u8"������ - " << mark << "\n";

}



int test::getResult()
{
	return result;
}

int test::getMark()
{
	return mark;
}

double test::getPercentage()
{
	return percentage;
}

std::vector<question>& test::getQuestions()
{
	return questions;
}





