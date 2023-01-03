#include "session.h"
#include "../JSON.h"

#include <functional>
#include <iostream>
#include <thread>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_generators.hpp> // generators


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

session::session(io_context& service, server* _server) : p_socket{ service }, p_origin{ _server } {
    
}

void session::listen() {
    
    auto handler = std::bind(&session::handle_read, shared_from_this(), _1, _2);
    boost::asio::async_read_until(p_socket, buffer, '#', handler);
}

void session::handle_write(const std::error_code& ec)
{
    if (ec) {
        throw system_error{ ec };
    }
}

void session::handle_read(const error_code& ec, size_t bytes_transferred) {
    if (ec) {
        if (ec == eof || ec == connection_reset) {
            return;
        }

        throw system_error{ ec };
    }

    auto handler_write = std::bind(&session::handle_write, shared_from_this(), _1);
    
    boost::asio::streambuf::const_buffers_type bufs = buffer.data();
    buffer.consume(2048);
    std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);
    std::string string = str.substr(0, bytes_transferred - 1);
    
    std::cout << "serveur recoit : " << string << std::endl;
    std::cout << bytes_transferred << ";;" << string.length() << std::endl;
    
    
    boost::property_tree::ptree root;
    std::stringstream ss;
    ss << string;
    boost::property_tree::read_json(ss, root);

    //travaille avec le propertry tree
    
    std::string type = JSON::getType(root);
    
    if (type == "join"){
        
        std::cout << "JOIN" << std::endl;
        
        boost::uuids::uuid UUID = boost::lexical_cast<boost::uuids::uuid>(JSON::getUUID(root));
        
        
        if (UUID.is_nil()) {
            UUID = boost::uuids::random_generator()();
        }
        
        int difficulty = JSON::getDifficultyJoin(root);
        
        p_origin->matchmaking(difficulty, UUID,shared_from_this());
        
    }
    else if(type == "move") {
        
        std::cout << "MOVE" << std::endl;

        boost::uuids::uuid UUID = boost::lexical_cast<boost::uuids::uuid>(JSON::getUUID(root));
        std::string MOVE = JSON::getMove(root);
        
        p_origin->getGame(UUID).move(UUID, MOVE);
        
        
    }
    listen();
}

void session::sendMaze(boost::uuids::uuid _uuid,Maze* _maze)
{
    std::string JSONokMaze = JSON::createokMaze(_uuid, *_maze) + "#";
    std::cout << "serveur envoi " << JSONokMaze << std::endl;
    std::cout << "taille du paquet " << JSONokMaze.size() << std::endl;
    
    boost::system::error_code error;
    boost::asio::write(p_socket, boost::asio::buffer(JSONokMaze), error);

}

void session::sendPheromons(boost::uuids::uuid _uuid,const std::vector<float>& _pheromons)
{
    std::string JSONInfo = JSON::createInfo(_uuid, _pheromons);
    std::cout << "serveur envoi " << JSONInfo << std::endl;
    std::cout << "taille du paquet " << JSONInfo.size() << std::endl;

    boost::system::error_code error;
    boost::asio::write(p_socket, boost::asio::buffer(JSONInfo), error);
}



