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
    int side, quantity;
    double price;

    getline(iss, clientOrderId, ',');
    getline(iss, instrument, ',');
    (iss >> side);
    (iss.ignore(1, ','));
    (iss >> quantity);
    (iss.ignore(1, ','));
    (iss >> price);

    order.setClientOrderId(clientOrderId);
    order.setInstrument(instrument);
    order.setSide(side);
    order.setQuantity(quantity);
    order.setPrice(price);
}
