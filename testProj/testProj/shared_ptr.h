#pragma once

#include <iostream>

template<class T>
class weak_ptr;

template<class T>
class shared_ptr
{
	T* m_ptr;
	int* m_references_count;

	friend class weak_ptr<T>;

private:
	void m_delete()
	{
		if (!m_references_count || --(*m_references_count) == 0)
		{

			//if (m_ptr)
			//	std::cout << "Deleted ptr\n";

			delete m_ptr;
			delete m_references_count;
		}
	}

public:

	operator bool() const
	{
		return m_ptr != nullptr;
	}

	shared_ptr(T* ptr = nullptr)
		:m_ptr(ptr), m_references_count(new int(1))
	{
	}

	// Деструктор позаботится об удалении указателя
	~shared_ptr()
	{
		m_delete();
	}

	// Конструктор перемещения, который передает право собственности на x.m_ptr в m_ptr
	shared_ptr(shared_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		(* m_references_count)++;
	}

	// Конструктор перемещения, который передает право собственности на x.m_ptr в m_ptr
	shared_ptr(const shared_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		(* m_references_count)++;
	}
	
	shared_ptr(weak_ptr<T>& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		(* m_references_count)++;
	}

	// Оператор присваивания перемещением, который передает право собственности на x.m_ptr в m_ptr
	shared_ptr& operator=(shared_ptr& x)
	{
		// Проверка на самоприсваивание
		if (&x == this)
			return *this;

		m_delete();

		// Передаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count;
		(*m_references_count)++; // увеличиваем количество ссылок

		return *this;
	}

	shared_ptr& operator=(weak_ptr<T>& x)
	{
		m_delete();

		// Передаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count;
		(*m_references_count)++; // увеличиваем количество ссылок

		return *this;
	}

	shared_ptr(shared_ptr&& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		x.m_ptr = nullptr; 
		x.m_references_count = nullptr;
	}

	// Оператор присваивания перемещением, который передает право собственности на x.m_ptr в m_ptr
	shared_ptr& operator=(shared_ptr&& x)
	{
		// Проверка на самоприсваивание
		if (&x == this)
			return *this;

		// Удаляем всё, что к этому моменту может хранить указатель 
		m_delete();

		// Передаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count;
		x.m_ptr = nullptr; // мы поговорим об этом чуть позже
		x.m_references_count = nullptr;

		return *this;
	}

	bool equals(shared_ptr ptr) {
		return m_ptr == ptr.m_ptr;
	}

	bool equals(shared_ptr const ptr) const {
		return m_ptr == ptr.m_ptr;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};