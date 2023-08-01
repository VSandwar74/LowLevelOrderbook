#include "MinHeap.hpp"

MinHeap::MinHeap() : Heap() {}

void MinHeap::heapify(int i) {
    int l = _left(i);
    int r = _right(i);
    int smallest = i;

    if (l < heap.size() && _peek(l) < _peek(i)) {
        smallest = l;
    }
    if (r < heap.size() && _peek(r) < _peek(smallest)) {
        smallest = r;
    }
    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapify(smallest);
    }
}

void MinHeap::insert(DoublyLinkedList* dll) {
    heap.push_back(dll);
    int i = heap.size() - 1;
    while (i != 0 && _peek(_parent(i)) > _peek(i)) {
        std::swap(heap[i], heap[_parent(i)]);
        i = _parent(i);
    }
}


void MinHeap::remove(DoublyLinkedList* target) {
    if (heap.empty()) {
        return;
    }

    int i = 0;
    for (; i < heap.size(); ++i) {
        if (heap[i] == target) {
            break;
        }
    }

    heap[i] = heap.back();
    heap.pop_back();
    heapify(0);
}
