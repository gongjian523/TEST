#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <functional>
#include <memory>
#include <tuple>
#include <atomic>

#include <boost/serialization/singleton.hpp>
#include <boost/asio/deadline_timer.hpp>


using namespace boost::serialization;


class CZMQPublisher : public singleton<CZMQPublisher>
{

public:
	CZMQPublisher() {};
	~CZMQPublisher();

	bool Start(std::string ip_ = "", std::string port_ = "");
	void Stop();

	void SetTopic(std::string topic_) { Topic = topic_; };
	bool SendFrame(std::string frame_);
	bool SendFrame(float f10104_, float f10028_, float f10029_, float f10119_, float f10122_);

	std::string GetConnectionStatusStr() { return conState; };

private:
	bool Initial();
	void Uninitial();

private:
	std::atomic<bool> bStart_ = false;
	std::string Topic = "SP1C0001";
	std::string IP_ = "192.168.1.99";
	std::string Port_ = "6000";
	std::string conState = "";

	void* context = NULL;
	void* publisher = NULL;
};
