#include <iostream>

#include "unique_ptr.h"
#include "shared_ptr.h"
#include "AVL.h"
#include "rbt.h"

class Item
{
public:
	Item() { std::cout << "Item acquired\n"; }
	~Item() { std::cout << "Item destroyed\n"; }
};

int main()
{
	// Выделяем объект класса Item и передаем право собственности на него std::unique_ptr
	unique_ptr<Item> item(new Item);

	return 0;
} // item выходит из области видимости здесь, соответственно, Item уничтожается также здесь
