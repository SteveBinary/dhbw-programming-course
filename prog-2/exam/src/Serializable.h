#pragma once

#include <string>

#define SERIALIZATION_SEPARATOR ','

class Serializable {
public:

    virtual ~Serializable() {
        // virtual destructor to prevent memory leaks
    }

    virtual std::string serializeToString() const = 0;
    virtual void deserializeFromString(std::string const &s) = 0;
};
