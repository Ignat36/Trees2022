#pragma once

template<class T>
class weak_ptr;

template<class T>
class shared_ptr
{
	T* m_ptr;
	int* m_references_count;

private:
	void m_delete()
	{
		(*m_references_count)--;
		if (!(*m_references_count))
		{
			delete m_ptr;
			delete m_references_count;
		}
	}

public:
	shared_ptr(T* ptr = nullptr)
		:m_ptr(ptr), m_references_count(new int(1))
	{
	}

	// ���������� ����������� �� �������� ���������
	~shared_ptr()
	{
		m_delete();
	}

	// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	shared_ptr(shared_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		(* m_references_count)++;
	}
	
	shared_ptr(weak_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		(* m_references_count)++;
	}

	// �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	shared_ptr& operator=(shared_ptr& x)
	{
		// �������� �� ����������������
		if (&x == this)
			return *this;

		m_delete();

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count;
		(*m_references_count)++; // ����������� ���������� ������

		return *this;
	}

	shared_ptr& operator=(weak_ptr& x)
	{
		// �������� �� ����������������
		if (&x == this)
			return *this;

		m_delete();

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count;
		(*m_references_count)++; // ����������� ���������� ������

		return *this;
	}

	shared_ptr(shared_ptr&& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
		x.m_ptr = nullptr; 
		x.m_references_count = nullptr;
	}

	// �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	shared_ptr& operator=(shared_ptr&& x)
	{
		// �������� �� ����������������
		if (&x == this)
			return *this;

		// ������� ��, ��� � ����� ������� ����� ������� ��������� 
		m_delete();

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count;
		x.m_ptr = nullptr; // �� ��������� �� ���� ���� �����
		x.m_references_count = nullptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};

template<class T>
class weak_ptr
{
	T* m_ptr;
	int* m_references_count;

public:
	// ���������� ����������� �� �������� ���������
	~weak_ptr()
	{
	}

	// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	weak_ptr(weak_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
	}

	weak_ptr(shared_ptr& x)
		: m_ptr(x.m_ptr), m_references_count(x.m_references_count)
	{
	}

	// �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	weak_ptr& operator=(weak_ptr& x)
	{
		// �������� �� ����������������
		if (&x == this)
			return *this;

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count

		return *this;
	}

	weak_ptr& operator=(shared_ptr& x)
	{
		// �������� �� ����������������
		if (&x == this)
			return *this;

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		m_references_count = x.m_references_count

		return *this;
	}

	shared_ptr lock()
	{
		return shared_ptr(*this)
	}
};
