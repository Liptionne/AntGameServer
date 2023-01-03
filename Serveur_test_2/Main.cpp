#include "server/server.h"
#include "Client/client.h"  

#include <thread>
#include <chrono>




void test() { //Juste pour faire le test de l'envoi du JSON join de la part du client
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); //on attend un peu pour etre sur que tout est bien initialisť
    std::string adress = "127.0.0.1";
    short port = 9999;
    boost::asio::io_context io_context1;
    Client client1{ io_context1, adress, port };
    auto t1 = std::thread([&]
        {
            io_context1.run();
        });
    
    client1.join();
   
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    client1.move("haut");
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    
    client1.move("haut");

    t1.join();
}

int main() {
    unsigned short port = 9999;
    
    std::thread thread_client(test);

    boost::asio::io_context service{};

    server s{ service, port };

    service.run();
    thread_client.join();
    return 0;
}