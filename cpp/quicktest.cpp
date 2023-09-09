#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "orderbook/orderbook.cpp"

int main() {
    OrderBook book;

    Order placed(11885113, 34200.01746, "BID", 2238100, 21, "client");
    Order execed(11885113, 34200.18961, "BID", 2238100, 21, "client");

    book.printMap();
    book.placeOrder(placed);
    book.printMap();

    // book.executeOrder(execed.orderId, "market");
}
