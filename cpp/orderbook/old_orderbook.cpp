#include <iostream>
#include "orderbook.h"

OrderBook::OrderBook() : txct(0) {}

bool OrderBook::_crossedTrade(Heap& book, Order& order) {
    if (book.exists()) {
        if (order.side == "BID") {
            if (order.price >= book.getMin().price) {
                return true;
            }
        } else {
            if (order.price <= book.getMin().price) {
                return true;
            }
        }
    }
    return false;
}

void OrderBook::placeOrder(Order& order) {
    Heap& oppBook = (order.side == "BID") ? bestAsk : bestBid;
    Heap& sameBook = (order.side == "BID") ? bestBid : bestAsk;

    while (order.volume > 0 && _crossedTrade(oppBook, order)) {
        Order matchedOrder = oppBook.getMin();
        txct++;

        int txPrice = matchedOrder.price;
        int txVolume = std::min(order.volume, matchedOrder.volume);

        matchedOrder.volume -= txVolume;
        order.volume -= txVolume;

        volumeMap[txPrice][matchedOrder.side] -= txVolume;

        if (matchedOrder.volume == 0) {
            cancelOrder(matchedOrder.orderId);
        }
    }

    if (order.volume > 0) {
        _placeResting(order, sameBook);
    }
}

void OrderBook::_placeResting(Order& order, Heap& book) {
    orderMap[order.orderId] = new Node(order);

    if (queueMap[order.price][order.side] == nullptr) {
        queueMap[order.price][order.side] = new DoublyLinkedList(orderMap[order.orderId]);
        book.insert(queueMap[order.price][order.side]);
        volumeMap[order.price][order.side] = order.volume;
    } else {
        queueMap[order.price][order.side]->append(orderMap[order.orderId]);
        volumeMap[order.price][order.side] += order.volume;
    }
}

void OrderBook::cancelOrder(int orderId) {
    auto orderNodeIter = orderMap.find(orderId);
    if (orderNodeIter != orderMap.end()) {
        Node* orderNode = orderNodeIter->second;
        Order order = orderNode->item;
        DoublyLinkedList* priceQueue = queueMap[order.price][order.side];
        priceQueue->remove(orderNode);
        if (!priceQueue->exists()) {
            Heap& sameBook = (order.side == "BID") ? bestBid : bestAsk;
            sameBook.remove(priceQueue);
            delete priceQueue;
            queueMap[order.price].erase(order.side);
        }
        volumeMap[order.price][order.side] -= order.volume;
        delete orderNode;
        orderMap.erase(orderId);
    }
}

void OrderBook::executeOrder(int orderId) {
    // add client-side handling
    cancelOrder(orderId);
}

void OrderBook::partialCancel(int orderId, int volume) {
    auto orderNodeIter = orderMap.find(orderId);
    if (orderNodeIter != orderMap.end()) {
        Order& order = orderNodeIter->second->item;
        order.volume -= volume;
        volumeMap[order.price][order.side] -= order.volume;
    }
}

int OrderBook::getVolumeAtPrice(int price, const std::string& side) {
    return volumeMap[price][side];
}
