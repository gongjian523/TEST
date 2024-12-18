// TestAsync.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <future>


int fun1(int a)
{
	auto f = std::async(std::launch::async, [a]() {
		std::cout << "Hello World start! [" << a << "]" << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Hello World2! [" << a << "]" << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Hello World3! [" << a << "]" << std::this_thread::get_id() << std::endl;

		return 2;

		});

	auto f2 = std::async(std::launch::async, [a]() {
		std::cout << "Hello World start2! [" << a << "]" << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Hello World22! [" << a << "]" << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Hello World23! [" << a << "]" << std::this_thread::get_id() << std::endl;

		return 2;

		});

	std::cout << "Hello World! [" << a << "]" << std::this_thread::get_id() << std::endl;
	return 1;

}


//class Share1
//{
//public:
//	Share1()
//	{
//		m_sh = std::shared_ptr<int>(new int[10], [](int* p) { 
//		
//		std::cout << "Share1 Release Mem " << *p  << " " << p[1] <<  " " << *(p+2) << std::endl;
//		
//		delete[] p;
//		});
//
//		int* pInt = m_sh.get();
//		for (int i = 0; i < 10; i++)
//		{
//			*pInt = i;
//			pInt++;
//		}
//		std::cout << "Share1 Mallc Mem" << std::endl;
//	}
//
//	~Share1() {
//		m_sh = nullptr;
//	};
//
//	void GetPointer(int* pTem) {
//		pTem = m_sh.get();
//	};
//
//	int use_count()
//	{
//		return m_sh.use_count();
//	}
//
//	void GetPointer(std::shared_ptr<int> sh) {
//
//		for (int i = 0; i < 10; i++)
//		{
//			std::cout << *(m_sh.get() + i) << std::endl;
//		}
//
//		m_sh = std::make_shared<int>(sh.get());
//
//	};
//
//protected:
//	int m_input;
//	std::shared_ptr<int> m_sh;
//};


//class Share2
//{
//public:
//	Share2()
//	{
//	}
//
//	~Share2() {
//		m_sh = nullptr;
//	};
//
//	void GetPointer(int* pTem) {
//		pTem = m_sh.get();
//	};
//
//	int use_count()
//	{
//		return m_sh.use_count();
//	}
//
//	void Update(int* p, int n)
//	{
//		m_sh = std::shared_ptr<int>(new int[10], [](int* p) {
//
//		std::cout << "Share2 Release Mem " << *p << " " << p[1] << " " << *(p + 2) << std::endl;
//		delete[] p;
//
//			});
//
//		memcpy(m_sh.get(), p, sizeof(int)*10);
//		std::cout << __FUNCTION__ <<std::endl;
//		for (int i = 0; i < 10; i++)
//		{
//			std::cout << " " << *(m_sh.get() + i);
//		}
//		std::cout << std::endl;
//	}
//
//	void GetPointer(int ** ppInt) {
//
//		*ppInt = m_sh.get();
//
//		std::cout << __FUNCTION__ << std::endl;
//		for (int i = 0; i < 10; i++)
//		{
//			std::cout << " " << *(*ppInt + i);
//		}
//		std::cout << std::endl;
//	};
//
//protected:
//	int m_input;
//	std::shared_ptr<int> m_sh;
//};



class Share3
{
public:
	Share3() {};
	~Share3() {
	};

	bool MallocMem(std::shared_ptr<int> & sh, int & len, int i)
	{
		len = 10;
		sh = std::shared_ptr<int>(new int[10], [](int* p) {
			std::cout << "Share3 Release Mem " << *p << " " << p[1] << " " << *(p + 2) << std::endl;
			delete[] p;
			});

		int data[10] = { i*10 ,i*10+1, i * 10 + 2, i * 10 + 3, i * 10 + 4, i * 10 + 5, i * 10 + 6, i * 10 + 7, i * 10 + 8, i * 10 + 9 };

		memcpy(sh.get(), data, sizeof(data));

		return true;
	}
};

int main()
{
	//signed int i;

	//for (i = 0; i < (5 - 10); )
	//{
	//	std::cout << "--------------i:" << i<< std::endl;
	//	i++;
	//}

	std::shared_ptr<int> sh;

#if 0
	Share1* pSHARE = new Share1();

	//int* pItem = nullptr;


	//pSHARE->GetPointer(pItem);

	//if (pItem != nullptr)
	//{
	//	for (int i = 0;  i < 10; i++)
	//	{
	//		std::cout << *(pItem+i) << std::endl;
	//	}
	//}
		
	std::shared_ptr<int> sh;
	pSHARE->GetPointer(sh);

	//if (sh != nullptr)
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		std::cout << *(sh.get() + i) << std::endl;
	//	}
	//}

	//int ret = fun1(1);

	//ret = fun1(2);

	//std::cout << "mian" << std::this_thread::get_id() <<  " "  << ret << std::endl;
	
	std::cout <<"[" << __LINE__ << "] " << "pSHARE->use_count():" << pSHARE->use_count() << std::endl;
	std::cout <<"[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count()  << std::endl;

	delete pSHARE;
	
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;	
	sh = nullptr;
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;

#endif

#if 0

	Share2* pSHARE2 = new Share2();


	int buffer[10] = { 0 ,1, 2, 3, 4, 5, 6, 7, 8, 9 };
	pSHARE2->Update(buffer, 10);
	std::cout << "[" << __LINE__ << "] " << "pSHARE2->use_count():" << pSHARE2->use_count() << std::endl;
	//std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;

	int* pp;

	pSHARE2->GetPointer(&pp);
	for (int i = 0; i < 10; i++)
	{
		std::cout << "[" << __LINE__ << "] " << *(pp + i) << std::endl;
	}

	std::cout << "[" << __LINE__ << "] " << "pSHARE2->use_count():" << pSHARE2->use_count() << std::endl;
	//std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;

	int buffer2[10] = { 10 ,11, 12, 13, 14, 15, 16, 17, 18, 19 };

	pSHARE2->Update(buffer2, 10);
	std::cout << "[" << __LINE__ << "] " << "pSHARE2->use_count():" << pSHARE2->use_count() << std::endl;
	//std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;

	pSHARE2->GetPointer(&pp);
	std::cout << "[" << __LINE__ << "] " << "pSHARE2->use_count():" << pSHARE2->use_count() << std::endl;
	//std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "[" << __LINE__ << "] " << *(pp + i) << std::endl;
	}
#endif

	int len;
	Share3* pSHARE3 = new Share3();
	pSHARE3->MallocMem(sh, len, 1);

	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "[" << __LINE__ << "] " << *(sh.get() + i) << std::endl;
	}
	
	pSHARE3->MallocMem(sh, len, 2);
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "[" << __LINE__ << "] " << *(sh.get() + i) << std::endl;
	}

	pSHARE3->MallocMem(sh, len, 3);
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "[" << __LINE__ << "] " << *(sh.get() + i) << std::endl;
	}

	std::shared_ptr<int> sh2;

	sh2 = sh;
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	std::cout << "[" << __LINE__ << "] " << "sh2.use_count():" << sh2.use_count() << std::endl;

	pSHARE3 = nullptr;
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;

	sh = nullptr;
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	std::cout << "[" << __LINE__ << "] " << "sh2.use_count():" << sh2.use_count() << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::cout << "[" << __LINE__ << "] " << *(sh2.get() + i) << std::endl;
	}

	sh2 = nullptr;
	std::cout << "[" << __LINE__ << "] " << "sh.use_count():" << sh.use_count() << std::endl;
	std::cout << "[" << __LINE__ << "] " << "sh2.use_count():" << sh2.use_count() << std::endl;

	getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
