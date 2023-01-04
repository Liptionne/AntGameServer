/** 
 * @file JSON.h
 * @brief Header file for the JSON class
 * @author Gautier
 * @date 04-01-2022
*/

#include "JSON.h"
#include "constants.h"
#include "boost/uuid/uuid_io.hpp"
#include <boost/property_tree/json_parser.hpp>
/**
 * @brief Get the UUID from the JSON ptree
 * @param root The ptree to search in
 * @return The UUID as a string
*/

std::string JSON::getUUID(const boost::property_tree::ptree& root) {


	return root.get<std::string>("body.playerId", "99");
}

/**
 * @brief Get the type from the JSON ptree
 * @param root The ptree to search in
 * @return The type as a string
*/

std::string JSON::getType(const boost::property_tree::ptree& root)
{
	return (root.get<std::string>("type", "0"));

}
/**
 * @brief Get the difficulty from the JSON ptree
 * @param root The ptree to search in
 * @return The difficulty as an integer
*/
int JSON::getDifficultyJoin(const boost::property_tree::ptree& root)
{
	return stoi(root.get<std::string>("body.difficulty", "0"));
}
/**
 * @brief Get the move from the JSON ptree
 * @param root The ptree to search in
 * @return The move as a string
*/
std::string JSON::getMove(const boost::property_tree::ptree& root)
{
	return root.get<std::string>("body.move", "0");
}
/**
 * @brief Get the maze from the JSON ptree
 * @param root The ptree to search in
 * @return The maze as a pointer to a Maze object
*/
Maze* JSON::getMaze(const boost::property_tree::ptree& root)
{

	Maze _maze = { 0 };
	_maze.nbColumn = stoi(root.get<std::string>("body.maze.nbColumn", "0"));
	_maze.nbLine = stoi(root.get<std::string>("body.maze.nbLine", "0"));
	_maze.nestColumn = stoi(root.get<std::string>("body.maze.nestColumn", "0"));
	_maze.nestLine = stoi(root.get<std::string>("body.maze.nestLine", "0"));

	_maze.tiles = (uint8_t*)malloc(sizeof(uint8_t*) * _maze.nbLine * _maze.nbColumn);

	std::string towork = root.get<std::string>("body.maze.tiles", "0");

	char* ptr;
	char* buffer = (char*)towork.c_str();
	ptr = strtok(buffer, " , ");
	int i = 0;
	while (ptr != NULL)
	{
		_maze.tiles[i] = ((uint8_t)atoi(ptr));
		i++;
		ptr = strtok(NULL, " , ");
	}
	return &_maze;
}
/**
 * @brief Get the pheromons from the JSON ptree
 * @param root The ptree to search in
 * @return The pheromons as a vector of floats
*/
std::vector<float> JSON::getPheromons(const boost::property_tree::ptree& root)
{
	std::string towork = root.get<std::string>("body.pheromon", "0");
	std::cout << towork << std::endl;

	char* ptr;
	char* buffer = (char*)towork.c_str();
	ptr = strtok(buffer, " , ");
	int i = 0;
	std::vector<float> vect_to_return;
	while (ptr != NULL)
	{
		vect_to_return.push_back(atof(ptr));
		i++;
		ptr = strtok(NULL, " , ");
	}
	for (int i = 0; i < vect_to_return.size(); i++) {
		std::cout << vect_to_return.at(i) << ' ';
	}
	return vect_to_return;
}
/**
 * @brief Load the global options from a JSON file
 * @param _path The path to the JSON file
*/
void JSON::LoadOptionFile(std::string _path)
{
	boost::property_tree::ptree root;

	boost::property_tree::read_json(_path, root);

	Constants::DIFFICULTY1_MAX_PLAYERS = root.get("difficulty.1.MaxPlayers", 6);
	Constants::DIFFICULTY1_SIDE_SIZE = root.get("difficulty.1.SideOfSideMaze", 20);
	Constants::DIFFICULTY1_NBFOOD = root.get("difficulty.1.NbFoodSources", 2);
	Constants::DIFFICULTY1_NESTLINE = root.get("difficulty.1.NestLine", 19);
	Constants::DIFFICULTY1_NESTCOLUMN = root.get("difficulty.1.NestColumn", 19);

	Constants::DIFFICULTY2_MAX_PLAYERS = root.get("difficulty.2.MaxPlayers", 6);
	Constants::DIFFICULTY2_SIDE_SIZE = root.get("difficulty.2.SideOfSideMaze", 20);
	Constants::DIFFICULTY2_NBFOOD = root.get("difficulty.2.NbFoodSources", 2);
	Constants::DIFFICULTY2_NESTLINE = root.get("difficulty.2.NestLine", 19);
	Constants::DIFFICULTY2_NESTCOLUMN = root.get("difficulty.2.NestColumn", 19);

	Constants::DIFFICULTY3_MAX_PLAYERS = root.get("difficulty.3.MaxPlayers", 6);
	Constants::DIFFICULTY3_SIDE_SIZE = root.get("difficulty.3.SideOfSideMaze", 20);
	Constants::DIFFICULTY3_NBFOOD = root.get("difficulty.3.NbFoodSources", 2);
	Constants::DIFFICULTY3_NESTLINE = root.get("difficulty.3.NestLine", 19);
	Constants::DIFFICULTY3_NESTCOLUMN = root.get("difficulty.3.NestColumn", 19);

	Constants::PHEROMON_DECREASE_AMOUNT = root.get("PheromonDecreaseAmount", 0.1);
	Constants::PHEROMON_DROP_AMOUNT = root.get("PheromonDropAmount", 0.2);

	Constants::VERBOSE = root.get("Verbose", false);
	Constants::SERVER_PORT = root.get<unsigned short>("ServerPort", 9999);
}

/**
 * @brief Create a JSON string with a given UUID and root ptree
 * @param _uuid The UUID to include in the JSON string
 * @param _root The ptree to include in the JSON string
 * @return The created JSON string
*/
std::string JSON::createGeneric(boost::uuids::uuid _uuid, boost::property_tree::ptree _root) {

	_root.put("body.playerId", _uuid);
	std::stringstream ss;
	boost::property_tree::write_json(ss, _root);
	return ss.str();
}
/**
 * @brief Create a "join" JSON string with a given UUID and difficulty
 * @param _uuid The UUID to include in the JSON string
 * @param _difficulty The difficulty to include in the JSON string
 * @return The created "join" JSON string
*/

std::string JSON::createJoin(boost::uuids::uuid _uuid, int _difficulty)
{
	boost::property_tree::ptree root;
	root.put("type", "join");
	root.put("body.difficulty", _difficulty);
	return createGeneric(_uuid, root);
}
/**
 * @brief Create a "move" JSON string with a given UUID and move
 * @param _uuid The UUID to include in the JSON string
 * @param _move The move to include in the JSON string
 * @return The created "move" JSON string
*/
std::string JSON::createMove(boost::uuids::uuid _uuid, std::string _move)
{
	boost::property_tree::ptree root;
	root.put("type", "move");
	root.put("body.move", _move);
	return createGeneric(_uuid, root);
}
/**
 * @brief Create a "okMaze" JSON string with a given UUID and maze
 * @param _uuid The UUID to include in the JSON string
 * @param _maze The maze to include in the JSON string
 * @return The created "okMaze" JSON string
*/
std::string JSON::createokMaze(boost::uuids::uuid _uuid, Maze _maze)
{
	boost::property_tree::ptree root;
	root.put("type", "okMaze");
	root.put("body.maze.nbColumn", _maze.nbColumn);
	root.put("body.maze.nbLine", _maze.nbLine);
	root.put("body.maze.nestColumn", _maze.nestColumn);
	root.put("body.maze.nestLine", _maze.nestLine);

	std::stringstream ss;
	int nbTiles = _maze.nbColumn * _maze.nbLine;
	for (int i = 0; i < nbTiles - 1; i++) {
		ss << (unsigned int)_maze.tiles[i] << ",";
	}
	ss << (unsigned int)_maze.tiles[nbTiles - 1];
	root.put("body.maze.tiles", ss.str());

	return createGeneric(_uuid, root);
}

/**
 * @brief Creates a JSON message with information about pheromons.
 * @param _uuid The UUID of the message.
 * @param _pheromons A vector of pheromons.
 * @return A string containing the JSON message.
 */

std::string JSON::createInfo(boost::uuids::uuid _uuid, std::vector<float> _pheromons)
{
	boost::property_tree::ptree root;
	root.put("type", "info");
	std::stringstream ss;
	std::string str(_pheromons.begin(), _pheromons.end());
	size_t nbPheromons = _pheromons.size() - 1;
	for (int i = 0; i < nbPheromons; i++) {
		ss << _pheromons[i] << ",";

	}
	ss << _pheromons[nbPheromons];

	root.put("body.pheromon", ss.str());

	return createGeneric(_uuid, root);
}

