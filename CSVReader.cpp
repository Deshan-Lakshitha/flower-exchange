//
// Created by ASUS on 12/12/2023.
//

#include "CSVReader.h"
#include <iostream>
#include <sstream>


vector<Order> CSVReader::readCSV(const string &filename) {
    vector<Order> orders;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return orders;
    }

    string line;
    getline(file, line); // Skip the header

    while (getline(file, line)) {
        Order order;
        parseOrder(line, order);
        orders.push_back(order);
    }

    file.close();
    return orders;
}

void CSVReader::parseOrder(const string &line, Order &order) {
    istringstream iss(line);
    string clientOrderId, instrument;
    string sideStr, quantityStr, priceStr;
    int side = -1, quantity = -1;
    double price = 0.0;

    getline(iss, clientOrderId, ',');
    getline(iss, instrument, ',');
    getline(iss, sideStr, ',');
    getline(iss, quantityStr, ',');
    getline(iss, priceStr, ',');

    if (!sideStr.empty()) side = stoi(sideStr);
    if (!quantityStr.empty()) quantity = stoi(quantityStr);
    if (!priceStr.empty()) price = stod(priceStr);

    order.setClientOrderId(clientOrderId);
    order.setInstrument(instrument);
    order.setSide(side);
    order.setSideStr(sideStr);
    order.setQuantity(quantity);
    order.setQuantityStr(quantityStr);
    order.setPrice(price);
    order.setPriceStr(priceStr);
}

void CSVReader::writeCSV(const string &filename, const vector<Order> &orders) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    file << "ClientOrderId, OrderId, Instrument, Side, Price, Quantity, ExecStatus, Reason,TransactionTime" << endl;
    for (size_t i = 0; i < orders.size(); i++) {
        file
                << orders[i].getClientOrderId() << ","
                << orders[i].getOrderId() << ","
                << orders[i].getInstrument() << ","
                << ((orders[i].getExecStatus() == "Reject") ? orders[i].getSideStr() : to_string(orders[i].getSide())) << ","
                << ((orders[i].getExecStatus() == "Reject") ? orders[i].getPriceStr() : to_string(orders[i].getPrice())) << ","
                << ((orders[i].getExecStatus() == "Reject") ? orders[i].getQuantityStr() : to_string(orders[i].getQuantity())) << ","
                << orders[i].getExecStatus() << ","
                << orders[i].getReason() << ","
                << orders[i].getTransactionTime() << endl;
    }

    file.close();

}
