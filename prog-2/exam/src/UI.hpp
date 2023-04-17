#pragma once

#include <string>
#include "Configuration.h"
#include "Person.h"
#include "Util.hpp"

namespace UI {

    /**
     * Ask the user to input a number between min and max (including).
     * It will try until the input is valid.
     * 
     * @param min - The maximum number.
     * @param max - The minimum number.
     * @return The valid input as an integer.
     */
    int getIntFromConsole(int const min, int const max) {
        std::string input = "";
        int option;

        do {
            std::cout << "| -> Choose a number between " + std::to_string(min) + " and " + std::to_string(max) + ": ";
            std::cin >> input;
        } while (!Util::tryParseInt(input, option, min, max));

        return option;
    }

    /**
     * Prints the welcome message to the console.
     */
    void printWelcome() {
        std::cout << "|-----------------------------------------------------------------------|" << std::endl;
        std::cout << "| Welcome to the Person-Sorting-Machine                                 |" << std::endl;
        std::cout << "|                                                                       |" << std::endl;
        std::cout << "| There is the file " + Util::extendToLength(std::string(DATASET_FILE) + " which contains a dataset of persons.", 51) + " |" << std::endl;
        std::cout << "| Each line represents a person with the following traits:              |" << std::endl;
        std::cout << "| name,age,salary                                                       |" << std::endl;
        std::cout << "| The name itself is subdivided in firstname,lastname                   |" << std::endl;
        std::cout << "|                                                                       |" << std::endl;
        std::cout << "| You can generate a new dataset of persons and decide how to sort it.  |" << std::endl;
        std::cout << "| The data will be simultaneously managed in these containers:          |" << std::endl;
        std::cout << "| std::vector, std::deque, std::array and in my own implemented ones:   |" << std::endl;
        std::cout << "| my own Array and may own CircularBuffer                               |" << std::endl;
        std::cout << "|                                                                       |" << std::endl;
        std::cout << "| I implemented the sorting algorithm QuickSort on my own.              |" << std::endl;
        std::cout << "| This single implementation can handle all of the containers above.    |" << std::endl;
        std::cout << "|                                                                       |" << std::endl;
        std::cout << "| NOTE: A dataset-size of other than 20 will cause some suboptimal      |" << std::endl;
        std::cout << "| behavior for std::array. That is because the std::array cannot be     |" << std::endl;
        std::cout << "| initialized with a non-literal size. You can change this number in    |" << std::endl;
        std::cout << "| Configuration.h                                                       |" << std::endl;
        std::cout << "|         1. If the number is smaller than the actual size of the       |" << std::endl;
        std::cout << "|            dataset, the std::array will only store so much.           |" << std::endl;
        std::cout << "|         2. If the number is larger than the actual size of the        |" << std::endl;
        std::cout << "|            dataset, the rest of the std::array will be filled with    |" << std::endl;
        std::cout << "|            empty persons.                                             |" << std::endl;
        std::cout << "|         So don't wonder if the output for the std::array doesn't look |" << std::endl;
        std::cout << "|         perfect. This is because of the limitations of the std::array |" << std::endl;
        std::cout << "|         in the STL.                                                   |" << std::endl;
        std::cout << "| Nevertheless, have fun playing around :)                              |" << std::endl;
        std::cout << "|-----------------------------------------------------------------------|" << std::endl;
    }

    /**
     * Ask the user whether they want to generate a new dataset.
     * 
     * @param summary - The summary that is completed. (MODIFIED)
     * @return Whether the user wanted to generate a new dataset.
     */
    bool askRegenerate(std::string &summary) {
        std::cout << "| Do you want to...                                                     |" << std::endl;
        std::cout << "|        ~> 0: generate a new dataset of persons                        |" << std::endl;
        std::cout << "|        ~> 1: use the existing dataset in " + Util::extendToLength(std::string(DATASET_FILE), 28) + " |" << std::endl;
        int chosen = getIntFromConsole(0, 1);
        bool regenerate;

        switch (chosen) {
            case 0:
                regenerate = true;
                summary += "| You wanted to generate a new dataset";
                break;
            case 1:
                summary += "| You didn't want to generate a new dataset.                            |\n";
                regenerate = false;
                break;
            default:
                summary += "| You didn't want to generate a new dataset.                            |\n";
                regenerate = false;
                break;
        }

        return regenerate;
    }

    /**
     * Ask the user which size they want the new dataset to be.
     * 
     * @param summary - The summary that is completed. (MODIFIED)
     * @return The size the user wants the dataset to be.
     */
    int askDatasetSize(std::string &summary) {
        int datasetSize;

        std::cout << "|-----------------------------------------------------------------------|" << std::endl;
        std::cout << "| You can choose the new size of the dataset between 1 and 100.         |" << std::endl;
        datasetSize = getIntFromConsole(1, 100);
        summary += " of size " + Util::extendToLength(std::to_string(datasetSize) + ".", 25) + "|\n";

        return datasetSize;
    }

    /**
     * Ask the user how they want the dataset to be sorted.
     * 
     * @param summary - The summary that is completed. (MODIFIED)
     * @return The comparator which determines the sorting order.
     */
    Person::Comparator askComparator(std::string &summary) {
        std::cout << "|-----------------------------------------------------------------------|" << std::endl;
        std::cout << "| How do you want the data to be sorted?                                |" << std::endl;
        std::cout << "|   ascending                                                           |" << std::endl;
        std::cout << "|        ~> 0:  by firstname and then by lastname                       |" << std::endl;
        std::cout << "|        ~> 1:  by lastname and then by firstname                       |" << std::endl;
        std::cout << "|        ~> 2:  by firstname                                            |" << std::endl;
        std::cout << "|        ~> 3:  by lastname                                             |" << std::endl;
        std::cout << "|        ~> 4:  by salary                                               |" << std::endl;
        std::cout << "|        ~> 5:  by age                                                  |" << std::endl;
        std::cout << "|   descending                                                          |" << std::endl;
        std::cout << "|        ~> 6:  by firstname and then by lastname                       |" << std::endl;
        std::cout << "|        ~> 7:  by lastname and then by firstname                       |" << std::endl;
        std::cout << "|        ~> 8:  by firstname                                            |" << std::endl;
        std::cout << "|        ~> 9:  by lastname                                             |" << std::endl;
        std::cout << "|        ~> 10: by salary                                               |" << std::endl;
        std::cout << "|        ~> 11: by age                                                  |" << std::endl;

        int whichComparator = getIntFromConsole(0, 11);
        std::cout << "|-----------------------------------------------------------------------|" << std::endl;

        switch (whichComparator) {
            case 0:
                summary += "| The data will be sorted ascending by firstname and then by lastname.  |";
                return Person::Sort::Ascending::BY_FIRSTNAME_THEN_LASTNAME;
            case 1:
                summary += "| The data will be sorted ascending by lastname and then by firstname.  |";
                return Person::Sort::Ascending::BY_LASTNAME_THEN_FIRSTNAME;
            case 2:
                summary += "| The data will be sorted ascending by firstname.                       |";
                return Person::Sort::Ascending::BY_FIRSTNAME;
            case 3:
                summary += "| The data will be sorted ascending by lastname.                        |";
                return Person::Sort::Ascending::BY_LASTNAME;
            case 4:
                summary += "| The data will be sorted ascending by salary.                          |";
                return Person::Sort::Ascending::BY_SALARY;
            case 5:
                summary += "| The data will be sorted ascending by age.                             |";
                return Person::Sort::Ascending::BY_AGE;
            case 6:
                summary += "| The data will be sorted descending by firstname and then by lastname. |";
                return Person::Sort::Descending::BY_FIRSTNAME_THEN_LASTNAME;
            case 7:
                summary += "| The data will be sorted descending by lastname and then by firstname. |";
                return Person::Sort::Descending::BY_LASTNAME_THEN_FIRSTNAME;
            case 8:
                summary += "| The data will be sorted descending by firstname.                      |";
                return Person::Sort::Descending::BY_FIRSTNAME;
            case 9:
                summary += "| The data will be sorted descending by lastname.                       |";
                return Person::Sort::Descending::BY_LASTNAME;
            case 10:
                summary += "| The data will be sorted descending by salary.                         |";
                return Person::Sort::Descending::BY_SALARY;
            case 11:
                summary += "| The data will be sorted descending by age.                            |";
                return Person::Sort::Descending::BY_AGE;
            default:
                summary += "| Your desired order couldn't be received, option 0 is used as default. |\n";
                summary += "| The data will be sorted ascending by firstname and then by lastname.  |";
                return Person::Sort::Ascending::BY_FIRSTNAME_THEN_LASTNAME;
        }
    }

    /**
     * Starts a dialogue with the user to ask for some configurable parameters.
     * 
     * @param regenerate - Whether the user wants to generate a new dataset. (MODIFIED)
     * @param datasetSize - The size of the new dataset, if the user has chosen to generate a new one. (MODIFIED)
     * @param comparator - Determines the sorting order. (MODIFIED)
     * @param file - The dataset file.
     */
    void userConfigPrompt(bool &regenerate, int &datasetSize, Person::Comparator &comparator, std::string const &file) {
        std::string summary = "";

        printWelcome();

        regenerate = askRegenerate(summary);

        if (regenerate) {
            datasetSize = askDatasetSize(summary);
        }

        comparator = askComparator(summary);

        std::cout << summary << std::endl;
        std::cout << "|-----------------------------------------------------------------------|" << std::endl;
    }

}
