#include "Game.h"
#include <iostream>
#include <stdlib.h>

#include <boost/property_tree/json_parser.hpp>


game::game(const int& _difficulty, const int& _max_nb_players, int _size_side_maze) : difficulty{ _difficulty }, MAX_PLAYERS{ _max_nb_players }
{
	std::cout << "creation game" << std::endl;
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

void game::join(const boost::uuids::uuid& _player_uuid)
{
	std::cout << "game.join" << std::endl;
	Player player_to_add;
	player_to_add.actual_line = p_Maze->nestLine;
	player_to_add.actual_column = p_Maze->nestColumn;
	player_to_add.has_food = false;
	player_to_add.p_uuid = _player_uuid;

	players.push_back(player_to_add);
	Actual_players += 1;
	
}

void game::move(const boost::uuids::uuid& _player, std::string _move)
{
	std::cout << "Fonction game.move" << std::endl;
	int i = 0;
	while (players[i].p_uuid != _player) {
		i++;
	}
	if (_move == "haut") {
		std::cout << "haut" << std::endl;
		(players[i].actual_line) -= 1;
	}
	if (_move == "bas") {
		(players[i].actual_line) += 1;
	}
	if (_move == "gauche") {
		(players[i].actual_column) -= 1;
	}
	if (_move == "droite") {
		(players[i].actual_column) += 1;
	}
	

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
