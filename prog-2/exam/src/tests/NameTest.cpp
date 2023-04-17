#include <stdlib.h>
#include <iostream>
#include "Name.h"

using namespace std;

void testSerializeToString() {
    Name name1;
    Name name2("John", "Smith");

    bool result1 = name1.serializeToString() == ",";
    bool result2 = name2.serializeToString() == "John,Smith";

    if (!result1 || !result2) {
        cout << "%TEST_FAILED% time=0 testname=testSerializeToString (NameTest) message=" << endl;
    }
}

void testInitializeFromString() {
    Name name1;
    Name name2("John", "Smith");
    
    name1.deserializeFromString("Harry,Potter");
    name2.deserializeFromString("Lord,Voldemort");

    bool result1 = name1.firstname == "Harry" && name1.lastname == "Potter";
    bool result2 = name2.firstname == "Lord" && name2.lastname == "Voldemort";

    if (!result1 || !result2) {
        cout << "%TEST_FAILED% time=0 testname=testInitializeFromString (NameTest) message=" << endl;
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% NameTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testSerializeToString (NameTest)" << endl;
    testSerializeToString();
    cout << "%TEST_FINISHED% time=0 testSerializeToString (NameTest)" << endl;

    cout << "%TEST_STARTED% testInitializeFromString (NameTest)" << endl;
    testInitializeFromString();
    cout << "%TEST_FINISHED% time=0 testInitializeFromString (NameTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
