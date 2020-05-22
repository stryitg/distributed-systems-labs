#include <hazelcast/client/HazelcastClient.h>
#include <string>
#include <iostream>
#include <memory>

struct Listener : public hazelcast::client::topic::MessageListener<std::string>  {
    void onMessage(std::auto_ptr<hazelcast::client::topic::Message<std::string>> message) override {
        std::cout << *message->getMessageObject() << std::endl;
    }
};

int main(int argc, char** argv) {
    hazelcast::client::ClientConfig config;
    hazelcast::client::HazelcastClient hz(config);
    auto topic = hz.getTopic<std::string>("my-topic");
    Listener l;
    topic.addMessageListener(l);
    while(true);

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