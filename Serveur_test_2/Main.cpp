#include "server/server.h"
#include "Client/client.h"  

#include <thread>
#include <chrono>




void test() { //Juste pour faire le test de l'envoi du JSON join de la part du client
    std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //on attend un peu pour etre sur que tout est bien initialisé
    std::string adress = "127.0.0.1";
    short port = 5000;
    std::shared_ptr<Client> client1 = std::make_shared<Client>(adress, port);
    client1->envoyerJSON("JOIN.json", client1->getSocket());
    
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