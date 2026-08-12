#include "../include/RedisDatabase.h"
#include "../include/RedisServer.h"

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
  int port = 6379;
  if (argc >= 2)
    port = std::stoi(argv[1]);

  if (RedisDatabase::getInstance().load("dump.my_rdb"))
    std::cout << "Database Loaded From dump.my_rdb\n";
  else
    std::cout
        << "No dump found or load failed; starting with an empty database.\n";

  RedisServer server(port);

  // Thread running in background to save database every 300 seconds
  std::thread persistance_thread([]() {
    while (true) {
      std::this_thread::sleep_for(std::chrono::seconds(300));
      if (!RedisDatabase::getInstance().dump("dump.my_rdb"))
        std::cerr << "Error Dumping Database\n";
      else
        std::cout << "Database Dumped to dump.my_rdb\n";
    }
  });

  persistance_thread.detach();

  server.run();
  return 0;
}