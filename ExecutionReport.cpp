//
// Created by Jalitha Kalsara on 12/13/2023.
//

#include "ExecutionReport.h"


void ExecutionReport::setExecutionReport( vector<Order> &executionReport) {
    ExecutionReport::executionReport = executionReport;
}

vector<Order> &ExecutionReport::getExecutionReport()  {
    return executionReport;
}


