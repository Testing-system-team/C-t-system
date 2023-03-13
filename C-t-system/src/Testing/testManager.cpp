#include "Header.h"
#include "Testing/testManager.h"
using namespace Testing;
Testing::testManager::testManager(): fileName("Tests.xml")
{
}
Testing::testManager::testManager(std::string fileName): fileName(fileName)
{
}
void Testing::testManager::display()
{
	if (categories.size() == 0)
	{
		std::cout << u8" Категорії не були додані\n";
	}
	else
	{
		for (category& c : categories)
		{
			c.display();
		}
	}


}

void Testing::testManager::loadData()
{
	pt::ptree tree;
	pt::read_xml(fileName, tree, pt::xml_parser::trim_whitespace);
	try
	{
		for (auto& c : tree.get_child("Categories"))
		{
			categories.push_back(category(c.second.get<std::string>("name")));
			for (auto& t : c.second.get_child("Tests"))
			{
				categories[categories.size() - 1].addtest(test(t.second.get<std::string>("name")));

				for (auto& q : t.second.get_child("questions"))
				{

					std::string data = q.second.get<std::string>("data");
					std::string a = q.second.get<std::string>("a");
					std::string b = q.second.get<std::string>("b");
					std::string c = q.second.get<std::string>("c");
					std::string rightanswer = q.second.get<std::string>("rightAnswer");
					categories[categories.size() - 1].
						getTests()[categories[categories.size() - 1].getTests().size() - 1].
						addQuestion(question(data, a, b, c, rightanswer));
				}
			}
		}
	}
	catch (pt::ptree_bad_path& ex)
	{
		std::cerr << "pt::ptree_bad_path: " << ex.what() << '\n';
		system("pause");
	}
}

void Testing::testManager::saveData()
{
	pt::ptree tree;
	int k = 0;

	for (category& c : categories)
	{
		tree.add_child("Categories.Category", c);
		
		/*
		for (test& t : categories[k].getTests())
		{
			tree.add_child("Categories.Category.Tests.test", t);
			/*
			* or (question& q : categories[k].getTests()[k1].getQuestions())
			{
				tree.add_child("Categories.Category.Tests.test.questions.question",q);
				
		     }
			k1++;
			
		}
		k++;
		*/
	}
	pt::write_xml(fileName, tree);
}

void Testing::testManager::addcategory(const Testing::category& c)
{
	categories.push_back(c);
}

std::vector<category>& Testing::testManager::getcategories()
{
	return categories;
}
