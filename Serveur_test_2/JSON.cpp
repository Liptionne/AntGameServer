#include "JSON.h"

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

