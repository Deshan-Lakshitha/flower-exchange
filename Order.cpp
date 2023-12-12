//
// Created by ASUS on 12/12/2023.
//

#include "Order.h"

Order::Order(string &clientOrderId, string &instrument, int side, double price, int quantity) {
    clientOrderId = clientOrderId;
    instrument = instrument;
    side = side;
    price = price;
    quantity = quantity;
}

Order::Order() {}

string Order::getClientOrderId() const {
    return clientOrderId;
}

string Order::getInstrument() const {
    return instrument;
}

int Order::getSide() const {
    return side;
}

double Order::getPrice() const {
    return price;
}

int Order::getQuantity() const {
    return quantity;
}

void Order::setClientOrderId(const string &clientOrderId) {
    Order::clientOrderId = clientOrderId;
}

void Order::setInstrument(const string &instrument) {
    Order::instrument = instrument;
}

void Order::setSide(int side) {
    Order::side = side;
}

void Order::setPrice(double price) {
    Order::price = price;
}

void Order::setQuantity(int quantity) {
    Order::quantity = quantity;
}
