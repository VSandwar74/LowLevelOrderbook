#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm> // for std::min
using namespace std;

class Order {
    public:
        int orderId;
        double datetime;
        string side;
        double price;
        mutable int volume;
        string client;

        Order(int orderId, double datetime, std::string side, double price, int volume, std::string client)
            : orderId(orderId), datetime(datetime), side(side), price(price), volume(volume), client(client) {
        }

        void cutVolume(int diff) const {
            volume -= diff;
            return;
        }
        
        void printAll() const {
            std::cout << "OrderID " << orderId << "\n";
            std::cout << "date " << datetime << "\n";
            std::cout << "side " << side << "\n";
            std::cout << "px " << price << "\n";
            std::cout << "vol " << volume << "\n";
            std::cout << "client " << client << "\n";
        };
};

class Node {
    public:
        const Order& item; // try reference
        Node* prev;
        Node* next;

        Node(const Order& item) : item(item), prev(NULL), next(NULL) {};
};

class DoublyLinkedList {
    public:
        Node* head;
        Node* tail;
        int val;

        DoublyLinkedList(Node* init) : head(init), tail(init), val(init->item.price) {}

        bool exists() {
            bool result = (head) ? true : false;
            return result;
        }

        void prepend(Node* newNode) {
            newNode->next = head;

            if (!head) {
                head = newNode;
                tail = newNode;
                newNode->prev = nullptr;
                return;
            } else {
                head->prev = newNode;
                newNode->prev = nullptr;
                head = newNode;
            }
        }

        void append(Node* newNode) {
            newNode->prev = tail;

            if (!tail) {
                tail = newNode;
                head = newNode;
                newNode->next = nullptr;
                return;
            } else {
                tail->next = newNode;
                newNode->next = nullptr;
                tail = newNode;
            }
        }

        int peekFront() {
            if (head) {
                return head->item.price;
            }
            return -1;
        }

        int peekBack() {
            if (tail) {
                return tail->item.price;
            }
            return -1;
        }

        int popleft() {
            if (!head) {
                return -1;
            }

            Node* temp = head;
            int result = temp->item.price;

            if (!head->next) {
                head = nullptr;
                tail = nullptr;
            } else { 
                temp->next->prev = nullptr;
                head = temp->next;
                temp->next = nullptr;
            }

            // delete temp;

            return result;
        }

        // swap to order
        int popright() {
            if (!tail) {
                return -1; // swap for nullptr
            }

            Node* temp = tail;
            int result = temp->item.price;

            if (!tail->prev) {
                head = nullptr;
                tail = nullptr;
            } else {
                tail->prev->next = nullptr;
                tail = temp->prev;
                temp->prev = nullptr;
            }

            // delete temp;

            return result;
        }

        void remove(Node* target) {

            cout << (exists()) << "\n";
            // printDLL();
            if (!head && !tail) {
                return;
            } else if (head->item.orderId == target->item.orderId) {
                // cout << "left" << endl;
                popleft();
            } else if (tail->item.orderId == target->item.orderId) {
                // cout << "right" << endl;
                popright();
            } else {
                // cout << "travl" << endl;
                if (target->next) {
                    target->next->prev = target->prev;
                }
                if (target->prev) {
                    target->prev->next = target->next;
                }

                // delete target;
            }
        }

        void printDLL() {
            // cout << head;
            Node* current = head;
            while (current != nullptr) {
                // Assuming Order has a method to print itself, replace the line below accordingly
                std::cout << "Order: " << current->item.orderId << " ";
                current = current->next;
            }
            // std::cout << std::endl;
        }
};
class Heap {
    public:
        vector<DoublyLinkedList*> heap;
        int parent(int i) { return (i-1)/2; }
        int left(int i) {return (2*i + 1);}
        int right(int i) {return (2*i + 2);}
        
        int peek(int i) {
            return heap[i]->val;
        }
        bool exists() {return !heap.empty();}
        const Order* getMin(){ 
            if(exists() and heap.front()->head) {
                return &heap.front()->head->item;
            }
            return nullptr;
        }
        virtual void insert(DoublyLinkedList* k) {return;}
        virtual void popOrder() {return;}
        virtual void remove(DoublyLinkedList* target) {return;}

};

class MinHeap: public Heap {

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
    
    void insert(DoublyLinkedList* k) override{
        heap.push_back(k);
        int i = heap.size() - 1;
        while(i != 0 && peek(parent(i)) > peek(i)){
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void popOrder() override{
        if(heap.size() == 0){
            // cout << "Heap is empty" << endl;
            return;
        }
        heap[0] = heap.back();
        // DoublyLinkedList* removedPtr = heap.back();
        heap.pop_back();
        heapify(0);
        // delete removedPtr;
    }
    

    
    void printHeap() {
        for(int i = 0; i < heap.size(); ++i) {
            cout << peek(i) << "\t";
        }
        cout << endl;
    }

    void remove(DoublyLinkedList* target) override {
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

        // delete target;        
    }
    
};

class MaxHeap: public Heap {
    
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
    
    void insert(DoublyLinkedList* k) override{
        heap.push_back(k);
        int i = heap.size() - 1;
        while(i != 0 && peek(parent(i)) < peek(i)){
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    void popOrder() override{
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

    void remove(DoublyLinkedList* target) override {
        if (getSize() == 0) {
            return;
        }
        int loc;
        for (int i = 0; i < getSize()-1; i++) { 
            if (heap[i] == target) {
                loc = i;
                break;
            }
        }
        heap[loc] = heap.back();
        heap.pop_back();
        heapify(loc);

        // delete target;
    }
    
};

class OrderBook {
    private:
        MaxHeap bestBid;
        MinHeap bestAsk;
        unordered_map<int, Node*> orderMap; // orderid // orderref
        unordered_map<int, unordered_map<string, int> > volumeMap; // price // side // volume
        unordered_map<int, unordered_map<string, DoublyLinkedList*> > queueMap; // price // side // dll
        unordered_map<string, unordered_map<string, double> > clientMap; // client // exposure/cash // value
        int txct; // tx count

        bool crossedTrade(Heap* book, Order order) {
            cout << "crossedTrade" << "\n";
            if (book->exists()) {
                // cout << book->getMin() << endl;
                if (order.side == "BID") {
                    if (order.price >= book->peek(0)) {
                        return true;
                    }
                } else {
                    if (order.price <= book->peek(0)) {
                        return true;
                    }
                }
            }
            return false;
        }

        void updateHoldings(const Order& order, string matchClient, int txVolume, double txPrice) {
            cout << "updateHoldings" << "\n";
            if (order.side == "BID") {
                clientMap[order.client]["Exposure"] += txVolume;
                clientMap[order.client]["Cash"] -= txVolume * txPrice;
                clientMap[matchClient]["Exposure"] -= txVolume;
                clientMap[matchClient]["Cash"] += txVolume * txPrice;
            } else {
                clientMap[order.client]["Exposure"] -= txVolume;
                clientMap[order.client]["Cash"] += txVolume * txPrice;
                clientMap[matchClient]["Exposure"] += txVolume;
                clientMap[matchClient]["Cash"] -= txVolume * txPrice;
            }
        };

        void placeResting(const Order& order, Heap* book) { // try pass as reference
            cout << "placeResting" << "\n";
              
            // cout << "resting" << "\n";
            // order.printAll();  
            // orderMap[order.orderId] = n1;
            orderMap[order.orderId] = new Node(order);
            // cout << &n1->item << endl;
            if (queueMap.count(order.price) == 0 || queueMap[order.price].count(order.side) == 0) {
                queueMap[order.price][order.side] = new DoublyLinkedList(orderMap[order.orderId]);
                book->insert(queueMap[order.price][order.side]);
                volumeMap[order.price][order.side] = order.volume;
            } else {
                // queueMap[order.price][order.side]->append(orderMap[order.orderId])
                queueMap[order.price][order.side]->append(orderMap[order.orderId]);
                volumeMap[order.price][order.side] += order.volume;
            }

            printMap();
            cout << "should end" << endl;
        };

    public:

        void printQueueMap() const {
            for (const auto& priceEntry : queueMap) {
                int price = priceEntry.first;
                std::cout << "Price: " << price << std::endl;

                const auto& sideMap = priceEntry.second;
                for (const auto& sideEntry : sideMap) {
                    const std::string& side = sideEntry.first;
                    DoublyLinkedList* dll = sideEntry.second;

                    std::cout << "Side: " << side << std::endl;
                    cout << &dll << endl;
                    std::cout << "Doubly Linked List Contents: " << endl;
                    if (dll) {
                        dll->printDLL(); // Assuming DoublyLinkedList has a printDLL method
                    } else {
                        std::cout << "nullptr" << std::endl;
                    }
                }
            }
        }

        void placeOrder(Order order) {
            cout << "placeOrder" << "\n";

            Heap* oppBook = nullptr;
            Heap* sameBook = nullptr;
            if (order.side == "BID") {
                oppBook = &bestAsk;
                sameBook = &bestBid;
            } else {
                sameBook = &bestAsk;
                oppBook = &bestBid;
            }
            if (clientMap.count(order.client) == 0) {
                clientMap[order.client]["Cash"] = 0;
                clientMap[order.client]["Exposure"] = 0;
            }
            while (order.volume > 0 && crossedTrade(oppBook, order)) {
                const Order* matchedOrder = oppBook->getMin();
                double txPrice = matchedOrder->price;
                int txVolume = min(order.volume, matchedOrder->volume);
                txct += txVolume;
                matchedOrder->cutVolume(txVolume);
                // matchedOrder->volume -= txVolume;
                order.volume -= txVolume;
                updateHoldings(order, matchedOrder->client, txVolume, txPrice);
                volumeMap[txPrice][matchedOrder->side] -= txVolume;
                if (matchedOrder->volume == 0) {
                    cancelOrder(matchedOrder->orderId);
                    // oppBook->popOrder();
                }
            }
            if (order.volume > 0) {
                // Node* n1 = new Node(order);
                placeResting(order, sameBook);
                // delete n1;
            }
            // new code
            // delete oppBook;
            // delete sameBook;
        };

        void cancelOrder(int orderId) { // prob could use order pointer
            cout << "cancelOrder" << "\n";

            auto iter = orderMap.find(orderId);

            if (iter != orderMap.end()) {
                // cout << "found" << "\n";

                Node* orderNode = orderMap[orderId];
                const Order& order = orderNode->item;
                cout << order.price << "\n";
                cout << order.side << "\n";

                printQueueMap();
                DoublyLinkedList* priceQueue = queueMap[order.price][order.side];



                cout << priceQueue << "\n";
                cout << priceQueue->exists() << "\n";


                
                priceQueue->remove(orderNode);
                
                cout << "dequeued" << "\n";

                if (!priceQueue->exists()) {
                    Heap& sameBook = (order.side == "BID") ?  static_cast<Heap&>(bestBid) :  static_cast<Heap&>(bestAsk);
                    sameBook.remove(priceQueue); // priceQueue freed in func.

                    delete priceQueue;
                    queueMap[order.price].erase(order.side); 
                }

                // cout << "i think here" << "\n";
                
                volumeMap[order.price][order.side] -= order.volume;
                
                // delete orderNode;
                orderMap.erase(orderId);
                // new code
                // delete orderNode->item;
            }
        }; 

        void executeOrder(int orderId, string client) {
            cout << "executeOrder" << "\n";

            // printMap();

            // cout << orderId << endl;

            auto iter = orderMap.find(orderId);


            if (iter != orderMap.end()) {
            // if (orderMap.count(orderId) > 0) {
                const Order& order = orderMap[orderId]->item;

                cout << &order << endl;

                cout << "pre update" << endl;

                // order.printAll();
                // order.printAll
                
                if (clientMap.count(client) == 0) {
                    clientMap[client]["Cash"] = 0;
                    clientMap[client]["Exposure"] = 0;
                }


                updateHoldings(order, client, order.volume, order.price);

                cout << "post update" << endl;

                order.printAll();
                
                cancelOrder(orderId); // broken

                // cout << "post cancel" << endl;
            }
        };

        void partialCancel(int orderId, int vol) {
            if (orderMap.count(orderId) > 0) {
                const Order& order = orderMap[orderId]->item;
                order.volume -= vol;
                volumeMap[order.price][order.side] -= vol;
            }
        };
        
        int getVolumeAtPrice(int price, string side) {
            return volumeMap[price][side];
        };

        void printMap() {
            for (const auto& pair : orderMap) {
                int orderId = pair.first;
                const Node* node = pair.second;

                std::cout << "Order ID: " << orderId << "\n";

                if (node) {
                    std::cout << "  Order Reference: " << &node->item << "\n";
                    node->item.printAll();
                } else {
                    std::cout << "  No order reference found.\n";
                }
            }
        };

        OrderBook(): txct(0) {};
};



// int main() {
//     // Insert some elements into the heap
//     MaxHeap minHeap;

//     Order* o1 = new Order(1, 12345.6789, "Buy", 1010.0f, 10, "Client A");   
//     Order* o2 = new Order(2, 98765.4321, "Sell", 910.0f, 20, "Client B");
//     Order* o3 = new Order(3, 98765.4321, "Sell", 920.0f, 20, "Client B");
//     Order* o4 = new Order(4, 98765.4321, "Sell", 930.0f, 20, "Client B");

//     Node* n1 = new Node(o1);
//     Node* n2 = new Node(o2);
//     Node* n3 = new Node(o3);
//     Node* n6 = new Node(o4);

//     DoublyLinkedList* node1 = new DoublyLinkedList(n1);
//     DoublyLinkedList* node2 = new DoublyLinkedList(n2);
//     DoublyLinkedList* node3 = new DoublyLinkedList(n3);
//     DoublyLinkedList* node4 = new DoublyLinkedList(n6);

//     minHeap.insert(node1);
//     minHeap.insert(node2);
//     minHeap.insert(node3);
//     minHeap.insert(node4);

//     cout << "Min element: " << minHeap.getMin() << endl;
//     cout << "Heap elements: ";
//     minHeap.printHeap();  // The elements may not be in sorted order after insertion

//     // Remove the minimum element
//     minHeap.popOrder();
//     cout << "After popping the minimum element: ";
//     minHeap.printHeap();  // The heap will be restructured after the pop

//     // Remove a specific element
//     minHeap.remove(node2);
//     cout << "After removing node2: ";
//     minHeap.printHeap();

//     // Clean up memory
//     // delete node1;
//     // delete node2;
//     // delete node3;
//     // delete node4;

//     return 0;
// }
// int main() {
//  // Create a linked list with elements
//     Order* o1 = new Order(1, 12345.6789, "Buy", 1010.0f, 10, "Client A");
//     Order* o2 = new Order(2, 98765.4321, "Sell", 910.0f, 20, "Client B");
//     Order* o3 = new Order(3, 98765.4321, "Sell", 920.0f, 20, "Client B");
//     Order* o4 = new Order(4, 98765.4321, "Sell", 930.0f, 20, "Client B");

//     Node* node1 = new Node(o1);
//     Node* node2 = new Node(o2);
//     Node* node3 = new Node(o3);
//     Node* node6 = new Node(o4);
//     // Node* node7 = new Node(7);

//     DoublyLinkedList list(node1);
//     list.append(node2);
//     list.append(node3);
//     list.append(node6);
//     // list.append(node7);

//     // Display initial list
//     std::cout << "Initial List: ";
//     list.printDLL();

//     // Test Case: Perform popleft
//     int removedValue = list.popleft();
//     std::cout << "Removed Value: " << removedValue << std::endl;

//     // Display updated list
//     std::cout << "Updated List: ";
//     list.printDLL();

//     // Test Case: Perform popright
//     int newval = list.popright();
//     std::cout << "Removed Value: " << newval << std::endl;

//     // Display updated list
//     std::cout << "Updated List: ";
//     list.printDLL();

//     list.remove(node3);

//     // Display updated list
//     std::cout << "Updated List: ";
//     list.printDLL();

//     return 0;
// }
