#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <memory>
#include <boost/uuid/uuid.hpp>   

using boost::asio::ip::tcp;



class Client {
private:
    boost::asio::io_context p_io_context;
    std::shared_ptr<tcp::socket> p_socket;
    boost::uuids::uuid p_uuid;
public:
    Client(std::string _adress, short _port);
    std::shared_ptr<tcp::socket> getSocket() { return p_socket; };

    void envoyerJSON(std::string file, std::shared_ptr<tcp::socket> socket_);

};