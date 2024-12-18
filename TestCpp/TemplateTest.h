#pragma once

#include <iostream>

void TemplateTest();

template<typename T> void output(const T& t) { std::cout << t << std::endl; };


template<class T1, class T2>  //���ﲻ���зֺ�
class Point {
public:
	Point(T1 x, T2 y) : m_x(x), m_y(y) { }
public:
	T1 getX() const;  //��ȡx����
	void setX(T1 x);  //����x����
	T2 getY() const;  //��ȡy����
	void setY(T2 y);  //����y����
private:
	T1 m_x;  //x����
	T2 m_y;  //y����
};

