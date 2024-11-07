#include "Entity.h"
#include "Message.h"
#include "MessageDispatcher.h"

Entity::Entity(const std::string& name, const std::string& description)
    : name(name), description(description) {}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getDescription() const {
    return description;
}

void Entity::receiveMessage(const Message& message) {
    std::cout << name << " received message: " << message.messageType << std::endl;

    if (message.messageType == "open") {
        std::cout << name << " is now open!" << std::endl;
    }
    else if (message.messageType == "attack" && !message.data.empty()) {
        std::cout << name << " is attacked with " << message.data << std::endl;
    }
    else if (message.messageType == "open_response" && !message.data.empty()) {
        std::cout << message.data << std::endl;  // Display additional data from the response
    }
}

void Entity::sendMessage(Entity* receiver, const std::string& messageType, const std::string& data) {
    Message msg(this, receiver, messageType, data);
    MessageDispatcher dispatcher;
    dispatcher.dispatchMessage(msg);
}
