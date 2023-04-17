#pragma once

#include "Configuration.h"
#include "DatasetGenerator.h"

namespace DemoUtil {

    /**
     * Deserializing the dataset. If regenerate is true, a new dataset gets generated and serialized at first.
     * 
     * @param regenerate - Whether to generate a new dataset before deserializing.
     * @param size - The size of the newly generated dataset.
     * @return The deserialized dataset.
     */
    Dataset getDatasetAndSerializeIfRegenerate(bool regenerate, int size) {
        DatasetGenarator generator(DATASET_FILE);

        if (regenerate) {
            generator.generateDataset(size); // generate random persons
            generator.serializeDataset(); // write randomly generated Persons to a file
        }

        generator.deserializeDataset(); // read randomly generated Persons from the file

        return generator.getDataset(); // return the persons read from the file
    }

}
