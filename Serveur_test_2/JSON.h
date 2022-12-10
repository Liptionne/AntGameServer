#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/uuid/uuid.hpp>  
#include <vector>
#include <iostream>

namespace JSON {
	std::string getUUID(const boost::property_tree::ptree& root);

	std::string getType(const boost::property_tree::ptree& root);

	int getDifficultyJoin(const boost::property_tree::ptree& root);

	std::string getMove(const boost::property_tree::ptree& root);
}

