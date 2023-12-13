//
// Created by Jalitha Kalsara on 12/13/2023.
//

#ifndef FLOWER_EXCHANGE_ORDERBOOK_H
#define FLOWER_EXCHANGE_ORDERBOOK_H


#include <vector>
#include "Order.h"
#include "ExecutionReport.h"

class OrderBook {
private:
    string type;               // Type of the order book
    std::vector<Order> buyOrders;   // Vector to store Buy orders
    std::vector<Order> sellOrders;  // Vector to store Sell orders

public:
    OrderBook(string &type);

    static bool compareOrderByPriceAscending(Order& a, Order& b);
    static bool compareOrderByPriceDescending(Order& a, Order& b);

    string getTimeStamp();
    // Function to add an order to the order book
    void addOrder(Order order, ExecutionReport &executionReport);


};


#endif //FLOWER_EXCHANGE_ORDERBOOK_H
