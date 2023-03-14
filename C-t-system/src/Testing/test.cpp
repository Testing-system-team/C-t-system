#include "Header.h"
#include "Testing/test.h"

using namespace Testing;

test::test() : name("-"),result(0), mark(0), percentage(0)
{

}
test::test(std::string name) : name(name),  result(0), mark(0), percentage(0)
{

}

Testing::test::operator Menu()
{
	int count = MultiByteToWideChar(CP_UTF8, 0, name.c_str(), name.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, name.c_str(), name.length(), &wstr[0], count);

	Menu menu(wstr);
	menu.exit_name = L"�����";
	menu.back_name = L"�����";

	menu[L"��������"] = std::bind(&test::display, this);
	menu[L"������ ����"] = std::bind(&test::startTest, this);

	return menu;
}

void test::addQuestion(const question& q)
{
	questions.push_back(q);
	
}

void test::display()
{

	std::cout << u8"\n ����: " << name << " (" << questions.size() << u8" ������)\n";
	system("pause");
}
void test::startTest()
{
	if (questions.size() == 0)
	{
		std::cout << u8"\n ���� �� ��� ������������\n";
		system("pause");
	}
	else
	{
		display();
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
	system("pause");
}



int test::getResult()
{
	return result;
}

int test::getMark()
{
	return mark;
}

std::string Testing::test::getname()
{
	return name;
}

void Testing::test::setName(const std::string name)
{
	this->name = name;
}

Testing::test::operator pt::ptree()
{
	pt::ptree testtags;
	testtags.put("name", name);
	for (question& q : questions)
	{
		testtags.add_child("questions.question", q);
	}
	return testtags;
}
double test::getPercentage()
{
	return percentage;
}

std::vector<question>& test::getQuestions()
{
	return questions;
}





