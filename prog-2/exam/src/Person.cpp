#include <string>
#include <vector>
#include "Util.hpp"
#include "Serializable.h"
#include "Exceptions.hpp"
#include "Person.h"

#define MAX_FULL_NAME_LENGTH 17
#define CENTER_SALARY_DECIMAL_POINT_POWER 3

using namespace std;

/**
 * Constructor for setting empty attributes.
 */
Person::Person() {
    name = Name();
    age = 0;
    salary = 0.0;
}

/**
 * Constructor for setting the attributes.
 */
Person::Person(string const _firstname, string const _lastname, int const _age, double const _salary) {
    name = Name(_firstname, _lastname);
    age = _age;
    salary = _salary;
}

/**
 * @return An easy to understand string representation of a Person.
 */
string Person::toString() const {
    string indentSalary = "";
    string indentAge = "";

    double _salary = salary < 0.00001 ? 1.0 : salary;
    int order = CENTER_SALARY_DECIMAL_POINT_POWER;
    while (order-- > 0 && _salary < pow(10, CENTER_SALARY_DECIMAL_POINT_POWER)) {
        _salary *= 10.0;
        indentSalary += " ";
    }

    double _age = age <= 0 ? 1 : age;
    while (_age < 100) {
        _age *= 10.0;
        indentAge += " ";
    }

    return "| " + Util::extendToLength(name.firstname + " " + name.lastname, MAX_FULL_NAME_LENGTH)
            + " | age: " + indentAge + to_string(age)
            + " | salary: " + indentSalary + to_string(salary) + " |";
}

/**
 * @return A string that can be used to set a person's attributes later.
 * It is a compact string representation of a person.
 */
string Person::serializeToString() const {
    return name.serializeToString() + SERIALIZATION_SEPARATOR
            + to_string(age) + SERIALIZATION_SEPARATOR
            + to_string(salary);
}

/**
 * Sets the person's attributes according to the given string.
 * The string has to be in the following format:
 * "firstname,lastname,age,salary"
 * 
 * usage: person.deserializeFromString("John,Smith,42,2899.99");
 * 
 * @param s - The string used to set the person's attributes.
 * 
 * @throw DeserializationException - When the string cannot be used to set the 
 * person's attributes because of a wrong format.
 */
void Person::deserializeFromString(string const &s) {
    vector<string> v = Util::split(s, SERIALIZATION_SEPARATOR);

    if (NUMBER_OF_ATTRIBUTES_PERSON != v.size()) {
        throw DeserializationException("To many attributes given in the string! " + to_string(v.size()) + " given but " + to_string(NUMBER_OF_ATTRIBUTES_PERSON) + " required: \"" + s + "\"");
    }

    string _firstname = v[0], _lastname = v[1], _age = v[2], _salary = v[3];

    try {
        stoi(_age);
    } catch (exception const &e) {
        throw DeserializationException("Cannot parse age to int: " + _age);
    }

    try {
        stod(_salary);
    } catch (exception const &e) {
        throw DeserializationException("Cannot parse salary to double: " + _salary);
    }

    name = Name(_firstname, _lastname); // At this pint, it is easier to create a new Name from the first- and lastname than deserializing the name explicitly.
    age = stoi(_age);
    salary = stod(_salary);
}

bool Person::operator!=(Person const &other) {
    return name != other.name || age != other.age || salary != other.salary;
}

bool Person::operator==(Person const &other) {
    return name == other.name && age == other.age && salary == other.salary;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Comparators for Person                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////////////

const Person::Comparator Person::Sort::Ascending::BY_LASTNAME_THEN_FIRSTNAME = [](Person const &p1, Person const &p2) {
    return (p1.name.lastname + p1.name.firstname).compare(p2.name.lastname + p2.name.firstname) < 0;
};

const Person::Comparator Person::Sort::Descending::BY_LASTNAME_THEN_FIRSTNAME = [](Person const &p1, Person const &p2) {
    return (p1.name.lastname + p1.name.firstname).compare(p2.name.lastname + p2.name.firstname) > 0;
};

const Person::Comparator Person::Sort::Ascending::BY_FIRSTNAME_THEN_LASTNAME = [](Person const &p1, Person const &p2) {
    return (p1.name.firstname + p1.name.lastname).compare(p2.name.firstname + p2.name.lastname) < 0;
};

const Person::Comparator Person::Sort::Descending::BY_FIRSTNAME_THEN_LASTNAME = [](Person const &p1, Person const &p2) {
    return (p1.name.firstname + p1.name.lastname).compare(p2.name.firstname + p2.name.lastname) > 0;
};

const Person::Comparator Person::Sort::Ascending::BY_FIRSTNAME = [](Person const &p1, Person const &p2) {
    return p1.name.firstname.compare(p2.name.firstname) < 0;
};

const Person::Comparator Person::Sort::Descending::BY_FIRSTNAME = [](Person const &p1, Person const &p2) {
    return p1.name.firstname.compare(p2.name.firstname) > 0;
};

const Person::Comparator Person::Sort::Ascending::BY_LASTNAME = [](Person const &p1, Person const &p2) {
    return p1.name.lastname.compare(p2.name.lastname) < 0;
};

const Person::Comparator Person::Sort::Descending::BY_LASTNAME = [](Person const &p1, Person const &p2) {
    return p1.name.lastname.compare(p2.name.lastname) > 0;
};

const Person::Comparator Person::Sort::Ascending::BY_AGE = [](Person const &p1, Person const &p2) {
    return p1.age < p2.age;
};

const Person::Comparator Person::Sort::Descending::BY_AGE = [](Person const &p1, Person const &p2) {
    return p1.age > p2.age;
};

const Person::Comparator Person::Sort::Ascending::BY_SALARY = [](Person const &p1, Person const &p2) {
    return p1.salary < p2.salary;
};

const Person::Comparator Person::Sort::Descending::BY_SALARY = [](Person const &p1, Person const &p2) {
    return p1.salary > p2.salary;
};
