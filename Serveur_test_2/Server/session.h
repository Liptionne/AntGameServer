#pragma once

#include <array>
#include <memory>

#include <boost/asio.hpp>


class game;
class server;


/**
 * A TCP session opened on the server.
 */
class session : public std::enable_shared_from_this<session> {

    using endpoint_t = boost::asio::ip::tcp::endpoint;
    using socket_t = boost::asio::ip::tcp::socket;

public:
    session(boost::asio::io_service& service, server* _server);

    /**
     * Start reading from the socket.
     */
    void listen();
    

    /**
     * Callback for socket reads.
     */
    void handle_read(const boost::system::error_code& ec,
        size_t bytes_transferred);

    /**
     * Get a reference to the session socket.
     */
    socket_t& socket() { return p_socket; }

    server* getServer() { return p_origin; }    

private:
    /**
     * Session socket
     */
    socket_t p_socket;
    server* p_origin;
    /**
     * Buffer to be used for r/w operations.
     */
    char buffer_[1024];
};