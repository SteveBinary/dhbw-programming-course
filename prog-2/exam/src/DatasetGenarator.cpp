#include <iostream>
#include <vector>
#include "Util.hpp"
#include "Serializer.hpp"
#include "Dataset.h"
#include "DatasetGenerator.h"

using namespace std;

// the 20 most popular forenames in Germany 2020
const vector<string> DatasetGenarator::FIRSTNAMES = {
    "Mia", "Emilia", "Hannah", "Emma", "Sophia", "Lina", "Ella", "Mila", "Clara", "Lea",
    "Noah", "Ben", "Matteo", "Finn", "Leon", "Elias", "Paul", "Henry", "Luis", "Felix"
};
// the 20 most common surnames in Germanny
const vector<string> DatasetGenarator::LASTNAMES = {
    "Mueller", "Schmidt", "Schneider", "Fischer", "Weber", "Meyer", "Wagner", "Becker", "Schulz", "Hoffmann",
    "Schaefer", "Koch", "Bauer", "Richter", "Klein", "Wolf", "Schroeder", "Neumann", "Schwarz", "Zimmermann"
};

/**
 * Constructor
 */
DatasetGenarator::DatasetGenarator(std::string _file) {
    file = _file;
}

/**
 * @return The internal dataset of persons.
 */
Dataset DatasetGenarator::getDataset() const {
    return dataset;
}

/**
 * Generates a dataset of persons of the given size.
 * 
 * @param size - The size of the dataset to be generated.
 */
void DatasetGenarator::generateDataset(const unsigned int size) {
    Dataset result(size);

    for (int i = 0; i < size; ++i) {
        string firstname = Util::getRandomElement(FIRSTNAMES);
        string lastname = Util::getRandomElement(LASTNAMES);
        int age = Util::getRandomNumber(MAX_AGE + 1, MIN_AGE);
        double salary = ((double) Util::getRandomNumber(MAX_SALARY * 100, MIN_SALARY * 100)) / 100.0;

        Person p(firstname, lastname, age, salary);
        result[i] = p;
    }

    dataset = result;
}

/**
 * Serializes the internal dataset of persons in the file specified in the constructor.
 */
void DatasetGenarator::serializeDataset() {
    Serializer<Person> serializer(file);
    P_Dataset p_dataset(dataset.size(), nullptr);

    for (int i = 0; i < dataset.size(); ++i) {
        p_dataset[i] = &(dataset[i]);
    }

    try {
        serializer.serialize(p_dataset);
    } catch (SerializationException const &e) {
        cout << "Could not serialize the dataset!\n\t" + string(e.what()) << endl;
    }
}

/**
 * Deserializes the dataset of persons from the file specified in the constructor into the internal dataset.
 */
void DatasetGenarator::deserializeDataset() {
    Serializer<Person> serializer(file);

    try {
        dataset = serializer.deserialize();
    } catch (DeserializationException const &e) {
        cout << "Could not deserialize the dataset!\n\t" + string(e.what()) << endl;
    }
}
