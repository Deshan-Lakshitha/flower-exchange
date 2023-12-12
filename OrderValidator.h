//
// Created by ASUS on 12/12/2023.
//

#ifndef FLOWER_EXCHANGE_ORDERVALIDATOR_H
#define FLOWER_EXCHANGE_ORDERVALIDATOR_H

#include <string>
#include <vector>

using namespace std;

#include "Order.h"
#include <set>

class OrderValidator {
public:
    static void validateOrder(vector<Order> &orders);
private:
    static const int MIN_QUANTITY = 10;
    static const int MAX_QUANTITY = 1000;
//    static const std::set<std::string> INSTRUMENTS;
    enum SIDE {
        BUY = 1,
        SELL = 2
    };
    // Define the valid flower types
    std::string validFlowers[5];

    static bool validateClientOrderId(const string &clientOrderId);

    static bool validateInstrument(const string &instrument);

    static bool validateSide(int side);

    static bool validatePrice(double price);

    static bool validateQuantity(int quantity);
};


#endif //FLOWER_EXCHANGE_ORDERVALIDATOR_H
