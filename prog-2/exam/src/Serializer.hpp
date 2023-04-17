#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Serializable.h"
#include "Exceptions.hpp"

using namespace std;

// used to check if a type parameter extends a given base class --------------------------------------
// https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class

template<typename Base, typename PotentialDerived>
struct isBase {
    typedef char (&no) [1];
    typedef char (&yes) [2];

    static yes check(Base*);
    static no check(...);

    enum {
        value = sizeof (check(static_cast<PotentialDerived*> (0))) == sizeof (yes)
    };
};

// ---------------------------------------------------------------------------------------------------

template<class T>
class Serializer {
    std::string filename;
public:

    /**
     * Constructor
     * 
     * @throws IncorrectTypeParameterException - When the type parameter doesn't extend Serializable.
     * Normally this exception can be ignored because being aware of it means that the caller should 
     * know what type parameter to hand over.
     * 
     * @caution
     * The IncorrectTypeParameterException should not be catched! If it is thrown, the application will 
     * crash anyway or show unexpected behavior because of the incompatible types.
     * But now the cause of the crash is known.
     */
    Serializer(std::string const _filename) {
        if (!isBase<Serializable, T>::value) {
            throw IncorrectTypeParameterException("The Serializer cannot serialize the given type. The type must extend 'Serializable'");
        }

        filename = _filename;
    }

    /**
     * Writes serializable objects to a file according to their serializeToString() implementation.
     * 
     * @param serializables - A vector of pointers to objects that extend Serializable.
     */
    void serialize(vector<T*> const serializables) const {
        ofstream file;
        file.open(filename);

        if (!file.is_open() || !file.good()) {
            file.close();
            throw SerializationException("Something went wrong opening the file \"" + filename + "\"");
        }

        for (T* t : serializables) {
            // The case that t doesn't extend Serializable und thus doesn't have the member function 
            // serializeToString() is handled already in the constructor.
            // So it is impossible to get a runtime exception here because of this.
            // In other cases the code might not even compile.
            // So it is save to ignore the warning.
            file << t->serializeToString() << endl;
        }

        file.close();
    }

    /**
     * Reads a file and creates objects according to the type parameter.
     * The given type must extend Serializable.
     * Each line in the input file correspondes to one dataset which is used for object-initialization.
     * Each line has to have the correct format for deserialization.
     * The format is given by the type parameter.
     * The created objects are collected into a vector.
     * 
     * @return The vector of all succesfully created objects.
     */
    vector<T> deserialize() const {
        ifstream file;
        file.open(filename);

        if (!file.is_open() || !file.good()) {
            file.close();
            throw DeserializationException("Something went wrong opening the file \"" + filename + "\"");
        }

        string line;
        int lineNumber = 0;
        vector<T> result;

        while (getline(file, line)) {
            ++lineNumber;

            try {
                T t;

                // The case that t doesn't extend Serializable und thus doesn't have the member function 
                // initializeFromString(std::string) is handled already in the constructor.
                // So it is impossible to get a runtime exception here because of this.
                // In other cases the code might not even compile.
                // So it is save to ignore the warning.
                t.deserializeFromString(line);

                result.push_back(t);
            } catch (DeserializationException const &e) {
                cout << "Could not deserialize the following dataset on line " + to_string(lineNumber) + ": " + line + "\n\t" + string(e.what()) << endl;
            }
        }

        file.close();

        return result;
    }
};
