#include "MaxHeap.hpp"

MaxHeap::MaxHeap() : Heap() {}

void MaxHeap::heapify(int i) {
    int l = _left(i);
    int r = _right(i);
    int largest = i;

    if (l < heap.size() && _peek(l) > _peek(i)) {
        largest = l;
    }
    if (r < heap.size() && _peek(r) > _peek(largest)) {
        largest = r;
    }
    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        heapify(largest);
    }
}

void MaxHeap::insert(DoublyLinkedList* dll) {
    heap.push_back(dll);
    int i = heap.size() - 1;
    while (i != 0 && _peek(_parent(i)) < _peek(i)) {
        std::swap(heap[i], heap[_parent(i)]);
        i = _parent(i);
    }
}

void MaxHeap::remove(DoublyLinkedList* target) {
    if (heap.empty()) {
        return;
    }

    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i] == target) {
            heap[i] = heap.back();
            heap.pop_back();
            heapify(0);
            return;
        }
    }
}

