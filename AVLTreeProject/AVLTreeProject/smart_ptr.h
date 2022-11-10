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

	// ���������� ����������� �� �������� ���������
	~smart_ptr()
	{
		delete m_ptr;
	}

	// ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	smart_ptr(smart_ptr&& x)
		: m_ptr(x.m_ptr)
	{
		x.m_ptr = nullptr; // �� ��������� �� ���� ���� �����
	}

	smart_ptr(const smart_ptr& x) = delete;

	// �������� ������������, ������� ������������� ��������� �����������
	smart_ptr& operator=(smart_ptr& a) = delete;


	// �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
	smart_ptr& operator=(smart_ptr&& x)
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

