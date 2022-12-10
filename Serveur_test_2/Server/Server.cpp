#include "server.h"

#include <functional>

#include <boost/asio.hpp>
#include "session.h"

using std::placeholders::_1;
using std::placeholders::_2;

using boost::asio::io_service;
using boost::asio::error::eof;
using boost::system::error_code;
using boost::system::system_error;

server::server(boost::asio::io_service& service,
    const unsigned short port)
    : service_{ service }, acceptor_{ service } {
        
        game game1(1, 10);
        game game2(2, 10);
        game game3(3, 10);
        _games.push_back(game1);
        _games.push_back(game2);
        _games.push_back(game3);

        endpoint_t endpoint{ boost::asio::ip::tcp::v4(), port };
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(acceptor_t::reuse_address(false));
        acceptor_.bind(endpoint);
        acceptor_.listen();
        start_accept();
}

void server::start_accept() {
    std::shared_ptr<session> new_session{ std::make_shared<session>(service_, this)};
    auto handler =
        std::bind(&server::handle_accept, this, new_session, _1);
    acceptor_.async_accept(new_session->socket(), handler);
}

void server::handle_accept( std::shared_ptr<session> new_session,
    const boost::system::error_code& ec) {
    if (ec) {
        throw system_error{ ec };
    }

    new_session->listen();
    start_accept();
}

void server::matchmaking(int _difficulty, boost::uuids::uuid _uuid, std::shared_ptr<session> _session)
{
    std::cout << "matchmaking" << std::endl;
    game game_ = _games[_difficulty - 1];
    if (game_.getMax_Players() == game_.getNb_Players()) {
        game newgame(_difficulty, 10);
        _games.insert(_games.begin() + (_difficulty - 1), newgame);
    }
    game_.join(_uuid, _session);
}


