#include "OrderBook.h"
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
        prodMap[e.product] = true;

    // now flatten the map to a vector of strings
    for (auto const& e : prodMap)
        products.push_back(e.first);

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

std::string OrderBook::getPreviousTime(std::string timestamp)
{
    std::string previous_timestamp = "";
    for (int i = orders.size() - 1; i >= 0; --i)
    {
        if (orders[i].timestamp < timestamp)
        {
            previous_timestamp = orders[i].timestamp;
            break;
        }
    }
    if (previous_timestamp == "")
    {
        previous_timestamp = orders.back().timestamp;
    }
    return previous_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    // asks = orderbook.asks in this timeframe
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    // bids = orderbook.bids in this timeframe
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

    // sales = []
    std::vector<OrderBookEntry> sales;
    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDsc);

    // for ask in asks:
    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry& bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};
                if (bid.amount == ask.amount)
                {
                    sale.amount == ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if (bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    // return sales
    return sales;
}

/** this function takes the orderbook, the currenttimestamp and the previoustimestamp and compares the prices and returns the price change in % */
void OrderBook::displayPriceChange(OrderBook &orderbook, const std::string &currentTimestamp, const std::string &previousTimestamp)
{
    std::vector<std::string> products = orderbook.getKnownProducts();

    for (const std::string& product : products)
    {
        std::vector<OrderBookEntry> currentOrders = orderbook.getOrders(OrderBookType::ask, product, currentTimestamp);
        std::vector<OrderBookEntry> previousOrders = orderbook.getOrders(OrderBookType::ask, product, previousTimestamp);

        if (currentOrders.empty() || previousOrders.empty())
        {
            std::cout << "No data for product: " << product << std::endl;
            continue;
        }

        // Get the representative price (e.g., high price) for each timeframe
        double currentPrice = OrderBook::getHighPrice(currentOrders);
        double previousPrice = OrderBook::getHighPrice(previousOrders);

         // Check if the previous price is valid to avoid division by zero
        if (previousPrice == 0.0)
        {
            std::cout << "Invalid previous price for product: " << product << std::endl;
            continue;
        }

        // Calculate percentage price change
        double priceChange = currentPrice - previousPrice;
        double percentageChange = (priceChange / previousPrice) * 100.0;
        // Round to 2 decimal places
        percentageChange = std::round(percentageChange * 100.0) / 100.0;

        std::cout << "Product: " << product << std::endl;
        std::cout << "Current Price: " << currentPrice << std::endl;
        std::cout << "Previous Price: " << previousPrice << std::endl;
        std::cout << "Price Change: " << percentageChange << "%" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        
    }
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    if (orders.empty()) return 0.0;
    double max = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max) max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    if (orders.empty()) return 0.0;
    double min = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min) min = e.price;
    }
    return min;
}
