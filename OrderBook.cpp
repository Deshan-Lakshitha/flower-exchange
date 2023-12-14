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

void OrderBook::addOrder(Order order, ExecutionReport &executionReport) {
    int side = order.getSide();
    if (side == 1) { //// BUY SIDE
        if (sellOrders.empty()) {   // If there are no sell orders, add the order directly to buy side as a new order
            order.setExecStatus("New");
            buyOrders.push_back(order);
            order.setTransactionTime(getTimeStamp());
            executionReport.getExecutionReport().push_back(order);
        } else {
            int sellOrdersSize = sellOrders.size();
            for (size_t i = 0; i < sellOrdersSize; i++) {
                int buyPrice = order.getPrice();
                int sellPrice = sellOrders[0].getPrice();
                if (buyPrice < sellPrice) { // If the buy price is less than the sell price, add the order to buy side
                    if (i > 0){  // If the order is not a new one
                        buyOrders.push_back(order);
                        break;
                    }
                    // If the order is a new one
                    order.setExecStatus("New");
                    buyOrders.push_back(order);
                    order.setTransactionTime(getTimeStamp());
                    executionReport.getExecutionReport().push_back(order);
                    break;
                } else {    // When the buy price is greater than or equal to the sell price need to execute accordingly
                    int sellQuantity = sellOrders[0].getQuantity();
                    int buyQuantity = order.getQuantity();
                    int difference = buyQuantity - sellQuantity;
                    if (difference == 0) {  // Both orders are fully filled
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
                    } else if (difference < 0) {   // The sell order is partially filled
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
                    } else {    // The buy order is partially filled
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

            // After iterating through all the sell orders, if the order is still partially filled, add it to buy side
            if(order.getExecStatus() == "PFill"){
                buyOrders.push_back(order);
            }
        }

        // After executing each order, sort the buy orders based on price
        // Use descending order since we are in the buy side
        std::sort(buyOrders.begin(), buyOrders.end(), compareOrderByPriceDescending);

    } else { //// SELL SIDE
        if (buyOrders.empty()) {    // If there are no buy orders, add the order directly to sell side as a new order
            order.setExecStatus("New");
            sellOrders.push_back(order);
            order.setTransactionTime(getTimeStamp());
            executionReport.getExecutionReport().push_back(order);
        } else {
            int buyOrderSize = buyOrders.size();
            for (size_t i = 0; i < buyOrderSize; i++) {
                int sellPrice = order.getPrice();
                int buyPrice = buyOrders[0].getPrice();
                if (sellPrice > buyPrice) { // If the sell price is greater than the buy price, add the order to sell side
                    if (i > 0){    // If the order is not a new one
                        sellOrders.push_back(order);
                        break;
                    }
                    // If the order is a new one
                    order.setExecStatus("New");
                    sellOrders.push_back(order);
                    order.setTransactionTime(getTimeStamp());
                    executionReport.getExecutionReport().push_back(order);
                    break;
                } else {
                    int buyQuantity = buyOrders[0].getQuantity();
                    int sellQuantity = order.getQuantity();
                    int difference = sellQuantity - buyQuantity;
                    if (difference == 0) { // Both orders are fully filled
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
                    } else if (difference < 0) {    // The buy order is partially filled
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
                    } else {    // The sell order is partially filled
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

            // After iterating through all the buy orders, if the order is still partially filled, add it to sell side
            if(order.getExecStatus() == "PFill"){
                sellOrders.push_back(order);
            }
        }

        // After executing each order, sort the sell orders based on price
        // Use ascending order since we are in the sell side
        std::sort(sellOrders.begin(), sellOrders.end(), compareOrderByPriceAscending);
    }
}

// Custom comparator function for sorting based on price ascending
bool OrderBook::compareOrderByPriceAscending(Order &a, Order &b) {
    return a.getPrice() < b.getPrice();
}

// Custom comparator function for sorting based on price descending
bool OrderBook::compareOrderByPriceDescending(Order &a, Order &b) {
    return a.getPrice() > b.getPrice();
}

// Get the current time in the desired format
string OrderBook::getTimeStamp() {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Format the time (without millisecond part)
    struct std::tm* timeInfo = std::localtime(&currentTime);

    // Create a string with the desired format
    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%Y%m%d-%H%M%S");

    // Add milliseconds
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}


