#include "client.h"

Client::Client(std::string _adress, short _port) {
    socket = std::make_shared<tcp::socket>(io_context);
    socket->connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 5000));
}

void Client::envoyerJSON(std::string file, std::shared_ptr<tcp::socket> socket_) {
    boost::property_tree::ptree root;
    std::stringstream ss;
    boost::system::error_code error;

    boost::property_tree::read_json("D:/testjson.json", root);

    boost::property_tree::write_json(ss, root);
    std::string string = ss.str();

    //std::cout << "on va envoyer ca : " << std::endl << string << std::endl;
    //std::cout << "longueur = " << string.length() << std::endl;

    boost::asio::write(*socket_, boost::asio::buffer(string), error);

    if (!error) {
        std::cout << "Send successfull" << std::endl;
    }

    else {
        std::cout << "send failed: " << error.message() << std::endl;
    }

}