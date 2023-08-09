#include <iostream>
#include "orderbook/uptoheap.cpp"

int main() {
    // Insert some elements into the heap
    MaxHeap minHeap;

    Order* o1 = new Order(1, 12345.6789, "Buy", 1010.0f, 10, "Client A");   
    Order* o2 = new Order(2, 98765.4321, "Sell", 910.0f, 20, "Client B");
    Order* o3 = new Order(3, 98765.4321, "Sell", 920.0f, 20, "Client B");
    Order* o4 = new Order(4, 98765.4321, "Sell", 930.0f, 20, "Client B");

    Node* n1 = new Node(o1);
    Node* n2 = new Node(o2);
    Node* n3 = new Node(o3);
    Node* n6 = new Node(o4);

    DoublyLinkedList* node1 = new DoublyLinkedList(n1);
    DoublyLinkedList* node2 = new DoublyLinkedList(n2);
    DoublyLinkedList* node3 = new DoublyLinkedList(n3);
    DoublyLinkedList* node4 = new DoublyLinkedList(n6);

    minHeap.insert(node1);
    minHeap.insert(node2);
    minHeap.insert(node3);
    minHeap.insert(node4);

    cout << "Min element: " << minHeap.getMin() << endl;
    cout << "Heap elements: ";
    minHeap.printHeap();  // The elements may not be in sorted order after insertion

    // Remove the minimum element
    minHeap.popOrder();
    cout << "After popping the minimum element: ";
    minHeap.printHeap();  // The heap will be restructured after the pop

    // Remove a specific element
    minHeap.remove(node2);
    cout << "After removing node2: ";
    minHeap.printHeap();

    // Clean up memory
    // delete node1;
    // delete node2;
    // delete node3;
    // delete node4;

    return 0;
}