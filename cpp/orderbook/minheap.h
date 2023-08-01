#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "heap.h"
#include "doublylinkedlist.h" 

class MinHeap : public Heap {
public:
    MinHeap();

    void heapify(int i);
    void insert(DoublyLinkedList* dll);
    void remove(DoublyLinkedList* target);
};

#endif // MIN_HEAP_H
