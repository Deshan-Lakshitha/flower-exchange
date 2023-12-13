//
// Created by Jalitha Kalsara on 12/13/2023.
//

#include "OrderBook.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

OrderBook::OrderBook(string &type) {
    type = type;
}

//// Custom comparator function for sorting based on price
//bool compareOrderByPrice(const Order& a, const Order& b) {
//    return a.getPrice() < b.getPrice();
//}

void OrderBook::addOrder(Order order, ExecutionReport &executionReport) {

    int side = order.getSide();
    if (side == 1) { // buy side
        cout << "Buy side" << endl;
        if (sellOrders.empty()) {
            order.setExecStatus("New");
            buyOrders.push_back(order);
            order.setTransactionTime(getTimeStamp());
            executionReport.getExecutionReport().push_back(order);
        } else {
            int sellOrdersSize = sellOrders.size();
            for (size_t i = 0; i < sellOrdersSize; i++) {
                int buyPrice = order.getPrice();
                int sellPrice = sellOrders[0].getPrice();
                if (buyPrice < sellPrice) {
                    if(i > 0){
                        buyOrders.push_back(order);
                        break;
                    }
                    order.setExecStatus("New");
                    buyOrders.push_back(order);
                    order.setTransactionTime(getTimeStamp());
                    executionReport.getExecutionReport().push_back(order);
                    break;
                } else {
                    int sellQuantity = sellOrders[0].getQuantity();
                    int buyQuantity = order.getQuantity();
                    int difference = buyQuantity - sellQuantity;
                    if (difference == 0) {
                        sellOrders[0].setExecStatus("Fill");
                        order.setExecStatus("Fill");
                        order.setPrice(sellPrice);
                        sellOrders[0].setTransactionTime(getTimeStamp());
                        order.setTransactionTime(getTimeStamp());
                        executionReport.getExecutionReport().push_back(order);
                        executionReport.getExecutionReport().push_back(sellOrders[0]);
                        order.setPrice(buyPrice);
                        sellOrders.erase(sellOrders.begin());
                        break;
                    } else if (difference < 0) {
                        sellOrders[0].setExecStatus("PFill");
                        order.setExecStatus("Fill");
                        order.setPrice(sellPrice);
                        sellOrders[0].setQuantity(order.getQuantity());
                        sellOrders[0].setTransactionTime(getTimeStamp());
                        order.setTransactionTime(getTimeStamp());
                        executionReport.getExecutionReport().push_back(order);
                        executionReport.getExecutionReport().push_back(sellOrders[0]);
                        order.setPrice(buyPrice);
                        sellOrders[0].setQuantity(sellQuantity - buyQuantity);
                        break;
                    } else {
                        sellOrders[0].setExecStatus("Fill");
                        order.setExecStatus("PFill");
                        order.setPrice(sellPrice);
                        order.setQuantity(sellOrders[0].getQuantity());
                        order.setTransactionTime(getTimeStamp());
                        sellOrders[0].setTransactionTime(getTimeStamp());
                        executionReport.getExecutionReport().push_back(order);
                        executionReport.getExecutionReport().push_back(sellOrders[0]);
                        order.setPrice(buyPrice);
                        sellOrders.erase(sellOrders.begin());
                        order.setQuantity(difference);
                    }
                }
            }
            if(order.getExecStatus() == "PFill"){
                buyOrders.push_back(order);
            }
        }
        std::sort(buyOrders.begin(), buyOrders.end(), compareOrderByPriceDescending);

    } else { // sell side
        cout << "Sell side" << endl;
        if (buyOrders.empty()) {
            order.setExecStatus("New");
            sellOrders.push_back(order);
            order.setTransactionTime(getTimeStamp());
            executionReport.getExecutionReport().push_back(order);
        } else {
            int buyOrderSize = buyOrders.size();
            for (size_t i = 0; i < buyOrderSize; i++) {
                int sellPrice = order.getPrice();
                int buyPrice = buyOrders[0].getPrice();
                if (sellPrice > buyPrice) {
                    if(i>0){
                        sellOrders.push_back(order);
                        break;
                    }
                    order.setExecStatus("New");
                    sellOrders.push_back(order);
                    order.setTransactionTime(getTimeStamp());
                    executionReport.getExecutionReport().push_back(order);
                    break;
                } else {
                    int buyQuantity = buyOrders[0].getQuantity();
                    int sellQuantity = order.getQuantity();
                    int difference = sellQuantity - buyQuantity;
                    if (difference == 0) {
                        buyOrders[0].setExecStatus("Fill");
                        order.setExecStatus("Fill");
                        order.setPrice(buyPrice);
                        order.setTransactionTime(getTimeStamp());
                        buyOrders[0].setTransactionTime(getTimeStamp());
                        executionReport.getExecutionReport().push_back(order);
                        executionReport.getExecutionReport().push_back(buyOrders[0]);
                        order.setPrice(sellPrice);
                        buyOrders.erase(buyOrders.begin());
                        break;
                    } else if (difference < 0) {
                        buyOrders[0].setExecStatus("PFill");
                        order.setExecStatus("Fill");
                        order.setPrice(buyPrice);
                        buyOrders[0].setQuantity(order.getQuantity());
                        order.setTransactionTime(getTimeStamp());
                        buyOrders[0].setTransactionTime(getTimeStamp());
                        executionReport.getExecutionReport().push_back(order);
                        executionReport.getExecutionReport().push_back(buyOrders[0]);
                        order.setPrice(sellPrice);
                        buyOrders[0].setQuantity(buyQuantity - sellQuantity);
                        break;
                    } else {
                        buyOrders[0].setExecStatus("Fill");
                        order.setExecStatus("PFill");
                        order.setPrice(buyPrice);
                        order.setQuantity(buyOrders[0].getQuantity());
                        order.setTransactionTime(getTimeStamp());
                        buyOrders[0].setTransactionTime(getTimeStamp());
                        executionReport.getExecutionReport().push_back(order);
                        executionReport.getExecutionReport().push_back(buyOrders[0]);
                        order.setPrice(sellPrice);
                        buyOrders.erase(buyOrders.begin());
                        order.setQuantity(difference);
                    }
                }
            }
            if(order.getExecStatus() == "PFill"){
                sellOrders.push_back(order);
            }
        }
        // Use the sort function with a custom comparator for sorting based on price
        std::sort(sellOrders.begin(), sellOrders.end(), compareOrderByPriceAscending);
    }
}

bool OrderBook::compareOrderByPriceAscending(Order &a, Order &b) {
    return a.getPrice() < b.getPrice();
}

bool OrderBook::compareOrderByPriceDescending(Order &a, Order &b) {
    return a.getPrice() > b.getPrice();
}

string OrderBook::getTimeStamp() {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Format the time
    struct std::tm* timeInfo = std::localtime(&currentTime);

    // Create a string with the desired format
    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%Y%m%d-%H%M%S");

    // Add milliseconds
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}


