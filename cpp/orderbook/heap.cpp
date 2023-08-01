#include <iostream>
#include <vector>
#include "heap.h"

Heap::Heap() {}

int Heap::_parent(int i) { return (i - 1) / 2; }

int Heap::_left(int i) { return 2 * i + 1; }

int Heap::_right(int i) { return 2 * i + 2; }

int Heap::_peek(int i) { return heap[i].val; }

std::optional<Order> Heap::getMin() {
    if (!heap.empty() && heap[0].head) {
        return heap[0].head->item;
    }
    return std::nullopt;
}

int Heap::getSize() { return heap.size(); }

bool Heap::exists() { return !heap.empty() && heap[0].head; }

void Heap::printHeap() {
    std::vector<std::vector<int>> out;
    for (const auto& h : heap) {
        std::vector<int> lvl;
        Node* curr = h.head;
        while (curr) {
            lvl.push_back(curr->item.orderId);
            curr = curr->next;
        }
        out.push_back(lvl);
    }
    for (const auto& lvl : out) {
        for (const auto& item : lvl) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}
