#include <iostream>
#include "MerkelMain.h"

// Constructor
MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    loadOrderBook();
    int input;
    while(running)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook()
{
    

    orders.push_back(OrderBookEntry{10'000,
                        0.002,
                        "2020/03/17 17:01:24.884492", 
                        "ETH/BTC", 
                        OrderBookType::ask});
    orders.push_back(OrderBookEntry{11'000,
                        0.002,
                        "ETH/BTC", 
                        "ETH/BTC", 
                        OrderBookType::ask});

    for (OrderBookEntry& order : orders)
    {
        std::cout << "The price is " << order.price << std::endl;
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
    // 7. Quit
    std::cout << "7. Quit" << std::endl;

    std::cout << "=================" << std::endl;
    std::cout << "Type in 1-7!" << std::endl;
  }

void MerkelMain::printHelp()
{
  std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers" << std::endl;
}

void MerkelMain::printMarketStats()
{
  std::cout << "OrderBook contains: " << orders.size() << " entries" << std::endl;
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
      std::cout << "Thank you. Have a good day!" << std::endl;
      running = false;
      break;
    default:
      std::cout << "Invalid choice. Choose 1-7" << std::endl;
      break;
  }
}