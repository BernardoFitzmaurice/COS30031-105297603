#ifndef PROPERTY_COMPONENT_H
#define PROPERTY_COMPONENT_H

#include <string>
#include <unordered_map>

class PropertyComponent {
public:
    virtual ~PropertyComponent() = default;
    virtual std::string getType() const = 0;
    virtual std::unordered_map<std::string, int> getProperties() const = 0;
};

#endif