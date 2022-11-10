#pragma once

template<class T>
class smart_ptr
{
	T* m_ptr;

public:
	smart_ptr(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}

	// ƒеструктор позаботитс€ об удалении указател€
	~smart_ptr()
	{
		delete m_ptr;
	}

	//  онструктор перемещени€, который передает право собственности на x.m_ptr в m_ptr
	smart_ptr(smart_ptr&& x)
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr; // мы поговорим об этом чуть позже
	}

	smart_ptr(const smart_ptr& x) = delete;

	// ќператор присваивани€, который реализовывает семантику перемещени€
	smart_ptr& operator=(smart_ptr& a) = delete;


	// ќператор присваивани€ перемещением, который передает право собственности на x.m_ptr в m_ptr
	smart_ptr& operator=(smart_ptr&& x)
	{
		// ѕроверка на самоприсваивание
		if (&x == this)
			return *this;

		// ”дал€ем всЄ, что к этому моменту может хранить указатель 
		delete m_ptr;

		// ѕередаем право собственности на x.m_ptr в m_ptr
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr; // мы поговорим об этом чуть позже

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

