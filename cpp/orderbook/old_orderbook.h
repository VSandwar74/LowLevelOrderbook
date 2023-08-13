#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "maxheap.h"
#include "minheap.h"
#include "doublylinkedlist.h"
#include "order.h"
#include <unordered_map>

class OrderBook {
    private:
        bool _crossedTrade(Heap& book, Order& order);
        void _placeResting(Order& order, Heap& book);

    public:
        MaxHeap bestBid;
        MinHeap bestAsk;
        std::unordered_map<int, Node*> orderMap;
        std::unordered_map<double, std::unordered_map<std::string, DoublyLinkedList*>> queueMap;
        std::unordered_map<double, std::unordered_map<std::string, int>> volumeMap;
        int txct;

        OrderBook();

        void placeOrder(Order order);
        void cancelOrder(int orderId);
        void executeOrder(int orderId);
        void partialCancel(int orderId, int volume);
        int getVolumeAtPrice(double price, const std::string& side);

};

#endif // ORDERBOOK_H
