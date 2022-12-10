#include "Game.h"
#include <iostream>

game::game(const int& _difficulty, const int& _max_nb_players) : difficulty{ _difficulty }, MAX_PLAYERS{ _max_nb_players }
{
	//créer le labyrinthe
	//initialise le std::vector de session
	Actual_players = 0;
	
}

void game::join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session)
{
	std::cout << "game.join" << std::endl;
	players.push_back(_session);
	Actual_players += 1;
	_session->setGame(this);
	//lui envoi le labyrinthe
}

void game::move(const boost::uuids::uuid& _player, std::string _move)
{
}

void game::updateMaze()
{
}

void game::startGame()
{
}

void game::stopGame()
{
}
