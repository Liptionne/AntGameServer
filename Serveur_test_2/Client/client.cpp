#include "client.h"

Client::Client(std::string _adress, short _port) {
    p_socket = std::make_shared<tcp::socket>(p_io_context);
    p_socket->connect(tcp::endpoint(boost::asio::ip::address::from_string(_adress), _port));
    p_uuid = NULL_UUID;
}

void Client::join(std::shared_ptr<tcp::socket> socket_) {
   
    boost::system::error_code error;

    std::string message_to_send = JSON::createJoin(p_uuid, 1);
   //std::cout << "on envoi ca :" << message_to_send << std::endl;

    boost::asio::write(*socket_, boost::asio::buffer(message_to_send), error);

    if (!error) {
        std::cout << "Send successfull" << std::endl;
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }

}

void Client::move(std::shared_ptr<tcp::socket> socket_, std::string _move)
{
    boost::system::error_code error;

    std::string message_to_send = JSON::createMove(p_uuid, _move);
    //std::cout << "on envoi ca :" << message_to_send << std::endl;

    boost::asio::write(*socket_, boost::asio::buffer(message_to_send), error);

    if (!error) {
        std::cout << "Send successfull" << std::endl;
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }
}
