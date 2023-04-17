#pragma once

#include <vector>
#include <string>
#include "Dataset.h"
#include "Configuration.h"

class DatasetGenarator {
    static const std::vector<std::string> FIRSTNAMES;
    static const std::vector<std::string> LASTNAMES;

    std::string file;
    Dataset dataset;

public:
    DatasetGenarator(std::string _file);

    void generateDataset(unsigned int const size);
    void serializeDataset();
    void deserializeDataset();
    Dataset getDataset() const;
};
