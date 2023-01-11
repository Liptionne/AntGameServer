#include "Game.h"
#include <iostream>
#include <stdlib.h>


game::game(const int& _difficulty, const int& _max_nb_players, int _size_side_maze) : difficulty{ _difficulty }, MAX_PLAYERS{ _max_nb_players }
{
	std::cout << "game creation" << '\n';
	//cr�er le labyrinthe
	ParamMaze parameters_maze;

	if (_difficulty == 1) {
		parameters_maze.nbColumn = Constants::DIFFICULTY1_SIDE_SIZE;
		parameters_maze.nbLine = Constants::DIFFICULTY1_SIDE_SIZE;
		parameters_maze.nbFood = Constants::DIFFICULTY1_NBFOOD;
		parameters_maze.nestLine = Constants::DIFFICULTY1_NESTLINE;
		parameters_maze.nestColumn = Constants::DIFFICULTY1_NESTCOLUMN;
		numberOfTiles = Constants::DIFFICULTY1_SIDE_SIZE * Constants::DIFFICULTY1_SIDE_SIZE;
	}

	else if (_difficulty == 2) {
		parameters_maze.nbColumn = Constants::DIFFICULTY2_SIDE_SIZE;
		parameters_maze.nbLine = Constants::DIFFICULTY2_SIDE_SIZE;
		parameters_maze.nbFood = Constants::DIFFICULTY2_NBFOOD;
		parameters_maze.nestLine = Constants::DIFFICULTY2_NESTLINE;
		parameters_maze.nestColumn = Constants::DIFFICULTY2_NESTCOLUMN;
		numberOfTiles = Constants::DIFFICULTY2_SIDE_SIZE * Constants::DIFFICULTY2_SIDE_SIZE;
	}

	else if (_difficulty == 3) {
		parameters_maze.nbColumn = Constants::DIFFICULTY3_SIDE_SIZE;
		parameters_maze.nbLine = Constants::DIFFICULTY3_SIDE_SIZE;
		parameters_maze.nbFood = Constants::DIFFICULTY3_NBFOOD;
		parameters_maze.nestLine = Constants::DIFFICULTY3_NESTLINE;
		parameters_maze.nestColumn = Constants::DIFFICULTY3_NESTCOLUMN;
		numberOfTiles = Constants::DIFFICULTY3_SIDE_SIZE* Constants::DIFFICULTY3_SIDE_SIZE;
	}
	
	parameters_maze.difficulty = _difficulty;
	p_Maze = generateMaze(&parameters_maze);
	
	std::vector<float> vector1(numberOfTiles, 0.0);
	p_pheromons = std::move(vector1);
	
	p_actual_players = 0;
	
}

game::~game()
{
	std::cout << "destruction de game : "<< difficulty << ";" << p_actual_players << std::endl;
	freeMaze(&p_Maze);
}


void game::join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session )
{
	
	Player player_to_add;
	player_to_add.actual_line = p_Maze->nestLine;
	player_to_add.actual_column = p_Maze->nestColumn;
	player_to_add.has_food = false;
	player_to_add.p_uuid = _player_uuid;
	player_to_add._session = _session;


	p_players.push_back(player_to_add);
	p_actual_players += 1;
	
	_session->setGame(this);
	_session->sendMaze(_player_uuid, p_Maze);
}

void game::move(const boost::uuids::uuid& _player, std::string _move)
{
	int i = 0;
	while (p_players[i].p_uuid != _player) {
		i++;
	}
	if (_move == "haut") {
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

	/* Si la tile sur laquelle se trouve le joueur est entre 16 compris et 32 alors il est sur une case nourriture
	 Daans une liste, pour representer un tableau, l'index de la liste avec deux coordon�es d'un tableau, l'index vaut le nombre de cases
	d�j� compl�tes (donc le nombre de lignes compl�tes : actual_Line * le nombre de case par lignes : nbColumn)
					+ le nombres de cases de la ligne imcompl�te (+ actualColumn)*/

	if (16 <= p_Maze->tiles[p_players[i].actual_line * p_Maze->nbColumn + p_players[i].actual_column] < 32 && p_players[i].has_food == false) {
		p_players[i].has_food == true;
	}

	// Si la case du jouer est la case Nest et qu'il a de la nourriture, alors il d�pose se nourriture et ne l'as plus

	if (p_players[i].actual_column == p_Maze->nestColumn && p_players[i].actual_line == p_Maze->nestLine && p_players[i].has_food == true) {
		p_players[i].has_food == false;
	}

	/* Si le joueur a de la nourriture � ce moment du code, cela veut dire qu'il nest pas sur un nid, 
	donc on augmente la valeur en pheromone de la case */

	if (p_players[i].has_food == true) {
		p_pheromons[p_players[i].actual_line * p_Maze->nbColumn + p_players[i].actual_column] += Constants::PHEROMON_DROP_AMOUNT;
	}
	

}

void game::remove(std::shared_ptr<session> _session)
{
	std::cout << "focnotion remove" << std::endl;
	int i = 0;
	while (p_players[i]._session != _session) {
		i++;
	}
	p_players.erase(p_players.begin() + i);
	p_actual_players -= 1;
	if (p_actual_players == 0) {
		endGame();
	}
}
void game::endGame() {
	std::cout << "fin de la partie" << std::endl;
	delete this;
}


void game::decreasePheromons()
{
	/*
	- vector[i] <- (1 - evaporation) * vector[i]
	- players[i].session.sendInfo(vector)
	*/

	// On fait decroitre la valeur de chaque case
	for (int i = 0; i < numberOfTiles; i++) {
		p_pheromons[i] = (1 - Constants::PHEROMON_DECREASE_AMOUNT) * p_pheromons[i];
	}

	//Puis on envoi ce vecteur � chaque joueur.

	for (int j = 0; j < p_actual_players; j++) {
		p_players[j]._session->sendPheromons(p_players[j].p_uuid,p_pheromons);
	}
}
