#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "shared_ptr.h"

#include "unique_ptr.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include "AVL.h"
#include "rbt.h"

std::map<int, std::string> map;

void fill(AVL &a, int n = 1000000, int mod = 1e9 + 7)
{
	map.clear();
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		int ran = rand() * rand() % mod;
		a[ran] = std::to_string(ran);
		map[ran] = std::to_string(ran);
	}
}

void fill(RBT<int, std::string> &a, int n = 1000000, int mod = 1e5 + 7)
{
	map.clear();
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		int ran = rand() * rand() % mod;
		a[ran] = std::to_string(ran);
		map[ran] = std::to_string(ran);
	}
}

void testAVl(int tests_count = 1000000)
{
	AVL avl; fill(avl, 100, 100);

	for (int i = 0; i < tests_count; i++)
	{
		int id = rand() % 3;
		int ran = rand() * rand() % 100;


		if (id == 0) // insert
		{
			avl[ran] = std::to_string(ran);
			map[ran] = std::to_string(ran);
		}

		if (id == 1) // delete
		{
			map.erase(ran);
			avl.remove(ran);
		}

		if (id == 2) // find
		{
			if (map.count(ran) != avl.contains(ran))
			{
				std::cout << "Mismatch ( " << ran << ") : map(" << map.count(ran) << ") avl(" << avl.contains(ran) << ") \n";
				return;
			}
		}

		//std::cout << "Test : " << i << ". Action : " << id << "\n";

	}
	std::cout << "AVL tests complited\n";
}

void testRBT(int tests_count = 1000000)
{
	
	RBT<int, std::string> rbt; fill(rbt, 100, 100);
	
	std::cout << "Testing started\n";

	for (int i = 0; i < tests_count; i++)
	{
		int id = rand() % 5;
		int ran = rand() * rand() % 100;

		//std::cout << "Test : " << i << ". Action : " << id << " VAL : " << ran << "\n";

		if (id == 0) // insert
		{
			rbt[ran] = std::to_string(ran);
			map[ran] = std::to_string(ran);
		}

		if (id == 1) // delete
		{
			if (map.count(ran))
			{
				map.erase(ran);
				rbt.remove(ran);
				//std::cout << "Test : " << i << ". Action : " << id << "\n";
			}
		}

		if (id == 2) // find
		{
			if (map.count(ran) != rbt.contains(ran))
			{
				std::cout << "Mismatch ( " << ran << ") : map(" << map.count(ran) << ") rbt(" << rbt.contains(ran) << ") \n";
				return;
			}
		}

		if (id == 3) // iter
		{
			for (auto j = rbt.begin(); j != rbt.end(); ++j) {}
				//std::cout << *j;

			//printf("\n");
		}

		if (id == 4) // list iter
		{
			for (auto j = rbt.begin_l(); j != rbt.end_l(); ++j) {}
				//std::cout << *j;

			//printf("\n");
		}

		
	}
	std::cout << "RBT tests complited\n";
}

RBT<std::string, std::string> dict;
std::map<int, int> mp;


void print_dict()
{
	for (auto i = dict.begin(); i != dict.end(); ++i) {}
		//printf_s("%s ", (*i).c_str());

	//printf("\n");
}

void print_dict_l()
{
	for (auto i = dict.begin_l(); i != dict.end_l(); ++i) {}
		//printf_s("%s ", (*i).c_str());

	//printf("\n");
}

int main()
{
	AVL avl;

	fill(avl, 50, 20);

	avl.directPrint(); std::cout << "\n";
	avl.reversePrint(); std::cout << "\n";
	avl.keySortedPrint(); std::cout << "\n";

	// complited final
	testAVl(); 
	testRBT();
	return 0;
}

