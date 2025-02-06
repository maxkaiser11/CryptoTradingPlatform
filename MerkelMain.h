#pragma once

#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
    public:
        // Constructor
        MerkelMain();

        /* Call this to start the sim*/
        void init();

    private:
        void loadOrderBook();
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterOffer();
        void enterBid();
        void printWallet();
        void nextTimeFrame();
        int getUserOption();
        void processUserOption(int userOption);

        bool running = true;
        std::vector<OrderBookEntry> orders;
};