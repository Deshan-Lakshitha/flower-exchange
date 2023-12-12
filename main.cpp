#include <iostream>
using namespace std;
#include "ExchangeApp.h"

int main()
{
    string filename = R"(C:\Users\ASUS\CLionProjects\flower-exchange\input\example_1.csv)";
    ExchangeApp::run(filename);

    return 0;
}
