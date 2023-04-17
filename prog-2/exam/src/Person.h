#pragma once

#include <string>
#include <functional>
#include "Serializable.h"
#include "Name.h"

#define NUMBER_OF_ATTRIBUTES_PERSON (2 + NUMBER_OF_ATTRIBUTES_NAME)

class Person : public Serializable {
public:
    Name name;
    int age;
    double salary;

    Person();
    Person(std::string const _firstname, std::string const _lastname, int const _age, double const _salary);

    std::string toString() const;
    std::string serializeToString() const;
    void deserializeFromString(std::string const &s);

    bool operator!=(Person const &other);
    bool operator==(Person const &other);

    using Comparator = std::function< bool (Person const&, Person const&) >;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                        Comparators for Person                                        //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    class Sort {
    public:

        class Ascending {
        public:
            /**
             * Sort first by firstname and then by lastname.\n
             * direction: ascending
             */
            static const Comparator BY_FIRSTNAME_THEN_LASTNAME;

            /**
             * Sort first by lastname and then by firstname.\n
             * direction: ascending
             */
            static const Comparator BY_LASTNAME_THEN_FIRSTNAME;

            /**
             * Sort just by firstname.\n
             * direction: ascending
             */
            static const Comparator BY_FIRSTNAME;

            /**
             * Sort just by lastname.\n
             * direction: ascending
             */
            static const Comparator BY_LASTNAME;

            /**
             * Sort by age.\n
             * direction: ascending
             */
            static const Comparator BY_AGE;

            /**
             * Sort by salary.\n
             * direction: ascending
             */
            static const Comparator BY_SALARY;
        };

        class Descending {
        public:
            /**
             * Sort first by firstname and then by lastname.\n
             * direction: descending
             */
            static const Comparator BY_FIRSTNAME_THEN_LASTNAME;

            /**
             * Sort first by lastname and then by firstname.\n
             * direction: descending
             */
            static const Comparator BY_LASTNAME_THEN_FIRSTNAME;

            /**
             * Sort just by firstname.\n
             * direction: descending
             */
            static const Comparator BY_FIRSTNAME;

            /**
             * Sort just by lastname.\n
             * direction: descending
             */
            static const Comparator BY_LASTNAME;

            /**
             * Sort by age.\n
             * direction: descending
             */
            static const Comparator BY_AGE;

            /**
             * Sort by salary.\n
             * direction: descending
             */
            static const Comparator BY_SALARY;
        };
    };
};
