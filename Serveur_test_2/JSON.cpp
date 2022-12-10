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
    root.put("body.maze", _maze);
    return createGeneric(_uuid, root);
}

std::string JSON::createInfo(boost::uuids::uuid _uuid, std::vector<float> _pheromons)
{
    boost::property_tree::ptree root;
    root.put("type", "info");
    root.put("body.maze", _pheromons);
    return createGeneric(_uuid, root);
}

