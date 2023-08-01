#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "orderbook/orderbook.cpp" 
# include "csv.h"

struct DataFrameRow {
    std::string Tick;
    std::string Ask;
    std::string AV;
    std::string Bid;
    std::string BVol;
};

int main() {

    OrderBook book;

    std::vector<std::vector<std::string>> data;
    int ct = 0;

    io::CSVReader<3> in("/Users/VishakhS/QFS/CPPOrderbook/LOBSTER_SampleFile_AMZN_2012-06-21_1/AMZN_2012-06-21_34200000_57600000_message_1.csv");
    in.read_header(io::ignore_extra_column, 'time', 'type', 'orderid', 'size', 'price', 'direction');
    double time; int type; int orderid, int size, float price, int direction;
    while(in.read_row(time, type, orderid, size, price, direction)){

        if (type == 1) {
            // Place order
            Order curr(orderid, time, (direction == 1 ? "BID" : "ASK"), price, size, "market");
            book.placeOrder(curr);
        } else if (type == 2) {
            // Partial cancel
            book.partialCancel(row.OrderId, row.Size);
        } else if (type == 3) {
            // Full cancel
            book.cancelOrder(row.OrderId);
        } else if (type == 4) {
            // Execution of visible
            book.executeOrder(row.OrderId);
        } else if (type == 5) {
            // Execution of hidden
            continue;
        } else if (type == 7) {
            // Halts
            continue;
        }

        // Retrieve bestAsk and bestBid from the OrderBook
        std::string bestAsk = book.bestAsk.getMin();
        std::string bestBid = book.bestBid.getMin();

        std::vector<std::string> bookListing;

        if (bestAsk != "" && bestBid != "") {
            bookListing.push_back(row.Time);

            bookListing.push_back(std::to_string(bestAsk.price));
            bookListing.push_back(std::to_string(book.getVolumeAtPrice(bestAsk.price, "ASK")));

            bookListing.push_back(std::to_string(bestBid.price));
            bookListing.push_back(std::to_string(book.getVolumeAtPrice(bestBid.price, "BID")));

            data.push_back(bookListing);
        }
    }

    std::vector<DataFrameRow> dataList = data;
    
    std::ofstream outputFile("reconstructed_book.csv");
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    outputFile << "Tick,Ask,AV,Bid,BVol" << std::endl;

    for (const auto& row : dataList) {
        outputFile << row.Tick << ","
                   << row.Ask << ","
                   << row.AV << ","
                   << row.Bid << ","
                   << row.BVol << std::endl;
    }

    outputFile.close();

    return 0;
}
