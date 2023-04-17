#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "DatasetGenerator.h"

#define TEST_FILE_DATASET_GENERATOR_SERIALIZE "test_dataset_generator_serialize.txt"
#define TEST_FILE_DATASET_GENERATOR_DESERIALIZE "test_dataset_generator_deserialize.txt"
#define TEST_DATASET_SIZE 100

using namespace std;

void testGetDataset() {
    DatasetGenarator datasetGenarator("");

    Dataset result = datasetGenarator.getDataset();

    if (result.size() != 0) {
        cout << "%TEST_FAILED% time=0 testname=testGetDataset (DatasetGeneratorTest) message=The default dataset should be of size 0" << endl;
    }
}

void testGenerateDataset() {
    DatasetGenarator datasetGenarator("");
    datasetGenarator.generateDataset(TEST_DATASET_SIZE);

    Dataset dataset = datasetGenarator.getDataset();

    if (dataset.size() != TEST_DATASET_SIZE) {
        cout << "%TEST_FAILED% time=0 testname=testGenerateDataset (DatasetGeneratorTest) message=The dataset has the wrong size!" << endl;
    }

    for (Person p : dataset) {
        if (p.name.firstname.length() == 0 || p.name.lastname.length() == 0) {
            cout << "%TEST_FAILED% time=0 testname=testGenerateDataset (DatasetGeneratorTest) message=The name is an empty string!" << endl;
        }
        if (p.age < MIN_AGE || p.age > MAX_AGE) {
            cout << "%TEST_FAILED% time=0 testname=testGenerateDataset (DatasetGeneratorTest) message=The age is not in the right range!" << endl;
        }

        if (p.salary < MIN_SALARY || p.salary > MAX_SALARY) {
            cout << "%TEST_FAILED% time=0 testname=testGenerateDataset (DatasetGeneratorTest) message=The salary is not in the right range!" << endl;
        }
    }
}

void testSerializeDataset() {
    DatasetGenarator datasetGenarator(TEST_FILE_DATASET_GENERATOR_SERIALIZE);
    datasetGenarator.generateDataset(TEST_DATASET_SIZE);
    Dataset dataset = datasetGenarator.getDataset();

    datasetGenarator.serializeDataset();

    ifstream file;
    file.open(TEST_FILE_DATASET_GENERATOR_SERIALIZE);

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        ++lineNumber;
        string expected = dataset[lineNumber - 1].serializeToString();

        if (expected != line) {
            cout << "%TEST_FAILED% time=0 testname=testSerializeDataset (DatasetGeneratorTest) message=[Line " +
                    to_string(lineNumber) + "] not serialized correctly! Expected: \"" + expected + "\" ### Actual: " + line << endl;
        }
    }

    file.close();

    if (lineNumber != TEST_DATASET_SIZE) {
        cout << "%TEST_FAILED% time=0 testname=testSerializeDataset (DatasetGeneratorTest) message=Serialized dataset size is " +
                to_string(lineNumber) + " but " + to_string(TEST_DATASET_SIZE) + " expected!" << endl;
    }
}

void testDeserializeDataset() {
    DatasetGenarator datasetGenarator(TEST_FILE_DATASET_GENERATOR_DESERIALIZE);

    datasetGenarator.deserializeDataset();
    Dataset dataset = datasetGenarator.getDataset();

    if (dataset.size() != 100) {
        cout << "%TEST_FAILED% time=0 testname=testDeserializeDataset (DatasetGeneratorTest) message=Deserialized dataset size is " +
                to_string(dataset.size()) + " but 100 expected!" << endl;
    }

    // just a few samples
    Person p1 = dataset[10]; // Emilia,Bauer,48,2758.500000
    Person p2 = dataset[63]; // Henry,Fischer,7,2909.730000
    Person p3 = dataset[94]; // Felix,Schwarz,99,3730.440000

    bool p1Correct = p1.name.firstname == "Emilia" && p1.name.lastname == "Bauer" && p1.age == 48 && p1.salary == 2758.5;
    bool p2Correct = p2.name.firstname == "Henry" && p2.name.lastname == "Fischer" && p2.age == 7 && p2.salary == 2909.73;
    bool p3Correct = p3.name.firstname == "Felix" && p3.name.lastname == "Schwarz" && p3.age == 99 && p3.salary == 3730.44;

    if (!p1Correct) {
        cout << "%TEST_FAILED% time=0 testname=testDeserializeDataset (DatasetGeneratorTest) message=p1 is deserialized incorrectly!" << endl;
    }

    if (!p2Correct) {
        cout << "%TEST_FAILED% time=0 testname=testDeserializeDataset (DatasetGeneratorTest) message=p2 is deserialized incorrectly!" << endl;
    }

    if (!p3Correct) {
        cout << "%TEST_FAILED% time=0 testname=testDeserializeDataset (DatasetGeneratorTest) message=p3 is deserialized incorrectly!" << endl;
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% DatasetGeneratorTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testGetDataset (DatasetGeneratorTest)" << endl;
    testGetDataset();
    cout << "%TEST_FINISHED% time=0 testGetDataset (DatasetGeneratorTest)" << endl;

    cout << "%TEST_STARTED% testGenerateDataset (DatasetGeneratorTest)" << endl;
    testGenerateDataset();
    cout << "%TEST_FINISHED% time=0 testGenerateDataset (DatasetGeneratorTest)" << endl;

    cout << "%TEST_STARTED% testSerializeDataset (DatasetGeneratorTest)" << endl;
    testSerializeDataset();
    cout << "%TEST_FINISHED% time=0 testSerializeDataset (DatasetGeneratorTest)" << endl;

    cout << "%TEST_STARTED% testDeserializeDataset (DatasetGeneratorTest)" << endl;
    testDeserializeDataset();
    cout << "%TEST_FINISHED% time=0 testDeserializeDataset (DatasetGeneratorTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
