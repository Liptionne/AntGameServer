#pragma once

#include "client.h"
#include <functional>
#include <iostream>
#include <thread>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>


using boost::asio::async_write;
using boost::asio::buffer;
using boost::asio::io_context;
using boost::asio::error::connection_reset;
using boost::asio::error::eof;
using boost::system::error_code;
using boost::system::system_error;

using std::placeholders::_1;
using std::placeholders::_2;

bool VERBOSE = false;

Client::Client(boost::asio::io_context& io_context1, std::string _adress, short _port) : p_io_context{ io_context1 }, p_socket_client{ io_context1 } {
    
    p_socket_client.connect(tcp::endpoint(boost::asio::ip::address::from_string(_adress), _port));
    p_uuid = NULL_UUID;
    listenClient();
    t1 = std::thread([&]
        {
            p_io_context.run();
        });
    
    
}

Client::~Client() {
    p_io_context.stop();
    
    t1.join();
    
}

void Client::join(int _difficulty) {
   
    boost::system::error_code error;

    std::string message_to_join = JSON::createJoin(p_uuid, _difficulty) + "#";
    if (VERBOSE) {
        std::cout << "on envoi ca :" << message_to_join << "\n";
    }
    boost::asio::write(p_socket_client, boost::asio::buffer(message_to_join), error);
    if (!error) {
        std::cout << "JOIN SENT" << std::endl;
        
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }

    

}


void Client::move(std::string _move)
{
    boost::system::error_code error;

    std::string message_move = JSON::createMove(p_uuid, _move) + "#";
    if (VERBOSE) {
        std::cout << "on envoi ca :" << message_move << "\n";
    }
        boost::asio::write(p_socket_client, boost::asio::buffer(message_move), error);
    if (!error) {
        std::cout << "MOVE SENT" << "\n";
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }
    
}

void Client::listenClient()
{
    
    auto handler_listen = std::bind(&Client::handleReadClient, this, _1, _2);
    boost::asio::async_read_until(p_socket_client, p_buffer, '#', handler_listen);
}

void Client::handleReadClient(const boost::system::error_code& ec,
    size_t bytes_transferred) {
    
    if (ec) {
        if (ec == eof || ec == connection_reset) {
            return;
        }

        throw system_error{ ec };
    }

    boost::asio::streambuf::const_buffers_type bufs = p_buffer.data();
    p_buffer.consume(bytes_transferred);
    std::string temp_str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);
    std::string received_message = temp_str.substr(0, bytes_transferred - 1);
    
    if (VERBOSE) {
        std::cout << "client RECOIT " << received_message << "\n";
    }
    
   
    boost::property_tree::ptree JSON_Property_Tree;
    std::stringstream ss;
    ss << received_message;
    boost::property_tree::read_json(ss, JSON_Property_Tree);
    std::string type = JSON::getType(JSON_Property_Tree);

    if (type == "okMaze") {
        p_uuid = boost::lexical_cast<boost::uuids::uuid>(JSON::getUUID(JSON_Property_Tree));

        setMaze(JSON::getMaze(JSON_Property_Tree));
        
    }
    if (type == "info") {
        p_pheromons = JSON::getPheromons(JSON_Property_Tree);
    }
    listenClient();

}
