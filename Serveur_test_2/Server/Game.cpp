#include "Game.h"
#include <iostream>
#include <stdlib.h>

#include <boost/property_tree/json_parser.hpp>

const float PHEROMON_DROP_AMOUNT = 0.2;
const float PHEROMON_DECREASE_AMOUNT = 0.1;


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
	
	numberOfTiles = _size_side_maze * _size_side_maze;
	std::vector<float> vector1(numberOfTiles, 0.0);
	p_pheromons = std::move(vector1);
	
	p_actual_players = 0;
	
}

void game::join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session )
{
	std::cout << "game.join" << std::endl;
	Player player_to_add;
	player_to_add.actual_line = p_Maze->nestLine;
	player_to_add.actual_column = p_Maze->nestColumn;
	player_to_add.has_food = false;
	player_to_add.p_uuid = _player_uuid;
	player_to_add._session = _session;


	p_players.push_back(player_to_add);
	p_actual_players += 1;
	
	_session->sendMaze(_player_uuid, p_Maze);
}

void game::move(const boost::uuids::uuid& _player, std::string _move)
{
	std::cout << "Fonction game.move" << std::endl;
	int i = 0;
	while (p_players[i].p_uuid != _player) {
		i++;
	}
	if (_move == "haut") {
		std::cout << "haut" << std::endl;
		(p_players[i].actual_line) -= 1;
	}
	if (_move == "bas") {
		(p_players[i].actual_line) += 1;
	}
	if (_move == "gauche") {
		(p_players[i].actual_column) -= 1;
	}
	if (_move == "droite") {
		(p_players[i].actual_column) += 1;
	}

	/* Si la tile sur laquelle se teouve le joueur est entre 16 compris et 32 alors il est sur une case nourriture
	 Daans une liste, pour representer un tableau, l'index de la liste avec deux coordonées d'un tableau, l'index vaut le nombre de cases
	déjà complètes (donc le nombre de lignes complètes : actual_Line * le nombre de case par lignes : nbColumn)
					+ le nombres de cases de la ligne imcomplète (+ actualColumn)*/

	if (16 <= p_Maze->tiles[p_players[i].actual_line * p_Maze->nbColumn + p_players[i].actual_column] < 32 && p_players[i].has_food == false) {
		p_players[i].has_food == true;
	}

	// Si la case du jouer est la case Nest et qu'il a de la nourriture, alors il dépose se nourriture et ne l'as plus

	if (p_players[i].actual_column == p_Maze->nestColumn && p_players[i].actual_line == p_Maze->nestLine && p_players[i].has_food == true) {
		p_players[i].has_food == false;
	}

	/* Si le joueur a de la nourriture à ce moment du code, cela veut dire qu'il nest pas sur un nid, 
	donc on augmente la valeur en phreromone de la case */

	if (p_players[i].has_food == true) {
		p_pheromons[p_players[i].actual_line * p_Maze->nbColumn + p_players[i].actual_column] += PHEROMON_DROP_AMOUNT;
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

void game::decreasePheromons()
{
	/*
	- vector[i] <- (1 - evaporation) * vector[i]
	- players[i].session.sendInfo(vector)
	*/


	// On fait decroitre la valeur de chaque case
	for (int i = 0; i <= numberOfTiles; i++) {
		p_pheromons[i] = (1 - PHEROMON_DECREASE_AMOUNT) * p_pheromons[i];
	}

	//Puis on envoi ce vecteur à chaque joueur.

	for (int j = 0; j <= p_actual_players; j++) {
		p_players[j]._session;
	}
}
