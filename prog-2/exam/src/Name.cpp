#include <string>
#include <vector>
#include "Serializable.h"
#include "Util.hpp"
#include "Exceptions.hpp"
#include "Name.h"

using namespace std;

/**
 * Constructor for setting empty attributes.
 */
Name::Name() {
    firstname = "";
    lastname = "";
}

/**
 * Constructor for setting the attributes.
 */
Name::Name(string const _firstname, string const _lastname) {
    firstname = _firstname;
    lastname = _lastname;
}

/**
 * @return A string that can be used to set a name's attributes later.
 * It is a compact string representation of a name.
 */
string Name::serializeToString() const {
    return firstname + SERIALIZATION_SEPARATOR + lastname;
}

/**
 * Sets the name's attributes according to the given string.
 * The string has to be in the following format:
 * "firstname,lastname"
 * 
 * usage: name.deserializeFromString("John,Smith");
 * 
 * @param s - The string used to set the name's attributes.
 * 
 * @throw DeserializationException - When the string cannot be used to set the 
 * name's attributes because of a wrong format.
 */
void Name::deserializeFromString(const std::string &s) {
    vector<string> v = Util::split(s, SERIALIZATION_SEPARATOR);

    if (NUMBER_OF_ATTRIBUTES_NAME != v.size()) {
        throw DeserializationException("To many attributes given in the string! " + to_string(v.size()) + " given but " + to_string(NUMBER_OF_ATTRIBUTES_NAME) + " required: \"" + s + "\"");
    }

    firstname = v[0];
    lastname = v[1];
}

bool Name::operator!=(Name const &other) {
    return firstname != other.firstname || lastname != other.lastname;
}

bool Name::operator==(Name const &other) {
    return firstname == other.firstname && lastname == other.lastname;
}
