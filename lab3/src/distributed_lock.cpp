#include <hazelcast/client/HazelcastClient.h>
#include "hazelcast/client/ILock.h"
#include <string>
#include <iostream>
#include <mutex>

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto lock = std::make_unique<hazelcast::client::ILock>(hz.getILock("my-lock_"));
    auto queue = hz.getQueue<int>("my-distributed-queue"); 
    queue.clear();
    for(size_t i = 0; i < 20; ++i) {
        try {
            if (std::string(argv[1]) == "with-lock")
                lock->lock();
            queue.put(++i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.put(++i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.put(++i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.put(++i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            queue.put(++i);
            --i;
            if (std::string(argv[1]) == "with-lock")
                lock->unlock();
        } catch(...) {
            if (std::string(argv[1]) == "with-lock")
                lock->unlock();
        }
    }
    queue.put(-1);
    

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Finished" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}