#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "Serializer.hpp"
#include "Person.h"
#include "Name.h"

#define TEST_FILE_SERIALIZE_PERSON "test_serialize_person.txt"
#define TEST_FILE_SERIALIZE_NAME "test_serialize_name.txt"
#define TEST_FILE_DESERIALIZE_PERSON "test_deserialize_person.txt"
#define TEST_FILE_DESERIALIZE_NAME "test_deserialize_name.txt"

using namespace std;

void testOnlySerializablesCanBeSerialized() {
    try {
        Serializer<vector<int>> a("a");
        cout << "%TEST_FAILED% time=0 testname=testOnlySerializablesCanBeSerialized (SerializerTest) message=The serializer shouldn't be instantiated!" << endl;
    } catch (IncorrectTypeParameterException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        Serializer<int> b("b");
        cout << "%TEST_FAILED% time=0 testname=testOnlySerializablesCanBeSerialized (SerializerTest) message=The serializer shouldn't be instantiated!" << endl;
    } catch (IncorrectTypeParameterException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        Serializer<Name> c("c");
    } catch (IncorrectTypeParameterException const &e) {
        cout << "%TEST_FAILED% time=0 testname=testOnlySerializablesCanBeSerialized (SerializerTest) message=The serializer should be instantiated!" << endl;
    }

    try {
        Serializer<Person> d("d");
    } catch (IncorrectTypeParameterException const &e) {
        cout << "%TEST_FAILED% time=0 testname=testOnlySerializablesCanBeSerialized (SerializerTest) message=The serializer should be instantiated!" << endl;
    }
}

void testSerialize() {
    Serializer<Person> personSerializer(TEST_FILE_SERIALIZE_PERSON);
    Serializer<Name> nameSerializer(TEST_FILE_SERIALIZE_NAME);

    Person p1, p2("Tony", "Stark", 40, 99999), p3("Captain", "America", 38, 8989.99);
    Name n1, n2("Tony", "Stark"), n3("Captain", "America");

    vector<Person*> vPerson{&p1, &p2, &p3};
    vector<Name*> vName{&n1, &n2, &n3};

    // provoke an excpetion while serializing is impossible
    try {
        personSerializer.serialize(vPerson);
    } catch (exception const &e) {
        cout << "%TEST_FAILED% time=0 testname=testSerialize (SerializerTest) message=Error while serializing persons: " + string(e.what()) << endl;
    }

    // provoke an excpetion while serializing is impossible
    try {
        nameSerializer.serialize(vName);
    } catch (exception const &e) {
        cout << "%TEST_FAILED% time=0 testname=testSerialize (SerializerTest) message=Error while serializing names: " + string(e.what()) << endl;
    }
}

void testDeserialize() {
    Serializer<Person> personSerializer(TEST_FILE_DESERIALIZE_PERSON);
    Serializer<Name> nameSerializer(TEST_FILE_DESERIALIZE_NAME);

    vector<Person> vPerson;
    vector<Name> vName;

    try {
        vPerson = personSerializer.deserialize();
    } catch (exception const &e) {
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=Error while deserializing persons: " + string(e.what()) << endl;
    }

    try {
        vName = nameSerializer.deserialize();
    } catch (exception const &e) {
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=Error while deserializing names: " + string(e.what()) << endl;
    }

    if (vPerson.size() != 3) {
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=Could not deserialize all 3 persons!" << endl;
    }

    if (vName.size() != 3) {
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=Could not deserialize all 3 names!" << endl;
    }

    bool person1Correct = vPerson[0].name.firstname == "" && vPerson[0].name.lastname == "" && vPerson[0].age == 0 && vPerson[0].salary == 0.0;
    bool person2Correct = vPerson[1].name.firstname == "Tony" && vPerson[1].name.lastname == "Stark" && vPerson[1].age == 40 && vPerson[1].salary == 99999;
    bool person3Correct = vPerson[2].name.firstname == "Captain" && vPerson[2].name.lastname == "America" && vPerson[2].age == 38 && vPerson[2].salary == 8989.99;

    bool name1Correct = vName[0].firstname == "" && vName[0].lastname == "";
    bool name2Correct = vName[1].firstname == "Tony" && vName[1].lastname == "Stark";
    bool name3Correct = vName[2].firstname == "Captain" && vName[2].lastname == "America";

    if (!person1Correct || !person2Correct || !person3Correct) {
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=Persons deserialized incorrectly!" << endl;
    }

    if (!name1Correct || !name2Correct || !name3Correct) {
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=Names deserialized incorrectly!" << endl;
    }

    //
    // from here there will be exceptions provoked
    //

    Serializer<Person> failingPersonSerializer("dbhedsnhsdeh");
    Serializer<Name> failingNameSerializer("sfgdefghds");

    try {
        failingPersonSerializer.deserialize();
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=This serializer should fail to deserialize Persons!" << endl;
    } catch (DeserializationException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        failingNameSerializer.deserialize();
        cout << "%TEST_FAILED% time=0 testname=testDeserialize (SerializerTest) message=This serializer should fail to deserialize Names!" << endl;
    } catch (DeserializationException const &e) {
        // everything is OK, the exception should be thrown
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% SerializerTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testOnlySerializablesCanBeSerialized (SerializerTest)" << endl;
    testOnlySerializablesCanBeSerialized();
    cout << "%TEST_FINISHED% time=0 testOnlySerializablesCanBeSerialized (SerializerTest)" << endl;

    cout << "%TEST_STARTED% testSerialize (SerializerTest)" << endl;
    testSerialize();
    cout << "%TEST_FINISHED% time=0 testSerialize (SerializerTest)" << endl;

    cout << "%TEST_STARTED% testDeserialize (SerializerTest)" << endl;
    testDeserialize();
    cout << "%TEST_FINISHED% time=0 testDeserialize (SerializerTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
