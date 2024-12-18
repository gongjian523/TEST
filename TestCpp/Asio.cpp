//#include "Asio.h"
//#include <boost/asio.hpp>
//#include <iostream>
//
//
//void TcpClientSend()
//{
//    boost::asio::io_service ios;
//    boost::asio::io_context ioc;
//    boost::asio::ip::tcp::socket socket(ioc);
//
//    boost::system::error_code error;
//
//    socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234), error);
//    if (error.value() == 0)
//        std::cout << "Connect Succeed: " << error.message() << std::endl;
//    else
//        std::cout << "Connect failed: " << error.message() << std::endl;
//
//    //getchar();
//    //
//    //// request/message from client
//    const std::string msg = "Hello from Client!\n";
//    int len;
//    len = boost::asio::write(socket, boost::asio::buffer(msg), error);
//    if (error.value() == 0)
//        std::cout << "Write Succeed: " << error.message() << " Len£º" << len << std::endl;
//    else
//        std::cout << "Write failed: " << error.message() << " Len£º" << len << std::endl;
//
//    getchar();
//
//
//    len = boost::asio::write(socket, boost::asio::buffer(msg), error);
//    if (error.value() == 0)
//        std::cout << "Write Succeed: " << error.message() << " Len£º" << len << std::endl;
//    else
//        std::cout << "Write failed: " << error.message() << " Len£º" << len << std::endl;
//
//    //socket.send(boost::asio::buffer(msg), boost::asio::socket_base::message_flags(0), error);
//    //if(error.value() == 0)
//    //    std::cout << "Send Succeed: " << error.message() << std::endl;
//    //else
//    //    std::cout << "Send failed: " << error.message() << std::endl;
//
//    getchar();
//
//    // request/message from client
//    len = boost::asio::write(socket, boost::asio::buffer(msg), error);
//    if (error.value() == 0)
//        std::cout << "Write Succeed: " << error.message() << " Len£º" << len << std::endl;
//    else
//        std::cout << "Write failed: " << error.message() << " Len£º" << len << std::endl;
//
//
//    //// getting response from server
//    //boost::asio::streambuf receive_buffer;
//    //boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
//    //if (error && error != boost::asio::error::eof) {
//    //    std::cout << "receive failed: " << error.message() << std::endl;
//    //}
//    //else {
//    //    const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
//    //    std::cout << data << std::endl;
//    //}
//}
//
//
//void TestAsio()
//{
//    TcpClientSend();
//}