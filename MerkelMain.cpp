#include <iostream>
#include "MerkelMain.h"
#include "CSVReader.h"

// Constructor
MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    while(running)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    std::cout << "=================" << std::endl;
    // 1. print help
    std::cout << "1: Print help " << std::endl;
    // 2. print exchange stats
    std::cout << "2: Print exchange stats " << std::endl;
    // 3. make an offer
    std::cout << "3. Make an offer " << std::endl;
    // 4. make a bid
    std::cout << "4. Make a bid " << std::endl;
    // 5. Print wallet
    std::cout << "5. Print my wallet " << std::endl;
    // 6. continue
    std::cout << "6. Continue " << std::endl;
    // 7. price change
    std::cout << "7. Price Change" << std::endl;
    // 7. Quit
    std::cout << "8. Quit" << std::endl;

    std::cout << "=================" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "=================" << std::endl;

    std::cout << "Type in 1-8!" << std::endl;
  }

void MerkelMain::printHelp()
{
  std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers" << std::endl;
}

void MerkelMain::printMarketStats()
{
  for (std::string const& p : orderBook.getKnownProducts())
  {
    std::cout << "Product: " << p << std::endl;
    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max Ask: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Min Ask: " << OrderBook::getLowPrice(entries) << std::endl;

  }
  // std::cout << "OrderBook entries: " << orders.size() << std::endl;
  // unsigned int bids = 0;
  // unsigned int asks = 0;
  // for (OrderBookEntry& e : orders)
  // {
  //   if (e.orderType == OrderBookType::ask)
  //   {
  //     asks++;
  //   }
  //   if (e.orderType == OrderBookType::bid)
  //   {
  //     bids++;
  //   }
  // }
  //   std::cout << "OrderBook asks: " << asks << "\n" << "OrderBook bids: " << bids << std::endl;

}

void MerkelMain::enterOffer()
{
  std::cout << "Make an offer - Enter amount" << std::endl;
}

void MerkelMain::enterBid()
{
  std::cout << "Mane a bid - Enter amount" << std::endl;
}

void MerkelMain::printWallet()
{
  std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::nextTimeFrame()
{
  std::cout << "Going to next time frame." << std::endl;
  currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::printPriceChange()
{
  std::string previousTime = orderBook.getPreviousTime(currentTime);
  orderBook.displayPriceChange(orderBook, currentTime, previousTime);
}

int MerkelMain::getUserOption()
{
  int userOption;
  std::cin >> userOption;
  return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
  switch (userOption)
  {
    case 1:
      printHelp();
      break;
    case 2:
      printMarketStats();
      break;
    case 3:
      enterOffer();
      break;
    case 4:
      enterBid();
      break;
    case 5:
      printWallet();
      break;
    case 6:
      nextTimeFrame();
      break;
    case 7:
      printPriceChange();
      break;
    case 8:
      std::cout << "Thank you. Have a good day!" << std::endl;
      running = false;
      break;
    default:
      std::cout << "Invalid choice. Choose 1-7" << std::endl;
      break;
  }
}