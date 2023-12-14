//
// Created by ASUS on 12/12/2023.
//

#include <iostream>
#include <vector>

using namespace std;

#include "ExchangeApp.h"
#include "CSVReader.h"
#include "OrderValidator.h"
#include "OrderBook.h"
#include "ExecutionReport.h"

void ExchangeApp::run(std::string filename, std::string outputFilename) {
    cout << "\n============Exchange App Started!============\n" << endl;

    // Read CSV file and create orders
    cout << "Reading CSV file...\n" << endl;
    vector<Order> orders = CSVReader::readCSV(filename);
    cout << "Number of orders: " << orders.size() << endl;

    // Validate orders
    cout << "Validating orders...\n" << endl;
    OrderValidator::validateOrder(orders);

    // Create the execution report object
    ExecutionReport executionReport;

    // Create a separate order book for each instrument
    OrderBook roseOrderBook((string &) "Rose");
    OrderBook lavenderOrderBook((string &) "Lavender");
    OrderBook lotusOrderBook((string &) "Lotus");
    OrderBook tulipOrderBook((string &) "Tulip");
    OrderBook orchidOrderBook((string &) "Orchid");

    // Execute each order
    for (size_t i = 0; i < orders.size(); i++) {
        std::string strNumber = std::to_string(i+1);    // Generate a unique order ID for each order
        orders[i].setOrderId("ord" + strNumber);
        if (orders[i].getStatus() == "Accepted"){
            std::string instrument = orders[i].getInstrument();
            if (instrument == "Rose") {
                roseOrderBook.addOrder(orders[i], executionReport);
            } else if (instrument == "Lavender") {
                lavenderOrderBook.addOrder(orders[i], executionReport);
            } else if (instrument == "Lotus") {
                lotusOrderBook.addOrder(orders[i], executionReport);
            } else if (instrument == "Tulip") {
                tulipOrderBook.addOrder(orders[i], executionReport);
            } else if (instrument == "Orchid") {
                orchidOrderBook.addOrder(orders[i], executionReport);
            }
        } else {
            orders[i].setExecStatus("Reject");
            executionReport.getExecutionReport().push_back(orders[i]);
        }
    }

    cout << "Execution list size: " << executionReport.getExecutionReport().size() << "\n" << endl;
    cout << "----------------- Execution List -----------------------" << endl;
    for (size_t i = 0; i < executionReport.getExecutionReport().size(); i++) {
        cout << executionReport.getExecutionReport()[i].getOrderId() << " "<< executionReport.getExecutionReport()[i].getClientOrderId() << " " << executionReport.getExecutionReport()[i].getInstrument() << " " << executionReport.getExecutionReport()[i].getSide() << " " << executionReport.getExecutionReport()[i].getExecStatus() << " " << executionReport.getExecutionReport()[i].getQuantity() << " " << executionReport.getExecutionReport()[i].getPrice() << " " << executionReport.getExecutionReport()[i].getReason() << " " << executionReport.getExecutionReport()[i].getTransactionTime() << endl;
    }
    cout << "--------------------------------------------------------\n" << endl;

    // Write CSV file
    cout << "Writing CSV file..." << endl;
    CSVReader::writeCSV(outputFilename, executionReport.getExecutionReport());
    cout << "CSV file written successfully!\n" << endl;

    cout << "============Exchange App Ended!============\n" << endl;
}
