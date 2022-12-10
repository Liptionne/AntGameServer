#include "client.h"

Client::Client(std::string _adress, short _port) {
    p_socket = std::make_shared<tcp::socket>(p_io_context);
    p_socket->connect(tcp::endpoint(boost::asio::ip::address::from_string(_adress), _port));
}

void Client::envoyerJSON(std::string file, std::shared_ptr<tcp::socket> socket_) {
    boost::property_tree::ptree root;
    std::stringstream ss;
    boost::system::error_code error;

    boost::property_tree::read_json("D:/testjson.json", root);

    boost::property_tree::write_json(ss, root);
    std::string string = ss.str();


    boost::asio::write(*socket_, boost::asio::buffer(string), error);

    if (!error) {
        std::cout << "Send successfull" << std::endl;
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }

}