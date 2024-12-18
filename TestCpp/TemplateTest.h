#pragma once

#include <iostream>

void TemplateTest();

template<typename T> void output(const T& t) { std::cout << t << std::endl; };


template<class T1, class T2>  //这里不能有分号
class Point {
public:
	Point(T1 x, T2 y) : m_x(x), m_y(y) { }
public:
	T1 getX() const;  //获取x坐标
	void setX(T1 x);  //设置x坐标
	T2 getY() const;  //获取y坐标
	void setY(T2 y);  //设置y坐标
private:
	T1 m_x;  //x坐标
	T2 m_y;  //y坐标
};

