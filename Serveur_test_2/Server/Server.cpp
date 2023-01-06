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
    : p_context{ service }, p_acceptor{ service } {
        

    
        game game1(1, Constants::DIFFICULTY1_MAX_PLAYERS,Constants::DIFFICULTY1_SIDE_SIZE);
        game game2(2, Constants::DIFFICULTY2_MAX_PLAYERS, Constants::DIFFICULTY2_SIDE_SIZE);
        game game3(3, Constants::DIFFICULTY3_MAX_PLAYERS, Constants::DIFFICULTY3_SIDE_SIZE);
        p_games.push_back(game1);
        p_games.push_back(game2);
        p_games.push_back(game3);
        

        endpoint_t endpoint{ boost::asio::ip::tcp::v4(), port };
        p_acceptor.open(endpoint.protocol());
        p_acceptor.set_option(acceptor_t::reuse_address(false));
        p_acceptor.bind(endpoint);
        p_acceptor.listen();
        startAccept();
}

void server::startAccept() {

    
    std::shared_ptr<session> new_session{ std::make_shared<session>(p_context, this)};
    auto handler =
        std::bind(&server::handleAccept, this, new_session, _1);
    p_acceptor.async_accept(new_session->socket(), handler);
}

game* server::getGame(const boost::uuids::uuid& _uuid)
{
    int i = 0;
    while (p_players_game[i].first != _uuid) {
        i++;
    }
   return &(p_players_game[i].second);
}

void server::handleAccept( std::shared_ptr<session> new_session,
    const boost::system::error_code& ec) {

    std::cout << "creation" << std::endl;
    if (ec) {
        throw system_error{ ec };
    }

    new_session->listen();
    startAccept();
}

void server::findGameWithDifficulty(int _difficulty, boost::uuids::uuid _uuid, std::shared_ptr<session> _session)
{
    game& game_ = p_games[_difficulty - 1];
    if (game_.getMax_Players() == game_.getNb_Players()) {
        std::cout << "new game matchmaking" << std::endl;
        
        if (_difficulty == 1) {
            game newgame(1, Constants::DIFFICULTY1_MAX_PLAYERS, Constants::DIFFICULTY1_SIDE_SIZE);
            p_games.insert(p_games.begin() + (_difficulty - 1), newgame);
            newgame.join(_uuid, _session);
            p_players_game.push_back(std::pair(_uuid, newgame));
            
        }
        else if (_difficulty == 2) {
            game newgame(2, Constants::DIFFICULTY2_MAX_PLAYERS, Constants::DIFFICULTY2_SIDE_SIZE);
            p_games.insert(p_games.begin() + (_difficulty - 1), newgame);
            newgame.join(_uuid, _session);
            p_players_game.push_back(std::pair(_uuid, newgame));
        }
        else if (_difficulty == 3) {
            game newgame(3, Constants::DIFFICULTY3_MAX_PLAYERS, Constants::DIFFICULTY3_SIDE_SIZE);
            p_games.insert(p_games.begin() + (_difficulty - 1), newgame);
            newgame.join(_uuid, _session);
            p_players_game.push_back(std::pair(_uuid, newgame));
        }
        
    }
    else {
        game_.join(_uuid, _session);
        //_session->setGame(&game_);
        p_players_game.push_back(std::pair(_uuid, game_));
    }
}


