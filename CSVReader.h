#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    private:
        static std::vector<std::string> tokenise(std::string csvLine, char seperator);
        static OrderBookEntry stringsToOrderBookEntry(std::vector<std::string> strings);

};

