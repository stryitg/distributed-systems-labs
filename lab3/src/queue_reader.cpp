#include <hazelcast/client/HazelcastClient.h>
#include <chrono>
#include <string>
#include <iostream>

std::string get_queue_name(const std::string& argv) {
    if(argv == "blocking") {
        return "my-blocking-queue";
    } else {
        return "my-distributed-queue";
    }
}

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto queue = hz.getQueue<int>(get_queue_name(argv[1]));
    for(;;) {
        std::cout << "Taking: ";
        const auto val = queue.take();
        if (!val) {
            continue;    
        }
        std::cout << *val << std::endl;
        
        if (*val == -1) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    queue.put(-1);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << " Finished" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}