#pragma once

template<class T>
class shared_ptr;

template<class T>
class weak_ptr
{
	T* m_ptr;
	int* m_references_count;

public:
	// ƒеструктор позаботитс€ об удалении указател€
	~weak_ptr()
	{
	}

	//  онструктор перемещени€, который передает право собственности на x.m_ptr в m_ptr
	weak_ptr(weak_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
	}

	weak_ptr(shared_ptr<T>& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
	}

	// ќператор присваивани€ перемещением, который передает право собственности на x.m_ptr в m_ptr
	weak_ptr& operator=(weak_ptr& x)
	{
		// ѕроверка на самоприсваивание
		if (&x == this)
			return *this;

		// ѕередаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count

			return *this;
	}

	weak_ptr& operator=(shared_ptr<T>& x)
	{
		// ѕроверка на самоприсваивание
		if (&x == this)
			return *this;

		// ѕередаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count

			return *this;
	}

	shared_ptr<T> lock()
	{
		return shared_ptr<T>(*this)
	}
};
