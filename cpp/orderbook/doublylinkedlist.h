#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <optional>
#include "node.h"

class DoublyLinkedList {
    public:
        double val;
        Node* head;
        Node* tail;
    
        DoublyLinkedList(Node& new_node);

        bool exists();
        void append(Node& new_node);
        std::optional<Order> peekFront();
        std::optional<Order> peekBack();
        std::optional<Order> popleft();
        std::optional<Order> popright();
        void remove(Node* target);
        void printDLL();

};

#endif // DOUBLYLINKEDLIST_H