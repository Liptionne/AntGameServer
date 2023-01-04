#pragma once
#include "server.h"

#include <functional>

#include <boost/asio.hpp>
#include "session.h"

using std::placeholders::_1;
using std::placeholders::_2;

using boost::asio::io_context;
using boost::asio::error::eof;
using boost::system::error_code;
using boost::system::system_error;

server::server(boost::asio::io_context& service,
    const unsigned short port)
    : service_{ service }, acceptor_{ service } {
        

    
        game game1(1, Constants::DIFFICULTY1_MAX_PLAYERS,Constants::DIFFICULTY1_SIDE_SIZE);
        game game2(2, Constants::DIFFICULTY2_MAX_PLAYERS, Constants::DIFFICULTY2_SIDE_SIZE);
        game game3(3, Constants::DIFFICULTY3_MAX_PLAYERS, Constants::DIFFICULTY3_SIDE_SIZE);
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

game* server::getGame(const boost::uuids::uuid& _uuid)
{
    int i = 0;
    while (_players_games[i].first != _uuid) {
        i++;
    }
   return &(_players_games[i].second);
}

void server::handle_accept( std::shared_ptr<session> new_session,
    const boost::system::error_code& ec) {

    std::cout << "creation" << std::endl;
    if (ec) {
        throw system_error{ ec };
    }

    new_session->listen();
    start_accept();
}

void server::matchmaking(int _difficulty, boost::uuids::uuid _uuid, std::shared_ptr<session> _session)
{
    game& game_ = _games[_difficulty - 1];
    if (game_.getMax_Players() == game_.getNb_Players()) {
        std::cout << "new game matchmaking" << std::endl;
        
        if (_difficulty == 1) {
            game newgame(1, Constants::DIFFICULTY1_MAX_PLAYERS, Constants::DIFFICULTY1_SIDE_SIZE);
            _games.insert(_games.begin() + (_difficulty - 1), newgame);
            newgame.join(_uuid, _session);
            _players_games.push_back(std::pair(_uuid, newgame));
            
        }
        else if (_difficulty == 2) {
            game newgame(2, Constants::DIFFICULTY2_MAX_PLAYERS, Constants::DIFFICULTY2_SIDE_SIZE);
            _games.insert(_games.begin() + (_difficulty - 1), newgame);
            newgame.join(_uuid, _session);
            _players_games.push_back(std::pair(_uuid, newgame));
        }
        else if (_difficulty == 3) {
            game newgame(3, Constants::DIFFICULTY3_MAX_PLAYERS, Constants::DIFFICULTY3_SIDE_SIZE);
            _games.insert(_games.begin() + (_difficulty - 1), newgame);
            newgame.join(_uuid, _session);
            _players_games.push_back(std::pair(_uuid, newgame));
        }
        
    }
    else {
        game_.join(_uuid, _session);
        //_session->setGame(&game_);
        _players_games.push_back(std::pair(_uuid, game_));
    }
}


