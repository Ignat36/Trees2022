#include <iostream>

#include "unique_ptr.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include "AVL.h"
#include "rbt.h"

class Human
{
	std::string m_name;
	weak_ptr<Human> m_partner; // изначально пустой

public:

	Human(const std::string& name) : m_name(name)
	{
		std::cout << m_name << " created\n";
	}
	~Human()
	{
		std::cout << m_name << " destroyed\n";
	}

	friend bool partnerUp(shared_ptr<Human>& h1, shared_ptr<Human>& h2)
	{
		if (!h1 || !h2)
			return false;

		h1->m_partner = h2;
		h2->m_partner = h1;

		std::cout << h1->m_name << " is now partnered with " << h2->m_name << "\n";

		return true;
	}

	shared_ptr<Human> getPartner() { return m_partner.lock(); } // используем метод lock() для конвертации std::weak_ptr в std::shared_ptr
	const std::string& getName() const { return m_name; }
};

int main()
{
	auto anton = shared_ptr<Human>(new Human("Anton")); // создание умного указателя с объектом Anton класса Human
	auto ivan = shared_ptr<Human>(new Human("Ivan")); // создание умного указателя с объектом Ivan класса Human

	partnerUp(anton, ivan); // Anton указывает на Ivan-а, а Ivan указывает на Anton-а

	auto partner = ivan->getPartner(); // передаем partner-у содержимое умного указателя, которым владеет ivan
	std::cout << ivan->getName() << "'s partner is: " << partner->getName() << '\n';

	return 0;
}