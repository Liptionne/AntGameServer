#include "server/server.h"
#include "Client/client.h"  

#include <numeric>
#include <thread>
#include <boost/thread.hpp>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

void test() { //Juste pour faire le test de l'envoi du JSON join de la part du client
    std::this_thread::sleep_for(std::chrono::milliseconds(3000)); //on attend un peu pour etre sur que tout est bien initialisé
    Client* client1 = new Client("127.0.0.1", 5000);
    client1->envoyerJSON("JOIN.json", client1->getSocket());
    free(client1);
}

int main() {
    unsigned short port = 5000;
    
    std::thread t(test);


    boost::asio::io_service service{};


    server s{ service, port };


    service.run();
    t.join();
    return 0;
}