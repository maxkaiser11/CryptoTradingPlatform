#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvFilename);

    private:
        static std::vector<std::string> tokenise(std::string csvLine, char seperator);
        static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);

};

