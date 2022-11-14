#pragma once

template<class T>
class unique_ptr
{
	T* m_ptr;

public:
	unique_ptr(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}

	// ƒеструктор позаботитс€ об удалении указател€
	~unique_ptr()
	{
		delete m_ptr;
	}

	//  онструктор перемещени€, который передает право собственности на x.m_ptr в m_ptr
	unique_ptr(unique_ptr&& x)
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr; // мы поговорим об этом чуть позже
	}

	unique_ptr(const unique_ptr& x) = delete;

	// ќператор присваивани€, который реализовывает семантику перемещени€
	unique_ptr& operator=(unique_ptr& a) = delete;


	// ќператор присваивани€ перемещением, который передает право собственности на x.m_ptr в m_ptr
	unique_ptr& operator=(unique_ptr&& x)
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

// конструктор копироавни€ л€ шареда и слабого

