#include <iostream>
#include <limits>
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

    wallet.insertCurrency("BTC", 10);

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
    std::cout << "3. Make an ask " << std::endl;
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
}

void MerkelMain::enterAsk()
{
  std::cout << "Make an offer - Enter amount: product, price, amount, (eg.ETH/BTC,200,0.5)" << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3)
  {
    std::cout << "Bad Input! " << input << std::endl;
  }
  else
  {
    try
    {
      OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
      if (wallet.canFullfillOrder(obe))
      {
        std::cout << "Wallet looks good. " << std::endl;
        orderBook.insertOrder(obe);
      }
      else
      {
        std::cout << "Wallet has insufficient funds." << std::endl;
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << "MerkelMain::enterAsk Bad Input!" << '\n';
    }
  }
  std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid()
{
  std::cout << "Make an Bid - Enter amount: product, price, amount, (eg.ETH/BTC,200,0.5)" << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3)
  {
    std::cout << "Bad Input! " << input << std::endl;
  }
  else
  {
    try
    {
      OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
      if (wallet.canFullfillOrder(obe))
      {
        std::cout << "Wallet looks good. " << std::endl;
        orderBook.insertOrder(obe);
      }
      else
      {
        std::cout << "Wallet has insufficient funds." << std::endl;
      }
    }
    catch(const std::exception& e)
    {
      std::cerr << "MerkelMain::enterBid Bad Input!" << '\n';
    }
  }
  std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::printWallet()
{
  std::cout << wallet.toString() << std::endl;
}

void MerkelMain::nextTimeFrame()
{
  std::cout << "Going to next time frame." << std::endl;
  std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
  std::cout << "Sales: " << sales.size() << std::endl;
  for (OrderBookEntry& sale : sales)
  {
    std::cout << "Sale price: " << sale.price << " Sales amount: " << sale.amount << std::endl;
  }
  currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::printPriceChange()
{
  std::string previousTime = orderBook.getPreviousTime(currentTime);
  orderBook.displayPriceChange(orderBook, currentTime, previousTime);
}

int MerkelMain::getUserOption()
{
  int userOption = 0;
  std::string line;
  std::getline(std::cin, line);
  try
  {
    userOption = std::stoi(line);
  }
  catch(const std::exception& e)
  {
    
  }
  
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
      enterAsk();
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