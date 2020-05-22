#include <hazelcast/client/HazelcastClient.h>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto topic = hz.getTopic<std::string>("my-topic");
    for(size_t i = 0; i < 20; ++i) {
        std::cout << "Putting: " << std::to_string(i) << std::endl;
        topic.publish(std::to_string(i));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

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