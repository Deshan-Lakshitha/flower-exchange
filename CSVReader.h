//
// Created by ASUS on 12/12/2023.
//

#ifndef FLOWER_EXCHANGE_CSVREADER_H
#define FLOWER_EXCHANGE_CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Order.h"

class CSVReader {
public:
    static vector<Order> readCSV(const string &filename);
    static void writeCSV(const string &filename, const vector<Order> &orders);

private:
    static void parseOrder(const string &line, Order &order);
};


#endif //FLOWER_EXCHANGE_CSVREADER_H
