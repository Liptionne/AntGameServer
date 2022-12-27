#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <memory>
#include <boost/uuid/uuid.hpp>   
#include "../Maze/libAntMaze.h"
#include "../JSON.h"

#define NULL_UUID    { 00000000 - 0000 - 0000 - 0000 - 000000000000 }

using boost::asio::ip::tcp;



class Client : public std::enable_shared_from_this<Client> {
private:
    boost::asio::io_context& p_io_context;
    tcp::socket p_socket_client;
    boost::uuids::uuid p_uuid;
    boost::asio::streambuf p_buffer{ 2048 };
    Maze* p_maze;
public:
    Client(boost::asio::io_context& io_context1,std::string _adress, short _port);


    void join();
    void handle_write_client(const std::error_code& ec);
    void move(std::string _move);
    void handle_read_client(const boost::system::error_code& ec,
        size_t bytes_transferred);
    void listen_client();
    void setMaze(Maze* _maze) { p_maze = _maze; }
};