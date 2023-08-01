#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "heap.h"
#include "doublylinkedlist.h" 

class MaxHeap : public Heap {
public:
    MaxHeap();

    void heapify(int i);
    void insert(DoublyLinkedList* dll);
    void remove(DoublyLinkedList* target);
};

#endif // MAX_HEAP_H
