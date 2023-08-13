// #include <iostream>
#include "orderbook/uptoheap.cpp"
#include "csv.h"

struct DataFrameRow {
    double time; 
    int type; 
    int orderid;
    int size;
    float price; 
    int direction;
};


int main(){
    io::CSVReader<3> in("/Users/VishakhS/QFS/CPPOrderbook/LOBSTER_SampleFile_AMZN_2012-06-21_1/AMZN_2012-06-21_34200000_57600000_message_1.csv");
    //   in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    in.read_header(io::ignore_extra_column, "Time","Type","OrderId","Size","Price","Direction");
    double time; int type; int orderid; int size; float price; int direction;
    while(in.read_row(time, type, orderid, size, price, direction)){
        // do stuff with the data
        cout << time << "\n";
    }


    return 0
}

    // // Insert some elements into the heap
    // MaxHeap minHeap;

    // Order* o1 = new Order(1, 12345.6789, "Buy", 1010.0f, 10, "Client A");   
    // Order* o2 = new Order(2, 98765.4321, "Sell", 910.0f, 20, "Client B");
    // Order* o3 = new Order(3, 98765.4321, "Sell", 920.0f, 20, "Client B");
    // Order* o4 = new Order(4, 98765.4321, "Sell", 930.0f, 20, "Client B");

    // Node* n1 = new Node(o1);
    // Node* n2 = new Node(o2);
    // Node* n3 = new Node(o3);
    // Node* n6 = new Node(o4);

    // DoublyLinkedList* node1 = new DoublyLinkedList(n1);
    // DoublyLinkedList* node2 = new DoublyLinkedList(n2);
    // DoublyLinkedList* node3 = new DoublyLinkedList(n3);
    // DoublyLinkedList* node4 = new DoublyLinkedList(n6);

    // minHeap.insert(node1);
    // minHeap.insert(node2);
    // minHeap.insert(node3);
    // minHeap.insert(node4);

    // cout << "Min element: " << minHeap.getMin() << endl;
    // cout << "Heap elements: ";
    // minHeap.printHeap();  // The elements may not be in sorted order after insertion

    // // Remove the minimum element
    // minHeap.popOrder();
    // cout << "After popping the minimum element: ";
    // minHeap.printHeap();  // The heap will be restructured after the pop

    // // Remove a specific element
    // minHeap.remove(node2);
    // cout << "After removing node2: ";
    // minHeap.printHeap();

    // return 0;
}