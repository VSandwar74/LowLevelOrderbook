// Implementation of Binary Heap in C++
// Detailed explanation video: https://youtu.be/A9iBOFDfD8Q
// ------------------------------------------------------------

#include <iostream>
#include <vector>
using namespace std;

class MinHeap{
    vector<int> heap;
    
    int parent(int i) { return (i-1)/2; }
    int left(int i) {return (2*i + 1);}
    int right(int i) {return (2*i + 2);}
    
    int peek(int i) {return heap[i];}
    bool exists() {return (sizeof(heap)) ? true : false;}

    void heapify(int i){
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if(l < heap.size() && heap[l] < heap[i])
            smallest = l;
        if(r < heap.size() && heap[r] < heap[smallest])
            smallest = r;
        if(smallest != i){
            std::swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
public:
    int getSize() {return sizeof(heap);}

    int getMin(){ 
        if(exists()) {
            return heap.front();
        }
        return -1;
    }
    
    void insert(int k){
        heap.push_back(k);
        int i = heap.size() - 1;
        while(i != 0 && heap[parent(i)] > heap[i]){
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
        heap.pop_back();
        heapify(0);
    }
    
    
    void printHeap() {
        for(int i = 0; i < heap.size(); ++i)
            cout << heap[i] << "\t";
        cout << endl;
    }

    void remove(int target) {
        if (getSize() == 0) {
            return;
        }
        int loc;
        for (int i = 0; i < getSize(); i++) { 
            if (peek(i) == target) {
                loc = i;
                break;
            }
        }
        heap[loc] = heap.back();
        heap.pop_back();
        heapify(loc);
    }
    
};

class MaxHeap{
    vector<int> heap;
    
    int parent(int i) { return (i-1)/2; }
    int left(int i) {return (2*i + 1);}
    int right(int i) {return (2*i + 2);}
    
    int peek(int i) {return heap[i];}
    bool exists() {return (sizeof(heap)) ? true : false;}

    void heapify(int i){
        int l = left(i);
        int r = right(i);
        int largest = i;
        if(l < heap.size() && heap[l] > heap[i])
            largest = l;
        if(r < heap.size() && heap[r] > heap[largest])
            largest = r;
        if(largest != i){
            (heap[i], heap[largest]);
            heapify(largest);
        }
    }
public:
    int getSize() {return sizeof(heap);}

    int getMin(){ 
        if(exists()) {
            return heap.front();
        }
        return -1;
    }
    
    void insert(int k){
        heap.push_back(k);
        int i = heap.size() - 1;
        while(i != 0 && heap[parent(i)] < heap[i]){
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
        heap.pop_back();
        heapify(0);
    }
    
    
    void printHeap() {
        for(int i = 0; i < heap.size(); ++i)
            cout << heap[i] << "\t";
        cout << endl;
    }

    void remove(int target) {
        if (getSize() == 0) {
            return;
        }
        int loc;
        for (int i = 0; i < getSize(); i++) { 
            if (peek(i) == target) {
                loc = i;
                break;
            }
        }
        heap[loc] = heap.back();
        heap.pop_back();
        heapify(loc);
    }
    
};




int main() {
    MaxHeap H;
    H.insert(20);
    H.insert(8);
    H.insert(5);
    H.insert(10);
    H.insert(15);
    H.insert(12);
    H.printHeap();
    cout << "Min = " << H.getMin() << endl;
    H.popOrder();
    H.printHeap();
    H.remove(10);
    H.printHeap();
    
    return 0;
}