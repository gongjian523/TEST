// TestCPP2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>

void byteToFloat(unsigned char* charBuf, float* out) {

	unsigned char  i;
	void* pf = out;
	unsigned char* px = charBuf;

	for (i = 0; i < 4; i++) {
		*((unsigned char*)pf + i) = *(px + i);
	}
}


int main()
{
    std::cout << "Hello World!\n";

	//int a = sizeof(int);
	//int b = sizeof(long);
	//int c = sizeof(long long);	int d = sizeof(short);

	////std::cout << a << " " << b << " " << c << " " << d << "\n ";

	//std::map<int, std::string> map1;

	//map1.insert(std::make_pair(1, "aaas"));
	//map1.insert(std::make_pair(2, "bbbb"));

	//std::cout << "map1" << " " << map1.at(1).c_str() << " map2" << map1.at(2).c_str() << " " << "\n ";


	unsigned char arr[16] = { 0 };

	float f1 = 23.3, f2 = 9.3, f3 = 123.3, f4 = 5123.34;

	memcpy(&arr[0], &f1, sizeof(float));
	memcpy(&arr[4], &f2, sizeof(float));
	memcpy(&arr[8], &f3, sizeof(float));
	memcpy(&arr[12], &f4, sizeof(float));

	float f21,f22,f23,f24;

	memcpy(&f21, &arr[0], sizeof(float));
	memcpy(&f22, &arr[4], sizeof(float));
	memcpy(&f23, &arr[8], sizeof(float));
	memcpy(&f24, &arr[12], sizeof(float));

	std::cout << "f1 " << f21 << " f2 " << f22 << " f3 " << f23 << " f4 " << f2 <<  "\n ";

	for (int i = 0; i < 16 / 4; i++) {
		//float fForce;
		//memcpy(&fForce, &arr[i * 4], sizeof(float));
		//fForce = fForce * 640.56;
		float fForce = (*(float*)&arr[i * 4]) * 640.56;
		memcpy(&arr[i * 4], &fForce, sizeof(float));
	}

	float f31, f32, f33, f34;
	memcpy(&f31, &arr[0], sizeof(float));
	memcpy(&f32, &arr[4], sizeof(float));
	memcpy(&f33, &arr[8], sizeof(float));
	memcpy(&f34, &arr[12], sizeof(float));

	std::cout << "f1 " << f31 << " f2 " << f32 << " f3 " << f33 << " f4 " << f34 << "\n ";

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
