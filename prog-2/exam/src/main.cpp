/* 
 * Author: SteveBinary
 */

#include <iostream>
#include "Configuration.h"
#include "DatasetGenerator.h"
#include "DemoUtil.hpp"
#include "Example.hpp"
#include "Util.hpp"
#include "UI.hpp"

int main() {
    bool regenerate;
    int datasetSize;
    Person::Comparator comparator;
    UI::userConfigPrompt(regenerate, datasetSize, comparator, DATASET_FILE);

    Dataset persons = DemoUtil::getDatasetAndSerializeIfRegenerate(regenerate, datasetSize);

    if (persons.empty()) {
        std::cout << "Der Datensatz ist leer oder konnte nicht gefunden werden!" << std::endl;
        return (EXIT_FAILURE);
    }
    
    Util::printPersonContainer(persons, "raw data");

    Example::stdVectorExample(persons, comparator);
    Example::stdDequeExample(persons, comparator);
    Example::stdArrayExample(persons, comparator);
    Example::ownArrayExample(persons, comparator);
    Example::ownCircularBufferExample(persons, comparator);

    std::cin.get(); // wait for user input so the console wont close
    std::cin.get();

    return (EXIT_SUCCESS);
}
