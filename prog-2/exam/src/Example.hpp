#pragma once

#include "Configuration.h"
#include "Algorithm.hpp"
#include "Dataset.h"
#include "Util.hpp"

#include <deque>
#include "Array.hpp"
#include "CircularBuffer.hpp"

namespace Example {

    /**
     * Managing the given dataset in a std::vector and sorting it with quick sort 
     * in the order determined by the given comparator.
     * Then print the sorted std::vector to the console.
     * 
     * @param dataset - The dataset the std::vector should manage.
     * @param comparator - The comparator to determine the sorting order.
     */
    void stdVectorExample(Dataset dataset, Person::Comparator comparator) {
        std::vector<Person> container(dataset);

        Algorithm::quickSort(container.begin(), container.end(), comparator);

        Util::printPersonContainer(container, "sorted in std::vector");
    }

    /**
     * Managing the given dataset in a std::deque and sorting it with quick sort 
     * in the order determined by the given comparator.     
     * Then print the sorted std::deque to the console.
     * 
     * @param dataset - The dataset the std::deque should manage.
     * @param comparator - The comparator to determine the sorting order.
     */
    void stdDequeExample(Dataset dataset, Person::Comparator comparator) {
        std::deque<Person> container(dataset.begin(), dataset.end());

        Algorithm::quickSort(container.begin(), container.end(), comparator);

        Util::printPersonContainer(container, "sorted in std::deque");
    }

    /**
     * Managing the given dataset in a std::array and sorting it with quick sort 
     * in the order determined by the given comparator.
     * Then print the sorted std::array to the console.
     * 
     * @param dataset - The dataset the std::array should manage.
     * @param comparator - The comparator to determine the sorting order.
     * @Note The size of the std::array cannot be set by the dataset. Instead it is set in Configuration.h
     */
    void stdArrayExample(Dataset dataset, Person::Comparator comparator) {
        std::array<Person, STD_ARRAY_SIZE> container;

        for (int i = 0; i < container.size() && i < dataset.size(); ++i) {
            container[i] = dataset[i];
        }

        Algorithm::quickSort(container.begin(), container.end(), comparator);

        Util::printPersonContainer(container, "sorted in std::array");
    }

    /**
     * Managing the given dataset in my own array and sorting it with quick sort 
     * in the order determined by the given comparator.
     * Then print the sorted array to the console.
     * 
     * @param dataset - The dataset the own array should manage.
     * @param comparator - The comparator to determine the sorting order.
     */
    void ownArrayExample(Dataset dataset, Person::Comparator comparator) {
        Array<Person> container(dataset.size());
        container.fillWith(dataset);

        Algorithm::quickSort(container.begin(), container.end(), comparator);

        Util::printPersonContainer(container, "sorted in own array");
    }

    /**
     * Managing the given dataset in my own circular buffer and sorting it with quick sort 
     * in the order determined by the given comparator.
     * Then print the sorted circular buffer to the console.
     * 
     * @param dataset - The dataset the own circular buffer should manage.
     * @param comparator - The comparator to determine the sorting order.
     */
    void ownCircularBufferExample(Dataset dataset, Person::Comparator comparator) {
        CircularBuffer<Person> container(dataset.size());
        container.fillWith(dataset);

        Algorithm::quickSort(container.begin(), container.end(), comparator);

        Util::printPersonContainer(container, "sorted in own circular buffer");
    }

}
