#include <iostream>
#include "order.cpp"
using namespace std;

int main() {

    Order o4(4, 98765.4321, "Sell", 930.0f, 20, "Client B");

    std::cout << o4.price << std::endl;

    return 0; 
}