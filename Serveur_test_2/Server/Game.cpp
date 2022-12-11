#include "Game.h"
#include <iostream>

game::game(const int& _difficulty, const int& _max_nb_players) : difficulty{ _difficulty }, MAX_PLAYERS{ _max_nb_players }
{
	//créer le labyrinthe
	ParamMaze parameters_maze;
	parameters_maze.nbColumn = 20;
	parameters_maze.nbLine = 20;
	parameters_maze.nbFood = 2;
	parameters_maze.nestLine = 19;
	parameters_maze.nestColumn = 19;
	parameters_maze.difficulty = _difficulty;
	p_Maze = generateMaze(&parameters_maze);
	std::vector<float> vector1(20 * 20, 0.0);
	p_pheromons = std::move(vector1);
	Actual_players = 0;
	
}

void game::join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session)
{
	std::cout << "game.join" << std::endl;
	players.push_back(_session);
	Actual_players += 1;
	_session->setGame(this);
	
	std::cout << JSON::createInfo(_player_uuid,p_pheromons) << std::endl;
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
