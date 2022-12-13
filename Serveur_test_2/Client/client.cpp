#pragma once

#include "client.h"
#include <functional>
#include <iostream>
#include <thread>


using boost::asio::async_write;
using boost::asio::buffer;
using boost::asio::io_context;
using boost::asio::error::connection_reset;
using boost::asio::error::eof;
using boost::system::error_code;
using boost::system::system_error;

using std::placeholders::_1;
using std::placeholders::_2;


Client::Client(std::string _adress, short _port) {
    p_socket_client = std::make_shared<tcp::socket>(p_io_context);
    p_socket_client->connect(tcp::endpoint(boost::asio::ip::address::from_string(_adress), _port));
    p_uuid = NULL_UUID;
    listen_client();
}

void Client::join(std::shared_ptr<tcp::socket> socket_) {
   
    boost::system::error_code error;

    std::string message_to_send = JSON::createJoin(p_uuid, 1) + "#";
   

    //boost::asio::write(*socket_, boost::asio::buffer(message_to_send), error);
    auto handler = std::bind(&Client::handle_write_client, shared_from_this(), _1);
    p_socket_client->async_write_some(boost::asio::buffer(message_to_send, message_to_send.size()), handler);
    if (!error) {
        //std::cout << "Send successfull" << std::endl;
        listen_client();
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }

}
void Client::handle_write_client(const std::error_code& ec) {
    if (ec) {
        throw system_error{ ec };
    }
    listen_client();

}



void Client::move(std::shared_ptr<tcp::socket> socket_, std::string _move)
{
    boost::system::error_code error;

    std::string message_to_send = JSON::createMove(p_uuid, _move) + "#";
    //std::cout << "on envoi ca :" << message_to_send << std::endl;
    auto handler = std::bind(&Client::handle_write_client, shared_from_this(), _1);
    p_socket_client->async_write_some(boost::asio::buffer(message_to_send, message_to_send.size()), handler);

    if (!error) {
        //std::cout << "Send successfull" << std::endl;
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }
}

void Client::listen_client()
{
    std::cout << "debut ecoute client" << std::endl;
    auto handler_listen = std::bind(&Client::handle_read_client, this, _1, _2);
    boost::asio::async_read_until((*p_socket_client), p_buffer, '#', handler_listen);
}

void Client::handle_read_client(const boost::system::error_code& ec,
    size_t bytes_transferred) {
    std::cout << "recu du client" << std::endl;
    if (ec) {
        if (ec == eof || ec == connection_reset) {
            return;
        }

        throw system_error{ ec };
    }

    boost::asio::streambuf::const_buffers_type bufs =p_buffer.data();
    p_buffer.consume(1024);
    std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);
    std::string string123456 = str.substr(0, bytes_transferred - 1);
    std::cout << "client a reçu" << string123456 << std::endl;
}
