#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "orderbook/orderbook.cpp"

using namespace std;

// int main() {

//     OrderBook orderBook;

//     Order bidOrder(1, 12345.6789, "BID", 1000.0, 10, "Client A");
//     Order askOrder(2, 12346.7890, "ASK", 1010.0, 8, "Client B");

//     cout << askOrder.datetime << "\n";

//     orderBook.placeOrder(bidOrder);
//     orderBook.placeOrder(askOrder);

//     // Check if trades have occurred and holdings have been updated accordingly
//     assert(orderBook.getVolumeAtPrice(1000, "BID") == 10);
//     assert(orderBook.getVolumeAtPrice(1010, "ASK") == 8);

// }

int main() {

    OrderBook book;

    ifstream file;
    file.open("/Users/VishakhS/QFS/CPPOrderbook/LOBSTER_SampleFile_AMZN_2012-06-21_1/AMZN_2012-06-21_34200000_57600000_message_1.csv");

    // Parse Header; 
    string line;
    getline(file, line);
    vector<string> row;
    string cell;
    for (char x:line) {
        if (x == ',') {
            row.push_back(cell);
            // cout << cell << endl;
            cell = "";
        } else {
            cell += x;
        }
    }
    row.push_back(cell);
    // cout << cell << endl;
    cell = "";

    cout << "header parsed" << "\n";

    int a = 0;

    while (getline(file, line)) {
        // Parse rows
        vector<string> row;
        string cell;
        for (char x:line) {
            if (x == ',') {
                row.push_back(cell);
                cout << cell << " ";
                cell = "";
            } else {
                cell += x;
            }
        }
        row.push_back(cell);
        cout << cell << endl;
        cell = "";

        // Time,Type,OrderId,Size,Price,Direction
        double time = stod(row[0]);
        int type = stoi(row[1]);
        int orderid = stoi(row[2]);
        int lotsize = stoi(row[3]);
        double price = stoi(row[4]);
        int direction = stoi(row[5]);
        price /= 1000;

        Order curr(orderid, time, (direction == 1) ? "BID" : "ASK", price, lotsize, "client");

        cout << "TRY " << a << "\n";
        a += 1;
        // cout << "made it" << "\n";

        switch (type) {
            case 1:
                cout << "placed" << "\n";
                book.placeOrder(curr);
                book.printMap();
                break;
            case 2:
                cout << "part cancel" << "\n";
                book.partialCancel(orderid, lotsize);
                break;
            case 3:
                cout << "full cancel" << "\n";
                book.cancelOrder(orderid);
                break;
            case 4:
                cout << "exec" << "\n";
                // book.printQueueMap();
                book.executeOrder(orderid, "market");
                break;
            case 5:
                // hidden execute
                break;
            case 7:
                // halts
                break;
            default:
                break;
        }


    }

    file.close();
    return 0;
}
