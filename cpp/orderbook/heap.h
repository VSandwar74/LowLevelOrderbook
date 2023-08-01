#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <optional>
#include "Order.hpp" // Assuming Order class is defined in Order.hpp

class Heap {
public:
    Heap();

    // Helper functions (not exposed to derived classes)
    int _parent(int i);
    int _left(int i);
    int _right(int i);
    int _peek(int i);

    std::optional<Order> getMin();
    int getSize();
    bool exists();
    void printHeap();

private:
    std::vector<std::vector<Order>> heap;
};

#endif // HEAP_H
