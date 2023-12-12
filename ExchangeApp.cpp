//
// Created by ASUS on 12/12/2023.
//

#include <iostream>

using namespace std;

#include "ExchangeApp.h"
#include "CSVReader.h"

void ExchangeApp::run(std::string filename) {
    cout << "Exchange App Started!\n" << endl;

    // Read CSV file and create orders
    cout << "Reading CSV file...\n" << endl;
    vector<Order> orders = CSVReader::readCSV(filename);
    cout << "Number of orders: " << orders.size() << endl;

    // Validate orders
    cout << "Validating orders...\n" << endl;


}
