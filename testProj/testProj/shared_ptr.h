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

	// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
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

	shared_ptr& operator=(weak_ptr<T>& x)
	{
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

	bool equals(shared_ptr ptr) {
		return m_ptr == ptr.m_ptr;
	}

	bool equals(shared_ptr const ptr) const {
		return m_ptr == ptr.m_ptr;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};