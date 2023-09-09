#include <iostream>
#include <vector>
#include "uptoheap.cpp"
using namespace std;

class Heap {
    public:
        vector<DoublyLinkedList*> heap;
        int parent(int i) { return (i-1)/2; }
        int left(int i) {return (2*i + 1);}
        int right(int i) {return (2*i + 2);}
        
        int peek(int i) {return heap[i]->val;}
        bool exists() {return (sizeof(heap)) ? true : false;}
};

class MinHeap: public Heap {
    // vector<DoublyLinkedList*> heap;
    
    // int parent(int i) { return (i-1)/2; }
    // int left(int i) {return (2*i + 1);}
    // int right(int i) {return (2*i + 2);}
    
    // int peek(int i) {return heap[i]->val;}
    // bool exists() {return (sizeof(heap)) ? true : false;}

    void heapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if(l < heap.size() && peek(l) < peek(i))
            smallest = l;
        if(r < heap.size() && peek(r) < peek(smallest))
            smallest = r;
        if(smallest != i){
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
public:
    int getSize() {return sizeof(heap);}

    int getMin(){ 
        if(exists()) {
            return heap.front()->val;
        }
        return -1;
    }
    
    void insert(DoublyLinkedList* k){
        heap.push_back(k);
        int i = heap.size() - 1;
        while(i != 0 && peek(parent(i)) > peek(i)){
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void popOrder(){
        if(heap.size() == 0){
            cout << "Heap is empty" << endl;
            return;
        }
        heap[0] = heap.back();
        // DoublyLinkedList* removedPtr = heap.back();
        heap.pop_back();
        heapify(0);
        // delete removedPtr;
    }
    
    
    void printHeap() {
        for(int i = 0; i < heap.size(); ++i)
            cout << peek(i) << "\t";
        cout << endl;
    }

    void remove(DoublyLinkedList* target) {
        if (getSize() == 0) {
            return;
        }
        int loc;
        for (int i = 0; i < getSize(); i++) { 
            if (heap[i] == target) {
                loc = i;
                break;
            }
        }
        heap[loc] = heap.back();
        heap.pop_back();
        heapify(loc);
        
        delete target;
    }
    
};

class MaxHeap: public Heap {
    // vector<DoublyLinkedList*> heap;
    
    // int parent(int i) { return (i-1)/2; }
    // int left(int i) {return (2*i + 1);}
    // int right(int i) {return (2*i + 2);}
    
    // int peek(int i) {return heap[i]->val;}
    // bool exists() {return (sizeof(heap)) ? true : false;}

    void heapify(int i){
        int l = left(i);
        int r = right(i);
        int largest = i;
        if(l < heap.size() && peek(l) > peek(i))
            largest = l;
        if(r < heap.size() && peek(r) > peek(largest))
            largest = r;
        if(largest != i){
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }
public:
    int getSize() {return sizeof(heap);}

    int getMin(){ 
        if(exists()) {
            return heap.front()->val;
        }
        return -1;
    }
    
    void insert(DoublyLinkedList* k){
        heap.push_back(k);
        int i = heap.size() - 1;
        while(i != 0 && peek(parent(i)) < peek(i)){
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void popOrder(){
        if(heap.size() == 0){
            cout << "Heap is empty" << endl;
            return;
        }
        heap[0] = heap.back();
        // DoublyLinkedList* removedPtr = heap.back();
        heap.pop_back();
        heapify(0);

        // delete removedPtr;
    }
    
    
    void printHeap() {
        for(int i = 0; i < heap.size(); ++i)
            cout << peek(i) << "\t";
        cout << endl;
    }

    void remove(DoublyLinkedList* target) {
        if (getSize() == 0) {
            return;
        }
        int loc;
        for (int i = 0; i < getSize(); i++) { 
            if (heap[i] == target) {
                loc = i;
                break;
            }
        }
        heap[loc] = heap.back();
        heap.pop_back();
        heapify(loc);

        delete target;
    }
    
};




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