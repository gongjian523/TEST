
#include <queue>
#include <iostream>

#include "QueueTest.h"


void QueueCopy()
{
	std::queue<int> q1, q2;
	std::queue<int>* p1, * p2;

	p1 = &q1;
	p2 = &q2;

	q1.push(1);
	q1.push(2);

	q2 = q1;

	std::cout << q1.size() << " " << q2.size() << " " << p1->size() << " " << p2->size() << std::endl;

	q1.push(3);

	std::cout << q1.size() << " " << q2.size() << " " << p1->size() << " " << p2->size() << std::endl;

}