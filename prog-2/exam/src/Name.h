#pragma once

#include <string>
#include "Serializable.h"

#define NUMBER_OF_ATTRIBUTES_NAME 2

class Name : public Serializable {
public:
    std::string firstname;
    std::string lastname;

    Name();
    Name(std::string const _firstname, std::string const _lastname);

    std::string serializeToString() const;
    void deserializeFromString(std::string const &s);

    bool operator!=(Name const &other);
    bool operator==(Name const &other);
};
