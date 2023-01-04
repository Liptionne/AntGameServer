#pragma once

#include <array>
#include <memory>

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>


class game;
class server;
class Maze;


/**
 * A TCP session opened on the server.
 */
class session : public std::enable_shared_from_this<session> {

    using endpoint_t = boost::asio::ip::tcp::endpoint;
    using socket_t = boost::asio::ip::tcp::socket;

public:
    session(boost::asio::io_context& service, server* _server);

    /**
     * Start reading from the socket.
     */
    void listen();
    
    /**
     * Callback for socket writes.
     */
    void handle_write(const std::error_code& ec);
    /**
     * Callback for socket reads.
     */
    void handle_read(const boost::system::error_code& ec,
        size_t bytes_transferred);

    /**
     * Send functions
     * 
     */


    void sendMaze(boost::uuids::uuid _uuid, Maze* _maze);

    void sendPheromons(boost::uuids::uuid _uuid,const std::vector<float>& _pheromons);

    void sendString(std::string _message);
    
    
    
    /**
     * Getters and setters
     */
    socket_t& socket() { return p_socket; }

    server* getServer() { return p_origin; }   

    

    //void setGame(game* _game) { p_game = _game; }

    //game* p_game;

private:
    /**
     * Session socket
     */
    socket_t p_socket;

    /*
    * Pointer to the server invoking the sesion    
    */

    server* p_origin;
    
    /**
     * Buffer to be used for r/w operations.
     */

    boost::asio::streambuf buffer{ 2048 };
    

};