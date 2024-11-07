#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

class Message;

class Entity {
public:
    Entity(const std::string& name, const std::string& description);

    // Accessor functions to get the name and description
    std::string getName() const;
    std::string getDescription() const;

    // Messaging functions
    void receiveMessage(const Message& message);
    void sendMessage(Entity* receiver, const std::string& messageType, const std::string& data = "");

private:
    std::string name;
    std::string description;
};

#endif
