#pragma once

#include <vector>
#include <map>
#include <memory>

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>  
#include <boost/uuid/uuid_io.hpp> 


#include "Game.h"

/**
 * Listens to a socket and dispatches sessions for each incoming request.
 */
class server {

    using acceptor_t = boost::asio::ip::tcp::acceptor;
    using endpoint_t = boost::asio::ip::tcp::endpoint;
    using socket_t = boost::asio::ip::tcp::socket;

public:
    std::vector<game> _games;
    std::vector <std::pair<boost::uuids::uuid, game>> _players_games;
    server(boost::asio::io_service& service, unsigned short port);

    void start_accept();

    game getGame(const boost::uuids::uuid& _uuid);

    void handle_accept(std::shared_ptr<session> new_session,
        const boost::system::error_code& ec);
    void matchmaking(int _difficulty, boost::uuids::uuid _uuid, std::shared_ptr<session> _session);

private:

    /**
     * Reference to the I/O service that will call our callbacks.
     */
    boost::asio::io_service& service_;

    /**
     * Acceptors listening to a socket on a port.
     */
    acceptor_t acceptor_;    

};