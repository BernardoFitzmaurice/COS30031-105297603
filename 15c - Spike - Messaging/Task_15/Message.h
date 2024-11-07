#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Entity;

class Message {
public:
    Entity* sender;
    Entity* receiver;
    std::string messageType;
    std::string data;  // Changed from std::any to std::string

    Message(Entity* sender, Entity* receiver, const std::string& messageType, const std::string& data = "")
        : sender(sender), receiver(receiver), messageType(messageType), data(data) {}
};

#endif
