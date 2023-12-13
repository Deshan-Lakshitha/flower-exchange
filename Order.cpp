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

string Order::getStatus() const {
    return status;
}

string Order::getReason() const {
    return reason;
}

string Order::getExecStatus() const {
    return execStatus;
}

string Order::getTransactionTime() const {
    return transactionTime;
}

string Order::getOrderId() const {
    return orderId;
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

void Order::setStatus(const string &status) {
    Order::status = status;
}

void Order::setReason(const string &reason) {
    Order::reason = reason;
}

void Order::setExecStatus(const string &execStatus) {
    Order::execStatus = execStatus;
}

void Order::setTransactionTime(const string &transactionTime) {
    Order::transactionTime = transactionTime;
}

void Order::setOrderId(const string &orderId) {
    Order::orderId = orderId;
}