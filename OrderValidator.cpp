//
// Created by ASUS on 12/12/2023.
//

#include "OrderValidator.h"

bool OrderValidator::validateClientOrderId(const string &clientOrderId) {
    // Check empty
    if (clientOrderId.empty()) {
        return false;
    }
    return true;
}

bool OrderValidator::validateInstrument(const string &instrument) {
    // Check empty
    if (instrument.empty()) {
        return false;
    }

    // Check valid instrument
    return INSTRUMENTS.find(instrument) != INSTRUMENTS.end();
}

bool OrderValidator::validateSide(int side) {
    // Check valid side
    return side == SIDE::BUY || side == SIDE::SELL;
}

bool OrderValidator::validatePrice(double price) {
    // Check price greater than 0
    return price > 0;
}

bool OrderValidator::validateQuantity(int quantity) {
    // Check multiple of 10
    if (quantity % 10 != 0) {
        return false;
    }

    // Check range
    return quantity >= MIN_QUANTITY && quantity <= MAX_QUANTITY;
}

bool OrderValidator::validateOrder(Order &order) {
    if (validateClientOrderId(order.getClientOrderId())) {
        return true;
    } else {
        return false;
    }
}
