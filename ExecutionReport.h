//
// Created by Jalitha Kalsara on 12/13/2023.
//

#ifndef FLOWER_EXCHANGE_EXECUTIONREPORT_H
#define FLOWER_EXCHANGE_EXECUTIONREPORT_H


#include <vector>
#include "Order.h"

class ExecutionReport {
private:
    std::vector<Order> executionReport;
public:
    void setExecutionReport(vector<Order> &executionReport);

    vector<Order> &getExecutionReport();
};


#endif //FLOWER_EXCHANGE_EXECUTIONREPORT_H
