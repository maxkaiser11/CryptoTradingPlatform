build:
	g++ main.cpp MerkelMain.cpp OrderBook.cpp OrderBookEntry.cpp CSVReader.cpp -o trading

run:
	./trading