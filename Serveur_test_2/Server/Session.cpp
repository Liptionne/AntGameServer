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
using boost::asio::io_context;
using boost::asio::error::connection_reset;
using boost::asio::error::eof;
using boost::system::error_code;
using boost::system::system_error;

using std::placeholders::_1;
using std::placeholders::_2;

session::session(io_context& service, server* _server) : p_socket{ service }, p_origin{ _server } {}

void session::listen() {
    
    auto handler = std::bind(&session::handle_read, shared_from_this(), _1, _2);
    //p_socket.async_read_some(buffer(buffer_), handler);
    boost::asio::async_read_until(p_socket, buffer12, '#', handler);
}

void session::handle_read(const error_code& ec, size_t bytes_transferred) {
    if (ec) {
        if (ec == eof || ec == connection_reset) {
            return;
        }

        throw system_error{ ec };
    }
    
    boost::asio::streambuf::const_buffers_type bufs = buffer12.data();
    buffer12.consume(1024);
    std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);
    std::string string = str.substr(0, bytes_transferred - 1);
    std::cout <<"hellooooooo\n" << string << std::endl;
    
    //std::string string(buffer_, buffer_ + bytes_transferred-1);
    //std::cout << string << std::endl;
    
    boost::property_tree::ptree root;
    std::stringstream ss;
    ss << string;
    boost::property_tree::read_json(ss, root);

    //travaille avec le propertry tree
    
    std::string type = JSON::getType(root);
    if (type == "join"){
        std::cout << "JOIN" << std::endl;
        boost::uuids::uuid UUID = boost::lexical_cast<boost::uuids::uuid>(JSON::getUUID(root));
        //std::cout << UUID << std::endl;
        int difficulty = JSON::getDifficultyJoin(root);
        //std::cout << "difficulty" << difficulty << std::endl;
        p_origin->matchmaking(difficulty, UUID,shared_from_this());
    }
    else if(type == "move") {
        
        std::cout << "MOVE" << std::endl;

        boost::uuids::uuid UUID = boost::lexical_cast<boost::uuids::uuid>(JSON::getUUID(root));
        std::string MOVE = JSON::getMove(root);
        std::cout << MOVE << std::endl;
        p_origin->getGame(UUID).move(UUID, MOVE);


        
    }
    listen();
}



