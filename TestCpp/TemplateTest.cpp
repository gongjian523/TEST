#include "TemplateTest.h"
#include <iostream>


//不支持
void ExportTest()
{
	output("abc");
	output(1);
	output(1.5);
	output(true);
}

template<class T1, class T2>  //模板头
T1 Point<T1, T2>::getX() const /*函数头*/ {
	return m_x;
}
template<class T1, class T2>
void Point<T1, T2>::setX(T1 x) {
	m_x = x;
}
template<class T1, class T2>
T2 Point<T1, T2>::getY() const {
	return m_y;
}
template<class T1, class T2>
void Point<T1, T2>::setY(T2 y) {
	m_y = y;
}




void TemplateClassTest()
{
	Point<int,int> p1(10, 20);
	std::cout << "x=" << p1.getX() << ", y=" << p1.getY() << std::endl;
	Point<int, const char*> p2(10, "东经180度");
	std::cout << "x=" << p2.getX() << ", y=" << p2.getY() << std::endl;
	Point<const char*, const char*>* p3 = new Point<const char*, const char*>("东经180度", "北纬210度");
	std::cout << "x=" << p3->getX() << ", y=" << p3->getY() << std::endl;
	Point<double,double> p4(10.0, 20.0);
	std::cout << "x=" << p4.getX() << ", y=" << p4.getY() << std::endl;
}


void TemplateTest()
{
	ExportTest();

	TemplateClassTest();

	//typedef struct _GUID {
	//	unsigned long  Data1;
	//	unsigned short Data2;
	//	unsigned short Data3;
	//	unsigned char  Data4[8];
	//} GUID;

	//GUID GUID_C5 =
	//{ 0x39d54454, 0xf35e, 0x418d, { 0x8d, 0x4d, 0x2e, 0xa, 0xce, 0xe7, 0x40, 0x3 } };

	//std::string strGUID;
	//strGUID.assign((char*)&GUID_C5,sizeof(GUID));

}



