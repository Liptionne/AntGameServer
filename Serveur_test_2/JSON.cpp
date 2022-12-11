#include "JSON.h"
#include "boost/uuid/uuid_io.hpp"
#include <boost/property_tree/json_parser.hpp>

std::string JSON::getUUID(const boost::property_tree::ptree& root) {
    
    try {
        return root.get<std::string>("body.playerId", "99");
        // exemple : 7feb24af-fc38-44de-bc38-04defc3804de
    }
    catch (std::exception& e) {
        std::printf("Exception: %s\n", e.what());
    }
}

std::string JSON::getType(const boost::property_tree::ptree& root)
{
    try {
        return (root.get<std::string>("type", "0"));
    }
    catch (std::exception& e) {
        std::printf("Exception: %s\n", e.what());
    }
}

int JSON::getDifficultyJoin(const boost::property_tree::ptree& root)
{
    return stoi(root.get<std::string>("body.difficulty", "0"));
}

std::string JSON::getMove(const boost::property_tree::ptree& root)
{
    return root.get<std::string>("body.direction","0");
}

void JSON::getMaze(const boost::property_tree::ptree& root, Maze* _maze)
{
    _maze->nbColumn = stoi(root.get<std::string>("body.maze.nbColumn", "0"));
    _maze->nbLine = stoi(root.get<std::string>("body.maze.nbLine", "0"));
    _maze->nestColumn = stoi(root.get<std::string>("body.maze.nestColumn", "0"));
    _maze->nestLine = stoi(root.get<std::string>("body.maze.nestLine", "0"));
    std::string towork = root.get<std::string>("body.maze.tiles", "0");

    char* ptr;    
    char* buffer = (char*)towork.c_str();
    ptr = strtok(buffer, " , ");
    int i = 0;
    while (ptr != NULL)
    {
        _maze->tiles[i] = ((uint8_t)atoi(ptr));
        i++;
        ptr = strtok(NULL, " , ");
    }
    
}

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

// ----------------------------------------------------------------------------------------------------------------------

std::string JSON::createGeneric(boost::uuids::uuid _uuid,boost::property_tree::ptree _root) {
    
    _root.put("body.playerId", _uuid);
    std::stringstream ss;
    boost::property_tree::write_json(ss, _root);
    return ss.str();
}


std::string JSON::createJoin(boost::uuids::uuid _uuid, int _difficulty)
{
    boost::property_tree::ptree root;
    root.put("type", "join");
    root.put("body.difficulty", _difficulty);
    return createGeneric(_uuid, root);
}

std::string JSON::createMove(boost::uuids::uuid _uuid, std::string _move)
{
    boost::property_tree::ptree root;
    root.put("type", "move");
    root.put("body.move", _move);
    return createGeneric(_uuid, root);
}

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
    for (int i = 0; i < nbTiles-1; i++) {
        ss << (unsigned int)_maze.tiles[i] << ",";
    }
    ss << (unsigned int)_maze.tiles[nbTiles - 1];
    root.put("body.maze.tiles", ss.str());
    
    return createGeneric(_uuid, root);
}


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

