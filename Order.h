//
// Created by ASUS on 12/12/2023.
//

#ifndef FLOWER_EXCHANGE_ORDER_H
#define FLOWER_EXCHANGE_ORDER_H


#include <iostream>
using namespace std;
#include <string>

class Order {
private:
    string clientOrderId;
    string instrument;
    int side;
    double price;
    int quantity;
    string status;
    string reason;
public:
    Order();    //    Default constructor
    Order(string &clientOrderId, string &instrument, int side, double price, int quantity);

    string getClientOrderId() const;
    string getInstrument() const;
    int getSide() const;
    double getPrice() const;
    int getQuantity() const;
    string getStatus() const;
    string getReason() const;

    void setClientOrderId(const string &clientOrderId);
    void setInstrument(const string &instrument);
    void setSide(int side);
    void setPrice(double price);
    void setQuantity(int quantity);
    void setStatus(const string &status);
    void setReason(const string &reason);
};


#endif //FLOWER_EXCHANGE_ORDER_H
