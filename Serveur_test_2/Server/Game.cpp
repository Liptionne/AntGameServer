#include "Game.h"
#include <iostream>
#include <boost/property_tree/json_parser.hpp>


game::game(const int& _difficulty, const int& _max_nb_players, int _size_side_maze) : difficulty{ _difficulty }, MAX_PLAYERS{ _max_nb_players }
{
	//créer le labyrinthe
	ParamMaze parameters_maze;
	
	parameters_maze.nbColumn = _size_side_maze;
	parameters_maze.nbLine = _size_side_maze;
	parameters_maze.nbFood = 2;
	parameters_maze.nestLine = 19;
	parameters_maze.nestColumn = 19;
	parameters_maze.difficulty = _difficulty;
	p_Maze = generateMaze(&parameters_maze);
	std::vector<float> vector1(_size_side_maze * _size_side_maze, 0.0);
	p_pheromons = std::move(vector1);
	Actual_players = 0;
	
}

void game::join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session)
{
	std::cout << "game.join" << std::endl;
	players.push_back(_session);
	Actual_players += 1;
	_session->setGame(this);
	std::string coucou = JSON::createokMaze(_player_uuid,*p_Maze);
	
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
