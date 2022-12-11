#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>  
#include <vector>
#include <iostream>
#include "Maze/libAntMaze.h"



namespace JSON {

	// ------------------------------- READING in JSON ---------------------------
	std::string getUUID(const boost::property_tree::ptree& root);

	std::string getType(const boost::property_tree::ptree& root);

	int getDifficultyJoin(const boost::property_tree::ptree& root);

	std::string getMove(const boost::property_tree::ptree& root);

	void getMaze(const boost::property_tree::ptree& root, Maze* _maze);

	std::vector <float> getPheromons(const boost::property_tree::ptree& root);

	

	// ------------------------------- CREATING a JSON (return a string to send it easily) ---------------------------

	std::string createGeneric(boost::uuids::uuid _uuid,boost::property_tree::ptree _root);

	std::string createJoin(boost::uuids::uuid _uuid, int _difficulty);

	std::string createMove(boost::uuids::uuid _uuid, std::string _move);

	std::string createokMaze(boost::uuids::uuid _uuid, Maze _maze);

	std::string createInfo(boost::uuids::uuid _uuid, std::vector<float> _pheromons);

}