#pragma once
#include <functional>
#include <iostream>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <memory>
#include "../JSON.h"
#include "../Maze/libAntMaze.h"
#include "session.h"
#include "player.h"

class game
{
private:
	int difficulty;
	std::vector<Player> p_players;
	int MAX_PLAYERS;
	int p_actual_players;

	std::vector<float> p_pheromons;
	int numberOfTiles;
	Maze* p_Maze;
	
public:
	game(const int& _difficulty,const int& _max_nb_players, int size_side_maze);

	void join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session );
	int getMax_Players() { return MAX_PLAYERS; }
	int getNb_Players() { return p_actual_players; }
	void move(const boost::uuids::uuid & _player, std::string _move );
	void updateMaze();
	void startGame();
	void stopGame();
	Maze* getMaze() { return p_Maze; };
	void decreasePheromons();
};

