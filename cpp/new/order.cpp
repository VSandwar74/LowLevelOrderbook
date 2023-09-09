#include "order.h"

Order::Order(int orderId, double datetime, std::string side, float price, int volume, std::string client)
    : orderId(orderId), datetime(datetime), side(side), price(price), volume(volume), client(client) {
}