#ifndef NODE_H
#define NODE_H

#include "order.h"

class Node {
public:
    Order item;
    Node* next;
    Node* prev;

    Node(Order item);
};

#endif // NODE_H
