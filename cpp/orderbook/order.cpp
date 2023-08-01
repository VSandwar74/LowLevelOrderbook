#include "order.h"

Order::Order(int orderId, double time, std::string bidOrAsk, double price, int volume, std::string client)
    : orderId(orderId), datetime(time), side(bidOrAsk), price(price), volume(volume), client(client) {}
