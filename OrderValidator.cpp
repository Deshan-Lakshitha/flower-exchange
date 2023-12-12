//
// Created by ASUS on 12/12/2023.
//

#include "OrderValidator.h"
#include <iostream>


void OrderValidator::validateOrder(vector<Order> & orders) {
    for (size_t i = 0; i < orders.size(); i++) {
        if (!validateClientOrderId(orders[i].getClientOrderId())) {
            orders[i].setStatus("Reject");
            orders[i].setReason("Invalid client order id");
        } else if (!validateInstrument(orders[i].getInstrument())) {
            orders[i].setStatus("Reject");
            orders[i].setReason("Invalid instrument");
        } else if (!validateSide(orders[i].getSide())) {
            orders[i].setStatus("Reject");
            orders[i].setReason("Invalid side");
        } else if (!validatePrice(orders[i].getPrice())) {
            orders[i].setStatus("Reject");
            orders[i].setReason("Invalid price");
        } else if (!validateQuantity(orders[i].getQuantity())) {
            orders[i].setStatus("Reject");
            orders[i].setReason("Invalid quantity");
        } else {
            orders[i].setStatus("Accepted");
            orders[i].setReason("");
        }
    }
}

bool OrderValidator::validateClientOrderId(const string &clientOrderId) {
    // Check empty
    if (clientOrderId.empty()) {
        return false;
    }
    return true;
}

bool OrderValidator::validateInstrument(const string &instrument) {

    // Check if the instrument is one of the specified types
    if (instrument == "Rose" || instrument == "Lavender" || instrument == "Lotus" || instrument == "Tulip" || instrument == "Orchid") {
        return true;
    } else {
        return false;
    }
}

bool OrderValidator::validateSide(int side) {
    // Check valid side
    return side == SIDE::BUY || side == SIDE::SELL;
}

bool OrderValidator::validatePrice(double price) {
    // Check price greater than 0.1
    return price > 0.1; // check why blank space is have a small value
}

bool OrderValidator::validateQuantity(int quantity) {
    // Check multiple of 10
    if (quantity % 10 != 0) {
        return false;
    }

    // Check range
    return quantity >= MIN_QUANTITY && quantity <= MAX_QUANTITY;
}