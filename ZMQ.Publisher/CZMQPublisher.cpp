#include "CZMQPublisher.h"

#include "zmq.h"
#include "json.hpp"

#include <list>
#include <boost/range/iterator_range.hpp> 
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#pragma comment(lib, "libzmq-v120-mt-4_3_2.lib")


#include <iostream>

CZMQPublisher::~CZMQPublisher()
{
	Stop();
}

bool CZMQPublisher::Start(std::string ip_, std::string port_)
{
	if (bStart_) return true;
	bStart_ = true;
	IP_ = ip_ == "" ? IP_ : ip_;
	Port_ = port_ == "" ? Port_ : port_;
	conState = "正在连接";

	std::cout << "启动ZMQ发布器" << std::endl;;
	
	return Initial();
}

void CZMQPublisher::Stop()
{
	if (!bStart_) return;
	bStart_ = false;
	
	std::cout << "停止ZMQ发布器" << std::endl;;
	
	Uninitial();
}


bool CZMQPublisher::Initial()
{
	//连接ZMQ
	std::string connectStr = "tcp://*:" + Port_;

	if (context == NULL)
	{
		context = zmq_ctx_new();
		publisher = zmq_socket(context, ZMQ_PUB);

		int ret = zmq_bind(publisher, connectStr.c_str());

		if (ret == 0)
		{
			std::cout << "ZMQ发布成功" << std::endl;
			conState = "连接成功";

		}
		else
		{

			std::cout << "ZMQ发布失败" << std::endl;
			conState = "连接断开";
			return false;
		}
	}

	return true;
}

void CZMQPublisher::Uninitial()
{
	//断开ZMQ
	if ((publisher != NULL) && (context != NULL))
	{
		conState = "连接断开";
		zmq_close(publisher);
		zmq_ctx_destroy(context);
		publisher = NULL;
		context = NULL;
	}
}

bool CZMQPublisher::SendFrame(float f10104_, float f10028_, float f10029_, float f10119_, float f10122_)
{
	//boost::format f("{\n   \"10104\":  %d,\n    \"10028\":  %d,\n   \"10029\":  %d,\n   \"10119\":  %d,\n   \"10122\":  \"%s\"\n}\n");
	//f % f10104_ % f10028_ % f10029_% f10119_% f10122_;
	//return SendFrame(f.str());


	nlohmann::json obj;

	obj["10104"] = f10104_;
	obj["10028"] = f10028_;
	obj["10029"] = f10029_;
	obj["10119"] = f10119_;
	obj["10122"] = f10122_;

	return SendFrame(obj.dump());

}

bool CZMQPublisher::SendFrame(std::string frame_)
{
	if ((publisher != NULL) && (frame_ != ""))
	{
		zmq_send(publisher, Topic.c_str(), Topic.length(), ZMQ_SNDMORE);
		int ret = zmq_send(publisher, frame_.c_str(), frame_.length(), 0);

		std::cout << frame_.c_str() << std::endl;
		return ret > 0;
	}

	return false;
}