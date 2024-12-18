// TestYaml.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "yaml-cpp/yaml.h"

typedef struct boxes_ {
    int x;
    int y;
    int w;
    int h;
} BOXES;

typedef struct automatic_shutter_analyse_ {
    int alg_code;
    bool has_shutter;
    int isarc;
    int isnutlost;
    int staticcontactpiecefracture;
    int staticcontactpiecelost;
    int isscrewloose;
    int iscotterpinlost;
    int switchbroken;
    double ring_piece_gap[6];
    double ring_piece_depth[3];
    BOXES arc_box[12];
    BOXES nut_lost[12];
    BOXES static_contact_piece_fracture[12];
    BOXES static_contact_piece_lost[12];
    BOXES screw_loose[6];
    BOXES cotter_pin_lost[3];
    BOXES switch_broken[1];
} SHUTTER_ANALYSE;

int main()
{
    YAML::Node result;
    // 当文件不存在或yaml格式出错时，抛异常
    //try {
    //    result = YAML::LoadFile("E:\\项目资料\\道岔\\PHM结果.yaml");
    //}
    //catch (...) {
    //    printf("error loading file, yaml file error or not exist.\n");
    //    return 0;
    //}

    //try {


    //    std::cout << "current_rating:" << result["current_rating1"].as<float>() << std::endl;
    //    std::cout << "overal_rating:" << result["overal_rating1"].as<float>() << std::endl;
    //    std::cout << "hitch_description:" << result["hitch_description1"].as<std::string>() << std::endl;

    //    std::cout << "sizeof related_hazards:" << (int)result["related_hazards1"].size() << std::endl;

    //    std::cout << "related_hazards:\n" << result["related_hazards1"] << std::endl; // 此处返回 Node
    //    
    //    for (int i = 0; i < (int)result["related_hazards1"].size(); i++)
    //    {
    //        std::cout << "related_hazards2: " << result["related_hazards1"][i].as<std::string>() << std::endl;
    //    }

    //    for (auto item : result["related_hazards1"])
    //    {
    //        std::cout << "related_hazards3: " << item.as<std::string>() << std::endl;
    //    }
    //}
    //catch (std::exception &ex) {
    //    std::cout << ex.what() << std::endl;
    //}


    try {
        result = YAML::LoadFile("D:\\Worksapce\\Switch\\Bin\\SwTiedaServ\\Release\\转辙机数据\\20231029\\00-07-32-86-76-76天回镇采样机1号\\过车记录\\050106\\智能分析结果_over.yaml");
    }
    catch (...) {
        printf("error loading file, yaml file error or not exist.\n");
        return 0;
    }

    try {

        std::string algtype;

        algtype = "自动开闭器拉弧左";
		//if (result[algtype]["arc"]) {
		//	float arcl = result[algtype]["arc"].as<float>();
		//	std::cout << arcl << std::endl;
		//}
		std::vector<int> arcl = result[algtype]["arc"].as<std::vector<int>>();

        algtype = "自动开闭器拉弧右";
        //float arcr = result[algtype]["arc"].as<float>();
        //std::cout << arcr << std::endl;
		std::vector<int> arcr = result[algtype]["arc"].as<std::vector<int>>();

        algtype = "道岔缺口左";
        float distancegl = result[algtype]["distance"].as<float>();
        std::cout << distancegl << std::endl;

        algtype = "道岔缺口右";
        float distanceg2 = result[algtype]["distance"].as<float>();
        std::cout << distanceg2 << std::endl;

        algtype = "尖轨开程左";
        float distance3 = result[algtype]["distance"].as<float>();
        std::cout << distance3 << std::endl;

        algtype = "尖轨开程右";
        float distance4 = result[algtype]["distance"].as<float>();
        std::cout << distance4 << std::endl;

        algtype = "尖轨爬行左";
        float distance5 = result[algtype]["distance"].as<float>();
        std::cout << distance5 << std::endl;

        algtype = "尖轨爬行右";
        float distance6 = result[algtype]["distance"].as<float>();
        std::cout << distance6 << std::endl;

		algtype = "自动开闭器左";
        SHUTTER_ANALYSE s1, s2;
		memset(&s1, 0x00, sizeof(SHUTTER_ANALYSE));
		memset(&s2, 0x00, sizeof(SHUTTER_ANALYSE));

		bool bhasshutter = result[algtype]["has_shutter"].as<bool>();
		if (!bhasshutter) {
			s1.has_shutter = false;
		}
		else {
			s1.has_shutter = true;

			if (result[algtype]["isnutlost"]) {
				s1.isnutlost = result[algtype]["isnutlost"].as<int>();

				if (s1.isnutlost > 12) {
					s1.isnutlost = 12;
				}
				for (int count = 0; count < s1.isnutlost; count++) {
					std::vector<int> pos = result[algtype]["nut_lost"][count].as<std::vector<int>>();

					if (pos.size() == 4) {
						s1.nut_lost[count].x = pos.at(0);
						s1.nut_lost[count].y = pos.at(1);
						s1.nut_lost[count].w = pos.at(2);
						s1.nut_lost[count].h = pos.at(3);
					}
					else {
						s1.nut_lost[count].x = 0;
						s1.nut_lost[count].y = 0;
						s1.nut_lost[count].w = 0;
						s1.nut_lost[count].h = 0;
					}

				}
			}
			else {
				s1.isnutlost = 0;
			}

			if (result[algtype]["staticcontactpiecefracture"]) {
				s1.staticcontactpiecefracture = result[algtype]["staticcontactpiecefracture"].as<int>();

				if (s1.staticcontactpiecefracture > 12) {
					s1.staticcontactpiecefracture = 12;
				}
				for (int count = 0; count < s1.staticcontactpiecefracture; count++) {
					std::vector<int> pos = result[algtype]["static_contact_piece_fracture"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s1.static_contact_piece_fracture[count].x = pos.at(0);
						s1.static_contact_piece_fracture[count].y = pos.at(1);
						s1.static_contact_piece_fracture[count].w = pos.at(2);
						s1.static_contact_piece_fracture[count].h = pos.at(3);
					}
					else {
						s1.static_contact_piece_fracture[count].x = 0;
						s1.static_contact_piece_fracture[count].y = 0;
						s1.static_contact_piece_fracture[count].w = 0;
						s1.static_contact_piece_fracture[count].h = 0;
					}
				}
			}
			else {
				s1.staticcontactpiecefracture = 0;
			}

			if (result[algtype]["staticcontactpiecelost"]) {
				s1.staticcontactpiecelost = result[algtype]["staticcontactpiecelost"].as<int>();

				if (s1.staticcontactpiecelost > 12) {
					s1.staticcontactpiecelost = 12;
				}
				for (int count = 0; count < s1.staticcontactpiecelost; count++) {
					std::vector<int> pos = result[algtype]["static_contact_piece_lost"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s1.static_contact_piece_lost[count].x = pos.at(0);
						s1.static_contact_piece_lost[count].y = pos.at(1);
						s1.static_contact_piece_lost[count].w = pos.at(2);
						s1.static_contact_piece_lost[count].h = pos.at(3);
					}
					else {
						s1.static_contact_piece_lost[count].x = 0;
						s1.static_contact_piece_lost[count].y = 0;
						s1.static_contact_piece_lost[count].w = 0;
						s1.static_contact_piece_lost[count].h = 0;
					}
				}
			}
			else {
				s1.staticcontactpiecelost = 0;
			}

			if (result[algtype]["ring_piece_gap"]) {
				int ringpiecegapcount = result[algtype]["ring_piece_gap"].size() > 6 ? 6 : result[algtype]["ring_piece_gap"].size();
				for (int count = 0; count < ringpiecegapcount; count++) {
					s1.ring_piece_gap[count] = result[algtype]["ring_piece_gap"][count].as<double>();
				}
			}

			if (result[algtype]["ring_piece_depth"]) {
				int ringpiecedepthcount = result[algtype]["ring_piece_depth"].size() > 3 ? 3 : result[algtype]["ring_piece_depth"].size();
				for (int count = 0; count < ringpiecedepthcount; count++) {
					s1.ring_piece_depth[count] = result[algtype]["ring_piece_depth"][count].as<double>();
				}
			}

			if (result[algtype]["isscrewloose"]) {
				s1.isscrewloose = result[algtype]["isscrewloose"].as<int>();

				if (s1.isscrewloose > 6) {
					s1.isscrewloose = 6;
				}
				for (int count = 0; count < s1.isscrewloose; count++) {
					std::vector<int> pos = result[algtype]["isscrewloose"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s1.screw_loose[count].x = pos.at(0);
						s1.screw_loose[count].y = pos.at(1);
						s1.screw_loose[count].w = pos.at(2);
						s1.screw_loose[count].h = pos.at(3);
					}
					else {
						s1.screw_loose[count].x = 0;
						s1.screw_loose[count].y = 0;
						s1.screw_loose[count].w = 0;
						s1.screw_loose[count].h = 0;
					}
				}
			}
			else {
				s1.isscrewloose = 0;
			}

			if (result[algtype]["iscotterpinlost"]) {
				s1.iscotterpinlost = result[algtype]["iscotterpinlost"].as<int>();

				if (s1.iscotterpinlost > 3) {
					s1.iscotterpinlost = 3;
				}
				for (int count = 0; count < s1.iscotterpinlost; count++) {
					std::vector<int> pos = result[algtype]["iscotterpinlost"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s1.cotter_pin_lost[count].x = pos.at(0);
						s1.cotter_pin_lost[count].y = pos.at(1);
						s1.cotter_pin_lost[count].w = pos.at(2);
						s1.cotter_pin_lost[count].h = pos.at(3);
					}
					else {
						s1.cotter_pin_lost[count].x = 0;
						s1.cotter_pin_lost[count].y = 0;
						s1.cotter_pin_lost[count].w = 0;
						s1.cotter_pin_lost[count].h = 0;
					}
				}
			}
			else {
				s1.iscotterpinlost = 0;
			}

			if (result[algtype]["switchbroken"]) {
				s1.switchbroken = result[algtype]["switchbroken"].as<int>();

				if (s1.switchbroken > 1) {
					s1.switchbroken = 1;
				}
				for (int count = 0; count < s1.switchbroken; count++) {
					std::vector<int> pos = result[algtype]["switchbroken"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s1.switch_broken[count].x = pos.at(0);
						s1.switch_broken[count].y = pos.at(1);
						s1.switch_broken[count].w = pos.at(2);
						s1.switch_broken[count].h = pos.at(3);
					}
					else {
						s1.switch_broken[count].x = 0;
						s1.switch_broken[count].y = 0;
						s1.switch_broken[count].w = 0;
						s1.switch_broken[count].h = 0;
					}
				}
			}
			else {
				s1.switchbroken = 0;
			}
		}

		algtype = "自动开闭器右";
		bhasshutter = result[algtype]["has_shutter"].as<bool>();
		if (!bhasshutter) {
			s2.has_shutter = false;
		}
		else {
			s2.has_shutter = true;

			if (result[algtype]["isnutlost"]) {
				s2.isnutlost = result[algtype]["isnutlost"].as<int>();

				if (s2.isnutlost > 12) {
					s2.isnutlost = 12;
				}
				for (int count = 0; count < s2.isnutlost; count++) {
					std::vector<int> pos = result[algtype]["nut_lost"][count].as<std::vector<int>>();

					if (pos.size() == 4) {
						s2.nut_lost[count].x = pos.at(0);
						s2.nut_lost[count].y = pos.at(1);
						s2.nut_lost[count].w = pos.at(2);
						s2.nut_lost[count].h = pos.at(3);
					}
					else {
						s2.nut_lost[count].x = 0;
						s2.nut_lost[count].y = 0;
						s2.nut_lost[count].w = 0;
						s2.nut_lost[count].h = 0;
					}
				}
			}
			else {
				s2.isnutlost = 0;
			}

			if (result[algtype]["staticcontactpiecefracture"]) {
				s2.staticcontactpiecefracture = result[algtype]["staticcontactpiecefracture"].as<int>();

				if (s2.staticcontactpiecefracture > 12) {
					s2.staticcontactpiecefracture = 12;
				}
				for (int count = 0; count < s2.staticcontactpiecefracture; count++) {
					std::vector<int> pos = result[algtype]["static_contact_piece_fracture"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s2.static_contact_piece_fracture[count].x = pos.at(0);
						s2.static_contact_piece_fracture[count].y = pos.at(1);
						s2.static_contact_piece_fracture[count].w = pos.at(2);
						s2.static_contact_piece_fracture[count].h = pos.at(3);
					}
					else {
						s2.static_contact_piece_fracture[count].x = 0;
						s2.static_contact_piece_fracture[count].y = 0;
						s2.static_contact_piece_fracture[count].w = 0;
						s2.static_contact_piece_fracture[count].h = 0;
					}
				}
			}
			else {
				s2.staticcontactpiecefracture = 0;
			}

			if (result[algtype]["staticcontactpiecelost"]) {
				s2.staticcontactpiecelost = result[algtype]["staticcontactpiecelost"].as<int>();

				if (s2.staticcontactpiecelost > 12) {
					s2.staticcontactpiecelost = 12;
				}
				for (int count = 0; count < s2.staticcontactpiecelost; count++) {
					std::vector<int> pos = result[algtype]["static_contact_piece_lost"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s2.static_contact_piece_lost[count].x = pos.at(0);
						s2.static_contact_piece_lost[count].y = pos.at(1);
						s2.static_contact_piece_lost[count].w = pos.at(2);
						s2.static_contact_piece_lost[count].h = pos.at(3);
					}
					else {
						s2.static_contact_piece_lost[count].x = 0;
						s2.static_contact_piece_lost[count].y = 0;
						s2.static_contact_piece_lost[count].w = 0;
						s2.static_contact_piece_lost[count].h = 0;
					}
				}
			}
			else {
				s2.staticcontactpiecelost = 0;
			}

			if (result[algtype]["ring_piece_gap"]) {
				int ringpiecegapcount = result[algtype]["ring_piece_gap"].size() > 6 ? 6 : result[algtype]["ring_piece_gap"].size();
				for (int count = 0; count < ringpiecegapcount; count++) {
					s2.ring_piece_gap[count] = result[algtype]["ring_piece_gap"][count].as<double>();
				}
			}

			if (result[algtype]["ring_piece_depth"]) {
				int ringpiecedepthcount = result[algtype]["ring_piece_depth"].size() > 3 ? 3 : result[algtype]["ring_piece_depth"].size();
				for (int count = 0; count < ringpiecedepthcount; count++) {
					s2.ring_piece_depth[count] = result[algtype]["ring_piece_depth"][count].as<double>();
				}
			}

			if (result[algtype]["isscrewloose"]) {
				s2.isscrewloose = result[algtype]["isscrewloose"].as<int>();

				if (s2.isscrewloose > 6) {
					s2.isscrewloose = 6;
				}
				for (int count = 0; count < s2.isscrewloose; count++) {
					std::vector<int> pos = result[algtype]["isscrewloose"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s2.screw_loose[count].x = pos.at(0);
						s2.screw_loose[count].y = pos.at(1);
						s2.screw_loose[count].w = pos.at(2);
						s2.screw_loose[count].h = pos.at(3);
					}
					else {
						s2.screw_loose[count].x = 0;
						s2.screw_loose[count].y = 0;
						s2.screw_loose[count].w = 0;
						s2.screw_loose[count].h = 0;
					}
				}
			}
			else {
				s2.isscrewloose = 0;
			}

			if (result[algtype]["iscotterpinlost"]) {
				s2.iscotterpinlost = result[algtype]["iscotterpinlost"].as<int>();

				if (s2.iscotterpinlost > 3) {
					s2.iscotterpinlost = 3;
				}
				for (int count = 0; count < s2.iscotterpinlost; count++) {
					std::vector<int> pos = result[algtype]["iscotterpinlost"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s2.cotter_pin_lost[count].x = pos.at(0);
						s2.cotter_pin_lost[count].y = pos.at(1);
						s2.cotter_pin_lost[count].w = pos.at(2);
						s2.cotter_pin_lost[count].h = pos.at(3);
					}
					else {
						s2.cotter_pin_lost[count].x = 0;
						s2.cotter_pin_lost[count].y = 0;
						s2.cotter_pin_lost[count].w = 0;
						s2.cotter_pin_lost[count].h = 0;
					}
				}
			}
			else {
				s2.iscotterpinlost = 0;
			}

			if (result[algtype]["switchbroken"]) {
				s2.switchbroken = result[algtype]["switchbroken"].as<int>();

				if (s2.switchbroken > 1) {
					s2.switchbroken = 1;
				}
				for (int count = 0; count < s2.switchbroken; count++) {
					std::vector<int> pos = result[algtype]["switchbroken"][count].as<std::vector<int>>();
					if (pos.size() == 4) {
						s2.switch_broken[count].x = pos.at(0);
						s2.switch_broken[count].y = pos.at(1);
						s2.switch_broken[count].w = pos.at(2);
						s2.switch_broken[count].h = pos.at(3);
					}
					else {
						s2.switch_broken[count].x = 0;
						s2.switch_broken[count].y = 0;
						s2.switch_broken[count].w = 0;
						s2.switch_broken[count].h = 0;
					}
				}
			}
			else {
				s2.switchbroken = 0;
			}
		}


    }
    catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

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
