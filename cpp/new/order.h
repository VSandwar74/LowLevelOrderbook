#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order {
    public:
        int orderId;
        double datetime;
        std::string side;
        float price;
        int volume;
        std::string client;

        Order(int orderId, double datetime, std::string side, float price, int volume, std::string client);

};

#endif