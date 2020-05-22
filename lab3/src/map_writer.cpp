#include <hazelcast/client/HazelcastClient.h>
#include <chrono>
#include <string>
#include <iostream>

std::string get_map_name(const std::string& argv) {
    return "my-distributed-map" + argv;
}

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto map = hz.getMap<std::string, std::string>(get_map_name(argv[1]));
    std::chrono::seconds duration(10);
    const auto begin = std::chrono::system_clock::now();
    size_t i = 0;
    for(; std::chrono::system_clock::now() < begin + duration; ++i) {
        try {
            map.put(std::to_string(i), std::to_string(i));
        } catch(...) {}
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::to_string(i) << " cycles" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}