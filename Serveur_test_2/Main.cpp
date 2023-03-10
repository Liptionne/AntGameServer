#include "server/server.h"
#include "Client/client.h"  

#include <thread>
#include <chrono>




void test() { 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::string adress = "127.0.0.1";
    short port = 9999;
    boost::asio::io_context io_context1;
    Client client1{ io_context1, adress, port };
    
    
    client1.join(1);
   
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    client1.move("haut");
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    client1.move("haut");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main() {

    JSON::LoadOptionFile("options.json");
    
    
    std::thread thread_client(test);

    boost::asio::io_context context{};

    server server{ context, Constants::SERVER_PORT };

    // -------------------------------------------------------------------------

    auto t1 = std::thread([&]
        {
            context.run();
        });

    // -------------------------------------------------------------------------

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        //update all games and send pheromons vector to all connected players
        for (game* game : server.getListofAvailaibleGames()) {
            game->decreasePheromons();
        }
    }

    // -------------------------------------------------------------------------

    thread_client.join();
    t1.join();
    return 0;
}