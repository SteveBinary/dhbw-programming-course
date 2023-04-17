#pragma once

#include <string>
#include <exception>

// represents the base for the custom exceptions

class BaseException : public std::exception {
protected:
    std::string description;

    BaseException(std::string const _description) : description(_description) {
    }

public:

    const char * what() const throw () {
        return description.c_str();
    }
};

// -------------------------------------------------------------------------------------------------- //

class DeserializationException : public BaseException {
public:

    DeserializationException(std::string const _description = "") : BaseException(_description) {
    }
};

class SerializationException : public BaseException {
public:

    SerializationException(std::string const _description = "") : BaseException(_description) {
    }
};

class IncorrectTypeParameterException : public BaseException {
public:

    IncorrectTypeParameterException(std::string const _description = "") : BaseException(_description) {
    }
};

class IndexOutOfBoundsException : public BaseException {
public:

    IndexOutOfBoundsException(int const requestedIndex, int const maxIndex) : BaseException("Index out of bounds for: ") {
        description += std::to_string(requestedIndex) + ". Maximum index is: " + std::to_string(maxIndex) + ".";
    }
};

class InitializeException : public BaseException {
public:

    InitializeException(std::string const _description = "") : BaseException(_description) {
    }
};
