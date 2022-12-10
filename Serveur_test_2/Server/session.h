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
     * Callback for socket writes.
     */
    void handle_write(const boost::system::error_code& ec);

    /**
     * Get a reference to the session socket.
     */
    socket_t& socket() { return socket_; }

    server* getServer() { return _origin; }

    void setGame(game* _game) { game = _game; };
    

private:
    /**
     * Session socket
     */
    game* game;
    socket_t socket_;
    server* _origin;
    /**
     * Buffer to be used for r/w operations.
     */
    char buffer_[1024];
};