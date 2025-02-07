#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvFilename);
        static std::vector<std::string> tokenise(std::string csvLine, char seperator);

        static OrderBookEntry stringsToOBE(std::string price, 
                                           std::string amount, 
                                           std::string timestamp, 
                                           std::string product, 
                                           OrderBookType orderType);


    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};

