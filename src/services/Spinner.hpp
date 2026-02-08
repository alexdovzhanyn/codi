#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>

class Spinner {
public:
  explicit Spinner(const std::string &message) : running(true), thread([this, message] {
    const char* frames[] = { "⠋","⠙","⠹","⠸","⠼", "⠴","⠦","⠧","⠇","⠏" };
    size_t i = 0;

    while (running) {
      std::cout << "\r" << frames[i++ % 10] << " " << message << std::flush;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\r" << message << std::flush;
  }) {}

  ~Spinner() {
    stop();
  }

  void stop() {
    if (!running) return;

    running = false;
    thread.join();
  }

private:
  std::atomic<bool> running;
  std::thread thread;

};
