#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
public:
    int orderId;
    double datetime;
    std::string side;
    double price;
    int volume;
    std::string client;

    Order(int orderId, double time, std::string bidOrAsk, double price, int volume, std::string client);
};

#endif // ORDER_H
