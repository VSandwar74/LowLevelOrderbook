#include <iostream>
#include <optional>
#include "doublylinkedlist.h"

DoublyLinkedList::DoublyLinkedList(Node& new_node) {
    this->val = new_node.item.price;
    this->head = new Node(new_node.item);
    this->tail = this->head;
};

bool DoublyLinkedList::exists() {
    return head != nullptr;
};

void DoublyLinkedList::append(Node& new_node) {
    new_node.prev = tail;

    if (!tail) {
        head = &new_node;
        tail = &new_node;
        new_node.next = nullptr;
        return;
    }

    tail -> next = &new_node;
    new_node.next = nullptr;
    tail = &new_node;

};

std::optional<Order> DoublyLinkedList::peekFront() {
    if (head) {
        return head -> item;
    }
    return std::nullopt;
};

std::optional<Order> DoublyLinkedList::peekBack() {
    if (tail) {
        return tail -> item;
    } 
    return std::nullopt;
};

std::optional<Order> DoublyLinkedList::popleft() {
    if (!head) {
        return std::nullopt;
    }

    if (!head->next) {
        Order result = head -> item;
        delete head;
        head = nullptr;
        tail = nullptr;
        return result;
    }

    Node* temp = head;
    head = head->next;
    head->prev = nullptr;
    temp->next = nullptr;
    Order result = temp -> item;
    delete temp;
    return result;
};

std::optional<Order> DoublyLinkedList::popright() {
    if (!tail) {
        return std::nullopt;
    }

    if (!tail->prev) {
        // Only one node in the list (tail == head)
        Order result = tail->item;
        delete tail;
        head = nullptr;
        tail = nullptr;
        return result;
    }

    Node* temp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    Order result = temp->item;
    delete temp; // Free the memory of the removed node
    return result;
}



void DoublyLinkedList::remove(Node* target) {
    if (!head || !target) {
        return;
    }

    if (head == target) {
        popleft();
    }

    if (tail == target) {
        popright();
    }

    if (target->next) {
        target->next->prev = target->prev;
    }

    if (target->prev) {
        target->prev->next = target->next;
    }

    delete target;
    return;
}

void DoublyLinkedList::printDLL() {
    if (!head) {
        return;
    }

    std::vector<double> path;

    Node* curr = head;
    while (curr) {
        path.push_back(curr->item.price);
        curr = curr->next;
    }

    for (const double& price : path) {
        std::cout << price << " ";
    }
    std::cout << std::endl;
}