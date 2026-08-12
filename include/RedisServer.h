#pragma once

#include <atomic>
#include <string>

class RedisServer {
public:
  RedisServer(int port);
  void run();
  void shutdown();

private:
  int port;
  int server_socket;
  std::atomic<bool> running;

  // Setup Signal Handling for graceful shutdown
  void setupSignalHandler();
};
