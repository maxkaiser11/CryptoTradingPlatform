#include <string>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> tokenise(std::string csvLine, char seperator)
{
    std::vector<std::string> tokens;

    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(seperator, 0);
    do
    {
        end = csvLine.find_first_of(seperator, start);
        if (start == csvLine.length() || start == end) break;

        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = ++end;
    } while (end > 0);
    

    return tokens;
}


int main()
{
    // std::string s = "2020/03/17 17:01:24.884492,ETH/BTC,ask,0.02223142,0.086064";
    // tokens = tokenise(s, ',');

    // for (std::string& token : tokens)
    // {
    //     std::cout << token << std::endl;
    // }

    std::ifstream csvFile{"data.csv"};
    std::string line;
    std::vector<std::string> tokens;


    if (csvFile.is_open())
    {
        std::cout << "Opened File" << std::endl;

        while(std::getline(csvFile, line))
        {
            std::cout << "Read Line: " <<  line << std::endl;
            tokens = tokenise(line, ',');
            if (tokens.size() != 5)
            {
                std::cout << "Bad Line" << std::endl;
                continue;
            }
            // we have 5 tokens
            try
            {
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
                std::cout << price << ":" << amount << std::endl;
            }
            catch(std::exception& e)
            {
                std::cout << "Bad Float! " << tokens[3] << std::endl;
                std::cout << "Bad Float! " << tokens[4] << std::endl;
                continue;
            }
        
        }
        csvFile.close();
    }
    else
    {
        std::cout << "Could not open file" << std::endl;
    }

    return 0;
}