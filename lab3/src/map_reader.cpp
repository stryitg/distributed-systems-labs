#include <hazelcast/client/HazelcastClient.h>
#include <string>
#include <iostream>

std::string get_map_name(const std::string& argv) {
    return "my-distributed-map" + argv;
}

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto map = hz.getMap<std::string, std::string>(get_map_name(argv[1]));
    size_t count = 0;
    try {
        for(const auto& [key, val]: map.entrySet()) {
            ++count;
        }
    } catch (...) {}
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::to_string(count) << " elements read" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    map.clear();
    return 0;
}