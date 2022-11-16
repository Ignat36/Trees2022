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

	// ���������� ����������� �� �������� ���������
	~unique_ptr()
	{
		delete m_ptr;
	}

	// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	unique_ptr(unique_ptr&& x)
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr; // �� ��������� �� ���� ���� �����
	}

	unique_ptr(const unique_ptr& x) = delete;

	// �������� ������������, ������� ������������� ��������� �����������
	unique_ptr& operator=(unique_ptr& a) = delete;


	// �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	unique_ptr& operator=(unique_ptr&& x)
	{
		// �������� �� ����������������
		if (&x == this)
			return *this;

		// ������� ��, ��� � ����� ������� ����� ������� ��������� 
		delete m_ptr;

		// �������� ����� ������������� �� x.m_ptr � m_ptr
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr; // �� ��������� �� ���� ���� �����

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};

// ����������� ����������� �� ������ � �������

