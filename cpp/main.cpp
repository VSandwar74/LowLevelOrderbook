#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "orderbook/uptoheap.cpp"

using namespace std;

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
            cout << cell << endl;
            cell = "";
        } else {
            cell += x;
        }
    }
    row.push_back(cell);
    cout << cell << endl;
    cell = "";

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
        switch (type) {
            case 1:
                book.placeOrder(curr);
                break;
            case 2:
                book.partialCancel(orderid, lotsize);
                break;
            case 3:
                book.cancelOrder(orderid);
                break;
            case 4:
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
