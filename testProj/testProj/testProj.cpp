#include <iostream>
#include <string>
#include <map>

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

void testAVl(int tests_count = 10000000)
{
	AVL avl; fill(avl, 10000000);

	for (int i = 0; i < tests_count; i++)
	{
		int id = rand() % 3;
		int ran = rand() * rand() % (int)(1e9 + 7);


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
	}
	std::cout << "AVL tests complited\n";
}

void testRBT(int tests_count = 100000000)
{
	
	RBT<int, std::string> rbt; fill(rbt, 10000000);
	
	std::cout << "Testing started\n";

	for (int i = 0; i < tests_count; i++)
	{
		int id = rand() % 3;
		int ran = rand() * rand() % (int)(1e5 + 7);

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
	}
	std::cout << "RBT tests complited\n";
}


int main()
{
	AVL avl;
	RBT<int, std::string> rbt;
	fill(avl, 50, 20); 

	avl.directPrint(); std::cout << "\n";
	avl.reversePrint(); std::cout << "\n";
	avl.keySortedPrint(); std::cout << "\n";
	
	// complited final
	//testAVl(); 
	
	testRBT();
	//rbt[2] = "2";
	//rbt[1] = "1";
	//rbt[4] = "4";
	//rbt[3] = "3";
	//

	//rbt.remove(1);
	//rbt.remove(3);
	//rbt.remove(5);
	//rbt.remove(4);
	//rbt.remove(2);

	return 0;
}