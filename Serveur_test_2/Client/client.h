#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <memory>
#include <boost/uuid/uuid.hpp>   
#include "../JSON.h"

#define NULL_UUID    { 00000000 - 0000 - 0000 - 0000 - 000000000000 }

using boost::asio::ip::tcp;



class Client : public std::enable_shared_from_this<Client> {
private:
    boost::asio::io_context p_io_context;
    std::shared_ptr<tcp::socket> p_socket_client;
    boost::uuids::uuid p_uuid;
    boost::asio::streambuf p_buffer{ 1024 };
public:
    Client(std::string _adress, short _port);
    std::shared_ptr<tcp::socket> getSocket() { return p_socket_client; };

    void join(std::shared_ptr<tcp::socket> socket_);
    void handle_write_client(const std::error_code& ec);
    void move(std::shared_ptr<tcp::socket> socket_, std::string _move);
    void handle_read_client(const boost::system::error_code& ec,
        size_t bytes_transferred);
    void listen_client();

};