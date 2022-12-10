#include "session.h"
#include "../JSON.h"

#include <functional>
#include <iostream>
#include <thread>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "server.h"
#include "Game.h"

using boost::asio::async_write;
using boost::asio::buffer;
using boost::asio::io_service;
using boost::asio::error::connection_reset;
using boost::asio::error::eof;
using boost::system::error_code;
using boost::system::system_error;

using std::placeholders::_1;
using std::placeholders::_2;

session::session(io_service& service, server* _server) : socket_{ service }, _origin{ _server }, game{NULL} {}

void session::listen() {
    auto handler = std::bind(&session::handle_read, shared_from_this(), _1, _2);
    socket_.async_read_some(buffer(buffer_), handler);
}

void session::handle_read(const error_code& ec, size_t bytes_transferred) {
    if (ec) {
        if (ec == eof || ec == connection_reset) {
            return;
        }

        throw system_error{ ec };
    }
    
    std::string string(buffer_, buffer_ + bytes_transferred);
    std::cout << string << std::endl;
    
    boost::property_tree::ptree root;
    std::stringstream ss;
    ss << string;
    boost::property_tree::read_json(ss, root);

    //travaille avec le propertry tree
    
    std::string type = JSON::getType(root);
    if (type == "join"){
        std::cout << "join" << std::endl;
        boost::uuids::uuid lol = boost::lexical_cast<boost::uuids::uuid>(JSON::getUUID(root));
        std::cout << lol << std::endl;
        int difficulty = JSON::getDifficultyJoin(root);
        std::cout << "difficulty" << difficulty << std::endl;
        _origin->matchmaking(difficulty, lol,shared_from_this());
    }
    else if(type == "move") {

    }
    listen();
}



