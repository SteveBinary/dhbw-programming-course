#pragma once

#include <vector>
#include <string>
#include <random>
#include <iostream>

const std::string SEPARATOR_DASHES = "|----------------------------------------------------|";

namespace Util {

    /**
     * Separates a given string into smaller strings that are separated by the separator.
     * 
     * @param s - The string that should be separated.
     * @param separator - The separator of the elements in the string s.
     * @return A vector of strings.
     */
    inline std::vector<std::string> split(std::string const &s, char const separator) {
        std::vector<std::string> v;
        std::string element = "";

        for (char c : s) {
            if (c == separator) {
                v.push_back(element);
                element = "";
            } else {
                element += c;
            }
        }

        v.push_back(element);

        return v;
    }

    /**
     * Generates a random integer. The range is:\n
     * from(inclusively) - to(exclusively)
     * 
     * @param to - Maximum of the generated random number - exclusively.
     * @param from - Minimum of the generated random number
     * (default is 0) - inclusively.
     * @return A random integer.
     */
    template<typename T>
    int getRandomNumber(T to, T from = 0) {
        std::random_device device;
        std::mt19937 engine(device());
        
        std::uniform_int_distribution<T> distribution(from, to - 1);

        return distribution(engine);
    }

    /**
     * Selects a random element of a vector and returns it.
     * 
     * @param v - The vector to select the element from.
     * @return A random element of the vector.
     */
    template<typename T>
    T getRandomElement(std::vector<T> const &v) {
        return v[getRandomNumber(v.size())];
    }

    /**
     * Adds white spaces to the given string until the target length is reached.
     * If the target length is smaller than the initial length of s, the result is the same as s.
     * The number of added white spaces is targetLength - initial length of s.
     * 
     * @param s - The string to extend with white spaces. (UN-MODIFIED)
     * @param targetLength - The length the string should have after adding the white spaces.
     * @return The extended string.
     * 
     * @caution The length of the string is the number of bytes!
     * Characters like 'ö' could lead to unexpected results!
     */
    inline std::string extendToLength(std::string const &s, unsigned int const targetLength) {
        std::string result(s);

        while (result.length() < targetLength) {
            result += " ";
        }

        return result;
    }

    /**
     * Prints the content of a container of persons to the console.
     * The type of the content must be Person or at least implement the member function toString().
     * 
     * @param container - The container to print.
     * @param info - Some more information about the container, like the name.
     */
    template<typename T>
    void printPersonContainer(T &container, std::string const &info) {
        std::string dashes = "";

        while (dashes.length() + info.length() < SEPARATOR_DASHES.length() - 8) {
            dashes += "-";
        }

        dashes += "|";

        std::cout << "| # " + info + " # " + dashes << std::endl;
        for (auto const &p : container) {
            std::cout << p.toString() << std::endl;
        }
        std::cout << SEPARATOR_DASHES << std::endl;
    }

    /**
     * Try to convert the string input to an integer. If the conversion 
     * is possible AND the resulting integer is between min and max (including)
     * the integer is stored in output and true is retured, otherwise false.
     * 
     * @param input - The string to convert to an integer.
     * @param output - The variable that is set if the conditions above are fulfilled.
     * @param min - The minimum value the integer can have to be accepted.
     * @param max - The maximum value the integer can have to be accepted.
     * @return Whether the conditions mentioned above are fulfillled.
     */
    inline bool tryParseInt(std::string const &input, int &output, int const min, int const max) {
        int temp;

        try {
            temp = std::stoi(input);
        } catch (std::exception const &e) {
            return false;
        }

        bool validInterval = temp >= min && temp <= max;

        if (validInterval) {
            output = std::stoi(input);
        }

        return validInterval;
    }

}
