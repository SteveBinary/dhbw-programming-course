#include <stdlib.h>
#include <iostream>
#include "Person.h"

using namespace std;

void testToString() {
    Person person1;
    Person person2("John", "Smith", 42, 2899.99);

    bool result1 = person1.toString() == "|                   | age:   0 | salary:    0.000000 |";
    bool result2 = person2.toString() == "| John Smith        | age:  42 | salary: 2899.990000 |";

    if (!result1 || !result2) {
        cout << "%TEST_FAILED% time=0 testname=testToString (PersonTest) message=" << endl;
    }
}

void testSerializeToString() {
    Person person1;
    Person person2("John", "Smith", 42, 2899.99);

    bool result1 = person1.serializeToString() == ",,0,0.000000";
    bool result2 = person2.serializeToString() == "John,Smith,42,2899.990000";

    if (!result1 || !result2) {
        cout << "%TEST_FAILED% time=0 testname=testSerializeToString (PersonTest) message=" << endl;
    }
}

void testInitializeFromString() {
    Person person1;
    Person person2("John", "Smith", 42, 2899.99);

    person1.deserializeFromString("James,May,55,3566");
    person2.deserializeFromString("Jerremy,Clarkson,59,3699.99");

    bool result1 = person1.name.firstname == "James" && person1.name.lastname == "May" && person1.age == 55 && person1.salary == 3566;
    bool result2 = person2.name.firstname == "Jerremy" && person2.name.lastname == "Clarkson" && person2.age == 59 && person2.salary == 3699.99;

    if (!result1 || !result2) {
        cout << "%TEST_FAILED% time=0 testname=testInitializeFromString (PersonTest) message=" << endl;
    }
}

void comparatorTests() {
    Person p1("John", "Smith", 42, 2899.99);
    Person p2("Adam", "Harris", 32, 1999.99);

    using Ascending = Person::Sort::Ascending;

    if (Ascending::BY_FIRSTNAME_THEN_LASTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Ascending::BY_FIRSTNAME_THEN_LASTNAME" << endl;
    }

    if (Ascending::BY_LASTNAME_THEN_FIRSTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Ascending::BY_LASTNAME_THEN_FIRSTNAME" << endl;
    }

    if (Ascending::BY_FIRSTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Ascending::BY_FIRSTNAME" << endl;
    }

    if (Ascending::BY_LASTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Ascending::BY_LASTNAME" << endl;
    }

    if (Ascending::BY_AGE(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Ascending::BY_AGE" << endl;
    }

    if (Ascending::BY_SALARY(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Ascending::BY_SALARY" << endl;
    }

    //--------------------------------------------------------------------------------------------------------------------------------//

    using Descending = Person::Sort::Descending;

    if (!Descending::BY_FIRSTNAME_THEN_LASTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Descending::BY_FIRSTNAME_THEN_LASTNAME" << endl;
    }

    if (!Descending::BY_LASTNAME_THEN_FIRSTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Descending::BY_LASTNAME_THEN_FIRSTNAME" << endl;
    }

    if (!Descending::BY_FIRSTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Descending::BY_FIRSTNAME" << endl;
    }

    if (!Descending::BY_LASTNAME(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Descending::BY_LASTNAME" << endl;
    }
    if (!Descending::BY_AGE(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Descending::BY_AGE" << endl;
    }

    if (!Descending::BY_SALARY(p1, p2)) {
        cout << "%TEST_FAILED% time=0 testname=comparatorTests (PersonTest) message=Descending::BY_SALARY" << endl;
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% PersonTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testToString (PersonTest)" << endl;
    testToString();
    cout << "%TEST_FINISHED% time=0 testToString (PersonTest)" << endl;

    cout << "%TEST_STARTED% testSerializeToString (PersonTest)" << endl;
    testSerializeToString();
    cout << "%TEST_FINISHED% time=0 testSerializeToString (PersonTest)" << endl;

    cout << "%TEST_STARTED% testInitializeFromString (PersonTest)" << endl;
    testInitializeFromString();
    cout << "%TEST_FINISHED% time=0 testInitializeFromString (PersonTest)" << endl;

    cout << "%TEST_STARTED% comparatorTests (PersonTest)" << endl;
    comparatorTests();
    cout << "%TEST_FINISHED% time=0 comparatorTests (PersonTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
