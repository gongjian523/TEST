#include "general.h"
#include <string>
#include <iostream>

int SplitByteArray(char buf[], int  bytes_transferred, int len, char header)
{
	int printfIndex = 0;
	int findStatus = 0;

	for (printfIndex = 0; printfIndex < bytes_transferred; printfIndex++)
	{
		if (0 == findStatus)
		{
			if ((printfIndex + len - 1 ) < bytes_transferred)
			{
				if ((header == (buf[printfIndex])))
				{
					findStatus = 1;	//找到帧头
				}
			}
			else
			{
				return printfIndex;
			}
		}
		else if (1 == findStatus)
		{
			std::string szOut = "";

			for (int i = 0; i < len; i++)
			{
				szOut += std::to_string((int ) buf[printfIndex - 1 + i]) + " ";
			}

			std::cout << szOut << std::endl;

			printfIndex += (len - 2); //偏移到帧尾
			findStatus = 0; //处理数据
		}
	}

	return bytes_transferred;
}

void DataParase()
{
	int ret = 0;

	char buf[6] = { 0xF1,0x1,0x1,0xF1,0x2,0x2};
	
	ret = SplitByteArray(buf, 6, 3, 0xF1);
	
	std::cout << ret  << std::endl;

	char buf1[5] = { 0xF1,0x1,0x1,0xF1,0x2};

	ret = SplitByteArray(buf1, 5, 3, 0xF1);

	std::cout << ret << std::endl;

	char buf2[3] = { 0xF1,0x1,0x1};

	ret = SplitByteArray(buf2, 3, 3, 0xF1);

	std::cout << ret << std::endl;

	char buf3[5] = { 0xF2,0x1,0x1,0x1,0x1 };

	ret = SplitByteArray(buf3, 5, 3, 0xF1);

	std::cout << ret << std::endl;
	 
}


void CheckSum()
{
	 unsigned char sum1 = 0xFE + 0x68 + 0x81;

	if (sum1 == 0xE7)
		std::cout << "CheckSum Right" << std::endl;
	else
		std::cout << "CheckSum wring" << std::endl;
}


void GeneralTest()
{
	//DataParase();

	CheckSum();
}
