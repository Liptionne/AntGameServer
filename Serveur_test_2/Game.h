#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include "session.h"
#include <boost/uuid/uuid.hpp>
#include <memory>
#include "JSON.h"
#include "libAntMaze.h"

class game
{
private:
	int difficulty;
	std::vector<std::shared_ptr<session>> players;
	int MAX_PLAYERS;
	int Actual_players;

	Maze test;
public:
	game(const int& _difficulty,const int& _max_nb_players);

	void join(const boost::uuids::uuid& _player_uuid, std::shared_ptr<session> _session);
	int getMax_Players() { return MAX_PLAYERS; }
	int getNb_Players() { return Actual_players; }
	void move(const boost::uuids::uuid & _player, std::string _move );
	void updateMaze();
	void startGame();
	void stopGame();
	Maze getMaze();
	
};

