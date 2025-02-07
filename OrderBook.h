#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** Construct, reading a csv data file */
        OrderBook(std::string filename);
        /** return vector of all known products in the data set */
        std::vector<std::string> getKnownProducts();
        /** return vector of orders according to the sent filters */
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

        /** returns the earliest time in the orderbook */
        std::string getEarliestTime();
        /** returns the next time after the sent time in the orderbook
         * If there is no next timestamp, wraps around to the start
         */
        std::string getNextTime(std::string timestamp);
        std::string getPreviousTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        void displayPriceChange(OrderBook& orderbook, const std::string& currentTimestanp, const std::string& previousTimestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

    private:
        std::vector<OrderBookEntry> orders;
};