#include <iostream>
#include <vector>
#include <unordered_map>
#include "uptoheap.cpp"

class Orderbook {
    private:
        MaxHeap bestBid;
        MinHeap bestAsk;
        unordered_map<int, Order*> orderMap; // orderid // order
        unordered_map<int, unordered_map<string, int>> volumeMap; // price // side // volume
        unordered_map<int, unordered_map<string, DoublyLinkedList*>> queueMap; // price // side // dll
        unordered_map<string, unordered_map<string, double>> clientMap; // client // exposure/cash // value
        int txct; // tx count

        bool crossedTrade(Heap& book, Order order) {
            if (book.exists()) {
                if (order.side == 'BID') {
                    if (order.price >= book.getMin()) {
                        return;
                    }
                }
            }
        }

        void updateHoldsings(Order order, string matchClient, int txVolume, double txPrice);
        void placeResting(Order order, Heap* book);

    public:

        void placeOrder(Order order);
        void cancelOrder(string orderid); // prob could use order pointer
        void executeOrder(string orderId, string client);
        void partialCancel(string orderId, int vol);
        
        int getVolumeAtPrice(int price, string side) {
            return volumeMap[price][side];
        };

        // add constructor OrderBook() : bestBid()
}

class OrderBook:
    def __init__(self) -> None:
        self.bestBid: MaxHeap = MaxHeap() # max heap
        self.bestAsk: MinHeap = MinHeap() # min heap
        self.orderMap: dict = {}
        self.volumeMap: dict = defaultdict(dict) # price // side // vol
        self.queueMap: dict = defaultdict(dict) # price // side // queue #DONT UNDERSTAND
        self.clientMap: dict = defaultdict(dict) # price // exposure/cash // value
        self.txct: int = 0

    
    def _crossedTrade(self, book, order) -> bool:
        if book.exists():
            if order.side == 'BID':
                if order.price >= book._peek(0): 
                    return True
            else:
                if order.price <= book._peek(0): 
                    return True
        return False
    
    def _updateHoldings(self, order, matchClient, txVolume, txPrice):
        # txPrice, txVolume = matchedOrder.price, min(order.volume, matchedOrder.volume)
        if order.side == "BID":
            self.clientMap[order.client]['Exposure'] += txVolume
            self.clientMap[order.client]['Cash'] -= txVolume * txPrice
            self.clientMap[matchClient]['Exposure'] -= txVolume
            self.clientMap[matchClient]['Cash'] += txVolume * txPrice
        else:
            self.clientMap[order.client]['Exposure'] -= txVolume
            self.clientMap[order.client]['Cash'] += txVolume * txPrice
            self.clientMap[matchClient]['Exposure'] += txVolume
            self.clientMap[matchClient]['Cash'] -= txVolume * txPrice

    def _placeResting(self, order, book) -> None: # Figure out the deal with queue map and heap
        
        self.orderMap[order.orderId] = Node(order)

        if order.price not in self.queueMap or order.side not in self.queueMap[order.price]:
            self.queueMap[order.price][order.side] = DoublyLinkedList(self.orderMap[order.orderId]) # [order] # DoublyLinkedList(order)
            book.insert(self.queueMap[order.price][order.side])
            self.volumeMap[order.price][order.side] = order.volume
        else:
            self.queueMap[order.price][order.side].append(self.orderMap[order.orderId]) # DLL
            self.volumeMap[order.price][order.side] += order.volume

    def placeOrder(self, order: Order) -> None:
        oppBook = self.bestAsk if order.side == 'BID' else self.bestBid
        sameBook = self.bestBid if order.side == 'BID' else self.bestAsk

        if order.client not in self.clientMap:
            self.clientMap[order.client]['Cash'] = 0
            self.clientMap[order.client]['Exposure'] = 0

#         self.orderMap[order.orderId] = Node(order)
# 
        while order.volume > 0 and self._crossedTrade(oppBook, order):
#             print(oppBook.printHeap())
            
            matchedOrder = oppBook.getMin()

            # self.txct += txVolume

            txPrice, txVolume = matchedOrder.price, min(order.volume, matchedOrder.volume) # add client side interaction here
            
            matchedOrder.volume -= txVolume
            order.volume -= txVolume

            self._updateHoldings(order, matchedOrder.client, txVolume, txPrice)

            self.volumeMap[txPrice][matchedOrder.side] -= txVolume

            if matchedOrder.volume == 0: 
                self.cancelOrder(matchedOrder.orderId)
#                 oppBook.popOrder()
#                 del self.orderMap[matchedOrder.orderId]

        if order.volume > 0:
            self._placeResting(order, sameBook)
    
    
    def cancelOrder(self, orderId) -> None:
        if orderId in self.orderMap:
            orderNode = self.orderMap[orderId]
            order = orderNode.item
            priceQueue = self.queueMap[order.price][order.side]
            priceQueue.remove(orderNode)
            if not priceQueue.exists():
                sameBook = self.bestBid if order.side == 'BID' else self.bestAsk
                sameBook.remove(priceQueue) # add O(log n) heap removal DONE
#                 sameBook.remove(self.queueMap[order.price][order.side]) # add O(log n) heap removal DONE
                del self.queueMap[order.price][order.side]
            self.volumeMap[order.price][order.side] -= order.volume
            del self.orderMap[orderId]
    
    def executeOrder(self, orderId, client) -> None:
        '''
        To do: add client side handling to update balances
        '''
        if orderId in self.orderMap:
            order = self.orderMap[orderId].item

            if client not in self.clientMap:
                self.clientMap[client]['Cash'] = 0
                self.clientMap[client]['Exposure'] = 0

            self._updateHoldings(order, client, order.volume, order.price)
            self.cancelOrder(orderId)
        
    def partialCancel(self, orderId, volume) -> None:
        if orderId in self.orderMap:
            order = self.orderMap[orderId].item
            order.volume -= volume
            self.volumeMap[order.price][order.side] -= order.volume

    def getVolumeAtPrice(self, price, side):
        return self.volumeMap[price][side]