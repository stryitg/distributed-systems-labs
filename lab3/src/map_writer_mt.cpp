#include <hazelcast/client/HazelcastClient.h>
#include <chrono>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto map = hz.getMap<std::string, int>("my-distributed-map"); 
    const std::string key = "hello_world";
    map.putIfAbsent(key, 0);
    for(size_t i = 0; i < 1000; ++i) {
        try {
            if(std::string(argv[1]) == "pessimistic") {
                map.lock(key);
                auto val = map.get(key);
                *val += 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                map.put(key, *val);
                map.unlock(key);
            } else if(std::string(argv[1]) == "optimistic") {
                for(;;) {
                    auto val = map.get(key);
                    *val += 1;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    if(map.replace(key, *val - 1, *val)) {
                        break;
                    }
                }
            }
            
        } catch(...) {
            map.unlock(key);
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Last read value: " << *map.get(key) << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    map.clear();
    return 0;
}