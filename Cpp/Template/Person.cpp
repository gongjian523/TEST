#include "Person.h"

namespace TestUnit5
{
	//���캯�� ����ʵ��
	template<class T1, class T2>
	Person<T1, T2>::Person(T1 name, T2 age) {
		this->m_Name = name;
		this->m_Age = age;
	}

	//��Ա���� ����ʵ��
	template<class T1, class T2>
	void Person<T1, T2>::showPerson() {
		std::cout << "����: " << this->m_Name << " ����:" << this->m_Age << std::endl;
	}
}